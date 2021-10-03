#pragma once
#include "obj.hpp"
#include <sdlpp/sdlpp.hpp>

class Fruit : public Obj
{
public:
  Fruit(sdl::Renderer &);
  auto draw(Canvas &) -> void override;
  auto eat() -> void;

private:
  std::reference_wrapper<sdl::Renderer> r;
  sdl::Texture sprite;

public:
  int x;
  int y;
};
