#include "audio.hpp"
#include "consts.hpp"
#include "booting.hpp"
#include "game_play_screen.hpp"
#include <sdlpp/sdlpp.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static std::unique_ptr<Scene> scene;

int main()
{
  sdl::Init init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  sdl::Window w("Brek: out", 64, 126, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
  SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  sdl::Renderer r(w.get(), -1, 0);
  Audio audio;

  scene = std::make_unique<GamePlayScreen>(r, audio);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(
    [](void) -> void {
      if (auto s = scene->loopOnce())
        scene = std::move(s);
    },
    -1,
    1);
#else
  while (!scene->done)
  {
    if (auto s = scene->loopOnce())
      scene = std::move(s);
  }
#endif
}
