#include "booting_3.hpp"
#include "audio.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "loading.hpp"
#include "sprite.hpp"
#include "title_screen.hpp"
#include <log/log.hpp>

Booting3::Booting3(sdl::Renderer &r, Audio &audio) : audio(audio), r(r), canvas(r), t0(SDL_GetTicks()), bg(r.get(), LOAD_SPRITE(boot_screen))
{
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.regEvents(e);
  audio.PLAY(booting_short, 0.25f, 0);
}

auto Booting3::loopOnce() -> std::unique_ptr<Scene>
{
  while (e.poll()) {}
  r.get().setDrawColor(0x00, 0x00, 0x00, 0xff);
  r.get().clear();
  canvas.draw(bg, 0, 0, ScreenWidth, ScreenHeight);
  world.draw(canvas);
  canvas.present();
  const auto t1 = SDL_GetTicks();
  const auto dt = 0.001f * (t1 - t0);
  world.tick(dt);
  wait += dt;
  t0 = t1;
  world.housekeeping();
  if (wait > 5 && !didShowDialog)
  {
    newScene = std::make_unique<TitleScreen>(5, r.get(), audio.get());
  }
  return std::move(newScene);
}
