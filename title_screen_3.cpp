#include "title_screen_3.hpp"
#include "audio.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "loading.hpp"
#include "loading_screen.hpp"
#include "sprite.hpp"
#include <log/log.hpp>

TitleScreen3::TitleScreen3(sdl::Renderer &r, Audio &audio) : audio(audio), r(r), canvas(r), t0(SDL_GetTicks()), bg(r.get(), LOAD_SPRITE(title_screen))
{
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, [this, &r, &audio]() {
    newScene = std::make_unique<LoadingScreen>(r, audio);
  });
  world.regEvents(e);
  world.newObj<Button>(r, LOAD_SPRITE(ver_b), ScreenWidth - 60, ScreenHeight - 90, 56, 80, []() {});
}

auto TitleScreen3::loopOnce() -> std::unique_ptr<Scene>
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
