#include "title_screen_6.hpp"
#include "audio.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "loading.hpp"
#include "loading_screen.hpp"
#include "sprite.hpp"
#include <log/log.hpp>

TitleScreen6::TitleScreen6(sdl::Renderer &r, Audio &audio) : audio(audio), r(r), canvas(r), t0(SDL_GetTicks()), bg(r.get(), LOAD_SPRITE(title_screen))
{
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.newObj<Button>(r, LOAD_SPRITE(issue_fixed_3), (ScreenWidth - 446) / 2, (ScreenHeight - 349) / 2, 446, 349, [this, &r, &audio]() {
    newScene = std::make_unique<LoadingScreen>(3, r, audio);
  });
  world.regEvents(e);
  world.newObj<Button>(r, LOAD_SPRITE(ver_2), ScreenWidth - 110, ScreenHeight - 90, 106, 80, []() {});
}

auto TitleScreen6::loopOnce() -> std::unique_ptr<Scene>
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
  t0 = t1;
  world.housekeeping();
  return std::move(newScene);
}
