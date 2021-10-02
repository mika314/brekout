#include "loading_screen_2.hpp"
#include "audio.hpp"
#include "booting_2.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "loading.hpp"
#include "sprite.hpp"
#include "title_screen_4.hpp"
#include <log/log.hpp>

LoadingScreen2::LoadingScreen2(sdl::Renderer &r, Audio &audio)
  : audio(audio),
    r(r),
    canvas(r),
    t0(SDL_GetTicks()),
    bg(r.get(), LOAD_SPRITE(title_screen))
{
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.regEvents(e);
  world.newObj<Button>(r, LOAD_SPRITE(ver_r), ScreenWidth - 60, ScreenHeight - 90, 56, 80, []() {});
}

auto LoadingScreen2::loopOnce() -> std::unique_ptr<Scene>
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
  else
    canvas.drawRect(0, ScreenHeight - 8, ScreenWidth, 8);
  canvas.present();
  const auto t1 = SDL_GetTicks();
  const auto dt = 0.001f * (t1 - t0);
  world.tick(dt);
  wait += dt;
  t0 = t1;
  world.housekeeping();
  return std::move(newScene);
}