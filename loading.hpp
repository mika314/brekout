#pragma once

#include "obj.hpp"
#include "sprite.hpp"

namespace sdl
{
  class Renderer;
}

class Loading : public Obj
{
public:
  Loading(sdl::Renderer &r, int x, int y);
  auto draw(class Canvas &) -> void override;

private:
  std::vector<sdl::Texture> sprites;
};
