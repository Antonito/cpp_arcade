#include <iostream>
#if defined(_WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Snake.hpp"

namespace arcade
{
Snake::Snake()
{
    constexpr size_t width = 24;
    constexpr size_t height = 24;

    m_map = std::make_unique<Map>(width, height);
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            m_map->at(0, x, y).setColor(Color::White);
        }
    };
    m_map->addLayer();
    m_gui = std::make_unique<GUI>();

    m_dir = Dir::LEFT;
    m_player = Player(Pos(width / 2, height / 2), m_dir, 4);
    m_food = Powerup(placeFood(), *m_map);
    m_lastTick = 0;
    m_curTick = 0;

    Component comp;

    comp.setX(0.05);
    comp.setY(0.05);
    comp.setWidth(0.15);
    comp.setHeight(0.05);
    comp.setBackgroundColor(Color(0, 0, 0, 170));
    m_gui->push(std::move(comp));
}

Snake::Snake(Snake const &other)
{
    size_t width = other.m_map->getWidth();
    size_t height = other.m_map->getHeight();

    m_map = std::make_unique<Map>(width, height);
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            m_map->at(0, x, y).setColor(Color::White);
        }
    };

    m_dir = Dir::LEFT;
    m_player = Player(Pos(width / 2, height / 2), m_dir, 4);
    m_food = Powerup(placeFood(), *m_map);
    m_lastTick = 0;
    m_curTick = 0;
    // TODO : also copy layers
}

Snake::~Snake()
{
}

Snake &Snake::operator=(Snake const &other)
{
    std::cout << "eq" << std::endl;
    if (this != &other)
    {
    }
    return (*this);
}

void Snake::notifyEvent(std::vector<Event> &&events)
{
    std::vector<Event> ev = events;

    for (Event const &e : ev)
    {
        if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
        {
            switch (e.kb_key)
            {
            case KB_ARROW_UP:
                if (m_dir != Dir::DOWN)
                    m_dir = Dir::UP;
                break;
            case KB_ARROW_DOWN:
                if (m_dir != Dir::UP)
                    m_dir = Dir::DOWN;
                break;
            case KB_ARROW_LEFT:
                if (m_dir != Dir::RIGHT)
                    m_dir = Dir::LEFT;
                break;
            case KB_ARROW_RIGHT:
                if (m_dir != Dir::LEFT)
                    m_dir = Dir::RIGHT;
                break;
            case KB_ESCAPE:
                m_state = MENU;
            default:
                break;
            }
        }
    }
}

std::vector<std::pair<std::string, SoundType>> Snake::getSoundsToLoad() const
{
    // TODO: implement
    return (std::vector<std::pair<std::string, SoundType>>());
}

std::vector<std::unique_ptr<ISprite>> &&Snake::getSpritesToLoad() const
{
    std::vector<std::unique_ptr<ISprite>> s;

    return (std::move(s));
}

Pos Snake::placeFood()
{
    Pos new_food(rand() % m_map->getWidth(), rand() % m_map->getHeight());

    while (m_player.touchTail(new_food))
    {
        new_food = Pos(rand() % m_map->getWidth(), rand() % m_map->getHeight());
    }
    return (new_food);
}

void Snake::process()
{
    Pos next;

    m_curTick = this->getCurrentTick();
    if ((m_curTick - m_lastTick) > 60)
    {
        for (size_t y = 0; y < m_map->getHeight(); ++y)
        {
            for (size_t x = 0; x < m_map->getWidth(); ++x)
            {
                m_map->at(1, x, y).setColor(Color::Transparent);
            }
        };

        m_food.display(*m_map);
        m_player.display(*m_map);
        if (m_player.getPos() == m_food.getPos())
            m_food.replace(*m_map, placeFood());
        if (m_player.move(*m_map, m_dir) || m_player.touchTail(m_player.getPos()))
            m_state = MENU;
        m_lastTick = m_curTick;
    }
}

#if defined(__linux__)
WhereAmI *Snake::getWhereAmI() const
{
    WhereAmI *w = new WhereAmI;

    w->type = CommandType::WHERE_AM_I;
    w->lenght = 0;
    return (w);
}
#endif
}
