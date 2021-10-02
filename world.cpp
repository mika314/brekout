#include "world.hpp"
#include <cmath>
#include <sdlpp/sdlpp.hpp>

auto World::draw(Canvas &canvas) -> void
{
  for (auto &obj : objs)
    obj->draw(canvas);
}

auto World::tick(float dt) -> void
{
  std::vector<Obj *> tmpObjs;
  for (auto &obj : objs)
    tmpObjs.push_back(obj.get());
  for (auto &obj : tmpObjs)
    obj->tick(dt);
}

auto World::housekeeping() -> void
{
  std::erase_if(objs, [](const std::unique_ptr<Obj> &x) { return !x->getIsAlive(); });
}

auto World::getObjsN() const -> int
{
  return objs.size();
}

auto World::regEvents(sdl::EventHandler &e) -> void
{
  e.mouseMotion = [this](const SDL_MouseMotionEvent &e) {
    const auto x = e.x;
    const auto y = e.y;
    std::vector<Obj *> tmpObjs;
    for (auto &obj : objs)
      tmpObjs.push_back(obj.get());
    for (auto &obj : tmpObjs)
      obj->mouseMove(x, y);
  };
  e.mouseButtonDown = [this](const SDL_MouseButtonEvent &e) {
    const auto x = e.x;
    const auto y = e.y;
    const auto btn = [b = e.button]() {
      switch (b)
      {
      case SDL_BUTTON_LEFT:
      default: return Btn::l;
      case SDL_BUTTON_MIDDLE: return Btn::m;
      case SDL_BUTTON_RIGHT: return Btn::r;
      }
    }();
    std::vector<Obj *> tmpObjs;
    for (auto &obj : objs)
      tmpObjs.push_back(obj.get());
    for (auto &obj : tmpObjs)
      obj->mouseDown(btn, x, y);
  };
  e.mouseButtonUp = [this](const SDL_MouseButtonEvent &e) {
    const auto x = e.x;
    const auto y = e.y;
    const auto btn = [b = e.button]() {
      switch (b)
      {
      case SDL_BUTTON_LEFT:
      default: return Btn::l;
      case SDL_BUTTON_MIDDLE: return Btn::m;
      case SDL_BUTTON_RIGHT: return Btn::r;
      }
    }();
    std::vector<Obj *> tmpObjs;
    for (auto &obj : objs)
      tmpObjs.push_back(obj.get());
    for (auto &obj : tmpObjs)
      obj->mouseUp(btn, x, y);
  };
}
