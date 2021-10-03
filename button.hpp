#pragma once
#include "obj.hpp"
#include "sprite.hpp"
#include <memory>

namespace sdl
{
  class Renderer;
}

class Button : public Obj
{
public:
  Button(sdl::Renderer &, class Audio &, SDL_Surface *, int x, int y, int w, int h, std::function<auto()->void> onClick);
  Button(sdl::Renderer &, class Audio &, SDL_Surface *, SDL_Surface *, int x, int y, int w, int h, std::function<auto()->void> onClick);
  auto draw(class Canvas &) -> void override;
  auto tick(float dt) -> void override;
  auto mouseUp(Btn, int x, int y) -> void override;
  auto mouseDown(Btn, int x, int y) -> void override;

private:
  std::reference_wrapper<class Audio> audio;
  sdl::Texture sprite;
  std::unique_ptr<sdl::Texture> spriteDown;
  int w;
  int h;
  std::function<auto()->void> onClick;
  bool isDown = false;
};
