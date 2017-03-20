#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <vector>
#include <memory>
#include <cstdlib>
#include "ILayer.hpp"
#include "Tile.hpp"

namespace arcade
{
  class Layer : public ILayer
  {
  public:
    explicit Layer(size_t width, size_t height);
    Layer(Layer const &other) = default;
    Layer(Layer &&other) = default;
    virtual ~Layer();

    Layer &operator=(Layer const &other) = delete;

	virtual std::vector<std::unique_ptr<ITile>> &operator[](int n);
	virtual std::vector<std::unique_ptr<ITile>> const &operator[](int n) const;
    virtual size_t getWidth() const;
    virtual size_t getHeight() const;

  private:
    std::vector<std::vector<std::unique_ptr<ITile>>> m_tiles;
    size_t                                           m_width;
    size_t                                           m_height;
  };
}

#endif // !LAYER_HPP_