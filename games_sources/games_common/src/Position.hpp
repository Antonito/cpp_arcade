#ifndef POS_HPP_
#define POS_HPP_

#include <stdint.h>
#include "Map.hpp"

namespace arcade
{
  namespace game
  {
    enum class Direction : uint16_t
    {
      UP = 0,
      DOWN = 1,
      LEFT = 2,
      RIGHT = 3
    };

    class Position
    {
    public:
      Position();
      Position(ssize_t x, ssize_t y);
      Position(Position const &other) = default;
      ~Position();

      Position &operator=(Position const &other) = default;
      bool operator==(Position const &other) const;
      bool operator!=(Position const &other) const;
      Position operator+(Position const &other) const;
      Position &operator+=(Position const &other);
      Position operator-(Position const &other) const;
      Position &operator-=(Position const &other);
      Position operator+(Direction dir) const;
      Position &operator+=(Direction dir);
      Position operator-(Direction dir) const;
      Position &operator-=(Direction dir);

      bool inMap(Map &map);
      ssize_t x;
      ssize_t y;
    };
  }
}

#endif // !POS_HPP_