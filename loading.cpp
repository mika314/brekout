#include "loading.hpp"
#include "canvas.hpp"

Loading::Loading(sdl::Renderer &r, int x, int y) : Obj(x, y)
{
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_00));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_01));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_02));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_03));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_04));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_05));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_06));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_07));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_08));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_09));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_10));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_11));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_12));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_13));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_14));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_15));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_16));
  sprites.emplace_back(r.get(), LOAD_SPRITE(loading_17));
}
auto Loading::draw(class Canvas &c) -> void
{
  c.draw(sprites[SDL_GetTicks() / 80 % sprites.size()], x, y, 300, 300);
}
