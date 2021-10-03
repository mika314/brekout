#pragma once
#include "obj.hpp"
#include <deque>
#include <functional>
#include <sdlpp/sdlpp.hpp>

enum class Dir { u, l, d, r };

class Snake : public Obj
{
public:
  Snake(int n, sdl::Renderer &, class Audio &);
  auto draw(Canvas &) -> void override;
  auto tick(float dt) -> void override;
  auto move(Dir) -> void;
  auto eat() -> void;

  int headX = 10;
  int headY = 10;

private:
  int n;
  std::deque<Dir> snake;
  float acc = 0;
  Dir curDir = Dir::d;
  int fruits = 0;
  float gameTime = 0.f;
  std::reference_wrapper<class Audio> audio;
  std::reference_wrapper<sdl::Renderer> r;
  sdl::Texture bodyBL;
  sdl::Texture bodyBR;
  sdl::Texture bodyLR;
  sdl::Texture bodyTB;
  sdl::Texture bodyTL;
  sdl::Texture bodyTR;
  sdl::Texture headB;
  sdl::Texture headL;
  sdl::Texture headR;
  sdl::Texture headT;
  sdl::Texture tailB;
  sdl::Texture tailL;
  sdl::Texture tailR;
  sdl::Texture tailT;
};
