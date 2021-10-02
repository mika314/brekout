#pragma once
#include "canvas.hpp"
#include "scene.hpp"
#include "world.hpp"
#include <functional>
#include <sdlpp/sdlpp.hpp>

class Audio;

namespace sdl
{
  class Renderer;
}

class TitleScreen3 : public Scene
{
public:
  TitleScreen3(sdl::Renderer &, Audio &);
  auto loopOnce() -> std::unique_ptr<Scene>;

private:
  sdl::EventHandler e;
  World world;
  std::reference_wrapper<Audio> audio;
  std::reference_wrapper<sdl::Renderer> r;
  Canvas canvas;
  uint32_t t0;
  sdl::Texture bg;
  std::unique_ptr<Scene> newScene = nullptr;
};
