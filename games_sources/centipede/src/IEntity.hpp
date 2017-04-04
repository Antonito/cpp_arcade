
#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <vector>
#include <cstddef>
#include <memory>

namespace arcade
{

class IEntity
{
  public:
    virtual ~IEntity(){};
    virtual std::vector<std::unique_ptr<ITile>> const &operator[](int n) const = 0;
    virtual size_t getWidth() const = 0;
    virtual size_t getHeight() const = 0;
};
}

#endif // !IENTITY_HPP_
