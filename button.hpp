#pragma once
#include "obj.hpp"
#include "sprite.hpp"

namespace sdl
{
  class Renderer;
}

class Button : public Obj
{
public:
  Button(sdl::Renderer &r, SDL_Surface *, int x, int y, int w, int h, std::function<auto()->void> onClick);
  auto draw(class Canvas &) -> void override;
  auto tick(float dt) -> void override;
  auto mouseUp(Btn, int x, int y) -> void override;

private:
  sdl::Texture sprite;
  int w;
  int h;
  std::function<auto()->void> onClick;
};
