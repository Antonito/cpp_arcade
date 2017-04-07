#include <iostream>
#if defined(_WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <sstream>
#include "Snake.hpp"
#include "Sprite.hpp"

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
          m_map->at(0, x, y).setColor(Color(20, 20, 20));
          m_map->at(0, x, y).removeSprite();
        }
    };
    m_map->addLayer();
    m_gui = std::make_unique<GUI>();

    m_dir = Dir::LEFT;
    m_player = Player(Pos(width / 2, height / 2), m_dir, 4);
    m_food = Powerup(placeFood(), *m_map);
    m_lastTick = 0;
    m_curTick = 0;
    m_score = 0;

    Component comp;

    comp.setX(0.05);
    comp.setY(0.05);
    comp.setWidth(0.15);
    comp.setHeight(0.05);
    comp.setBackgroundColor(Color(0, 0, 0, 170));
    m_gui->push(std::move(comp));

    comp.setX(0.07);
    comp.setY(0.05);
    comp.setBackgroundColor(Color::Transparent);
    comp.setText("0");
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
            m_map->at(0, x, y).setColor(Color(20, 20, 20));
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

std::vector<std::unique_ptr<ISprite>> Snake::getSpritesToLoad() const
{
  std::vector<std::unique_ptr<ISprite>> s;

  s.push_back(std::make_unique<Sprite>("./assets/snake/", "cherry", 1, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("./assets/snake/", "strawberry", 1, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("./assets/snake/", "peach", 1, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("./assets/snake/", "apple", 1, ".png", "$"));
  s.push_back(std::make_unique<Sprite>("./assets/snake/", "head", 1, ".png", "O"));
  s.push_back(std::make_unique<Sprite>("./assets/snake/", "body", 1, ".png", "o"));
  return (s);
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
    std::stringstream ss;

    m_curTick = this->getCurrentTick();
    if ((m_curTick - m_lastTick) > 60)
    {
      // Clear the layer
        for (size_t y = 0; y < m_map->getHeight(); ++y)
        {
            for (size_t x = 0; x < m_map->getWidth(); ++x)
            {
              m_map->at(1, x, y).setColor(Color::Transparent);
              m_map->at(1, x, y).removeSprite();
            }
        };

        // Display the food
        m_food.display(*m_map);

        // Check if food is being eaten
        if (m_player.getPos() == m_food.getPos())
        {
          m_food.replace(*m_map, placeFood());
          m_score++;
        }
        // Move the player if possible
        if (m_player.move(*m_map, m_dir) || m_player.touchTail(m_player.getPos()))
            m_state = MENU;

        // Update the current tick
        m_lastTick = m_curTick;

        // Update the displayed score
        ss << m_score;
        m_gui->at(1).setText(ss.str());
    }
    // Display the player and update it everytime for smooth movement
    if (m_state == INGAME)
      m_player.display(*m_map, (m_curTick - m_lastTick) / 60.0);
}

#if defined(__linux__)
WhereAmI *Snake::getWhereAmI() const
{
    return (m_player.getWhereAmI());
}
#endif
}

extern "C" void Play(void)
{
  arcade::Snake game;

  game.Play();
}