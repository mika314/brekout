#include "fruit.hpp"
#include "canvas.hpp"
#include "sprite.hpp"

Fruit::Fruit(sdl::Renderer &r) : r(r), sprite(r.get(), LOAD_SPRITE(fruit)), x(rand() % (80 - 4) + 2), y(rand() % (45 - 7) + 4) {}

auto Fruit::draw(Canvas &c) -> void
{
  c.draw(sprite, x * 16, y * 16, 16, 16);
}

auto Fruit::eat() -> void
{
  x = rand() % (80 - 4) + 2;
  y = rand() % (45 - 7) + 4;
}
