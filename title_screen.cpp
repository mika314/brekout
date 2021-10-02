#include "title_screen.hpp"
#include "audio.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "loading.hpp"
#include "sprite.hpp"
#include "title_screen_2.hpp"
#include <log/log.hpp>

TitleScreen::TitleScreen(sdl::Renderer &r, Audio &audio) : audio(audio), r(r), canvas(r), t0(SDL_GetTicks()), bg(r.get(), LOAD_SPRITE(title_screen))
{
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, [this, &r, &audio]() {
    audio.PLAY(crash, 1, 0);
    world.newObj<Button>(r, LOAD_SPRITE(crash), 100, 100, 516, 256, []() {});
    world.newObj<Button>(
      r, LOAD_SPRITE(check_online), 130, 230, 371, 18, [this, &r, &audio]() { newScene = std::make_unique<TitleScreen2>(r, audio); });
    world.newObj<Button>(r, LOAD_SPRITE(close), 130, 255, 155, 18, [this, &r, &audio]() { newScene = std::make_unique<TitleScreen2>(r, audio); });
  });
  world.regEvents(e);
}

auto TitleScreen::loopOnce() -> std::unique_ptr<Scene>
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
