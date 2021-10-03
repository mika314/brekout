#include "button.hpp"
#include "audio.hpp"
#include "canvas.hpp"
#include <sdlpp/sdlpp.hpp>

Button::Button(sdl::Renderer &r, Audio &audio, SDL_Surface *s, int x, int y, int w, int h, std::function<auto()->void> onClick)
  : Obj(x, y), audio(audio), sprite(r.get(), s), w(w), h(h), onClick(std::move(onClick))
{
}

Button::Button(sdl::Renderer &r, Audio &audio, SDL_Surface *s, SDL_Surface *down, int x, int y, int w, int h, std::function<auto()->void> onClick)
  : Obj(x, y), audio(audio), sprite(r.get(), s), spriteDown(std::make_unique<sdl::Texture>(r.get(), down)), w(w), h(h), onClick(std::move(onClick))
{
}

auto Button::draw(class Canvas &c) -> void
{
  if (isDown && spriteDown)
    c.draw(*spriteDown, x, y, w, h);
  else
    c.draw(sprite, x, y, w, h);
}

auto Button::tick(float) -> void {}

auto Button::mouseUp(Btn btn, int ax, int ay) -> void
{
  isDown = false;
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
  if (!onClick)
    return;
  audio.get().PLAY(click, 1, 0);
  onClick();
}

auto Button::mouseDown(Btn btn, int ax, int ay) -> void
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
  isDown = true;
}
