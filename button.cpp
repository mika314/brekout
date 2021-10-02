#include "button.hpp"
#include "canvas.hpp"
#include <sdlpp/sdlpp.hpp>

Button::Button(sdl::Renderer &r, SDL_Surface *s, int x, int y, int w, int h, std::function<auto()->void> onClick)
  : Obj(x, y), sprite(r.get(), s), w(w), h(h), onClick(std::move(onClick))
{
}

auto Button::draw(class Canvas &c) -> void
{
  c.draw(sprite, x, y, w, h);
}

auto Button::tick(float) -> void {}

auto Button::mouseUp(Btn btn, int ax, int ay) -> void
{
  if (btn != Btn::l)
    return;
  if (ax < x)
    return;
  if (ay < y)
    return;
  if (ax > x + w)
    return;
  if (ay > y + h)
    return;
  onClick();
}
