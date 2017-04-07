#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <string>
#include "IComponent.hpp"
#include "Color.hpp"

namespace arcade
{
  class Component : public IComponent
  {
  public:
    Component();
    Component(double x, double y, double width, double height,
      Color color = Color::Transparent, std::string const &text = "");
    Component(Component const &other) = default;
    Component(Component &&other) = default;
    virtual ~Component();

    Component &operator=(Component const &other) = default;
    Component &operator=(Component &&other) = default;

    virtual double getX() const;
    virtual double getY() const;

    void setX(double x);
    void setY(double y);

    virtual double getWidth() const;
    virtual double getHeight() const;

    void setWidth(double width);
    void setHeight(double height);

    virtual std::size_t getBackgroundId() const;
    virtual Color getBackgroundColor() const;
    virtual std::string const &getText() const;
    virtual bool hasSprite() const;
    virtual Color getTextColor() const;

    void setBackgroundId(std::size_t id);
    void setBackgroundColor(Color color);
    void setText(std::string const &text);

    virtual void setClicked();
    void setClicked(bool click);
    bool isClicked() const;

  private:
    typedef struct
    {
      double x;
      double y;
    }          m_vec;

    m_vec m_pos;
    m_vec m_size;

    std::size_t m_sprite;
    Color m_color;
    std::string m_text;
    bool m_clicked;
  };
}

#endif // !COMPONENT_HPP_
