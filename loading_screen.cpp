#include "loading_screen.hpp"
#include "audio.hpp"
#include "booting_2.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "loading.hpp"
#include "sprite.hpp"
#include "title_screen_4.hpp"
#include <log/log.hpp>

LoadingScreen::LoadingScreen(sdl::Renderer &r, Audio &audio)
  : audio(audio),
    r(r),
    canvas(r),
    t0(SDL_GetTicks()),
    bg(r.get(), LOAD_SPRITE(title_screen))
{
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.regEvents(e);
  world.newObj<Button>(r, LOAD_SPRITE(ver_b), ScreenWidth - 60, ScreenHeight - 90, 56, 80, []() {});
}

auto LoadingScreen::loopOnce() -> std::unique_ptr<Scene>
{
  while (e.poll()) {}
  r.get().setDrawColor(0x00, 0x00, 0x00, 0xff);
  r.get().clear();
  canvas.draw(bg, 0, 0, ScreenWidth, ScreenHeight);
  world.draw(canvas);
  canvas.setColor(0, 255, 0);
  if (wait < 5.8)
    canvas.drawRect(0, ScreenHeight - 8, (wait + sin(wait)) * ScreenWidth / 6, 8);
  else if (wait < 9)
    canvas.drawRect(0, ScreenHeight - 8, 5.8f * ScreenWidth / 6, 8);
  else if (wait < 12)
    canvas.drawRect(0, ScreenHeight - 8, (18 - wait) * ScreenWidth / 9, 8);
  canvas.present();
  const auto t1 = SDL_GetTicks();
  const auto dt = 0.001f * (t1 - t0);
  world.tick(dt);
  wait += dt;
  t0 = t1;
  world.housekeeping();
  if (wait > 12 && !didShowDialog)
  {
    didShowDialog = true;
    audio.get().PLAY(crash, 1, 0);
    world.newObj<Button>(r, LOAD_SPRITE(crash), 100, 100, 516, 256, []() {});
    world.newObj<Button>(r, LOAD_SPRITE(check_online), 130, 230, 371, 18, [this]() { newScene = std::make_unique<TitleScreen4>(r, audio); });
    world.newObj<Button>(r, LOAD_SPRITE(close), 130, 255, 155, 18, [this]() { newScene = std::make_unique<TitleScreen4>(r, audio); });
  }
  return std::move(newScene);
}
