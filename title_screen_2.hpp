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

class TitleScreen2 : public Scene
{
public:
  TitleScreen2(sdl::Renderer &, Audio &);
  auto loopOnce() -> std::unique_ptr<Scene>;

private:
  sdl::EventHandler e;
  World world;
  std::reference_wrapper<Audio> audio;
  std::reference_wrapper<sdl::Renderer> r;
  Canvas canvas;
  uint32_t t0;
  float wait = 0;
  bool didShowDialog = false;
  sdl::Texture bg;
  std::unique_ptr<Scene> newScene = nullptr;
  std::reference_wrapper<class Button> playButton;
  std::reference_wrapper<class Loading> loading;
};
