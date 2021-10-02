#include "title_screen_2.hpp"
#include "audio.hpp"
#include "booting_2.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "loading.hpp"
#include "sprite.hpp"
#include "title_screen.hpp"
#include <log/log.hpp>

TitleScreen2::TitleScreen2(sdl::Renderer &r, Audio &audio)
  : audio(audio),
    r(r),
    canvas(r),
    t0(SDL_GetTicks()),
    bg(r.get(), LOAD_SPRITE(title_screen)),
    playButton(world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, []() {})),
    loading(world.newObj<Loading>(r, (ScreenWidth - 300) / 2, (ScreenHeight - 300) / 2))
{
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.regEvents(e);
}

auto TitleScreen2::loopOnce() -> std::unique_ptr<Scene>
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
    didShowDialog = true;
    loading.get().kill();
    audio.get().PLAY(crash, 1, 0);
    world.newObj<Button>(r, LOAD_SPRITE(issue_fixed), (ScreenWidth - 507) / 2, (ScreenHeight - 238) / 2, 507, 238, [this]() {
      newScene = std::make_unique<Booting2>(r.get(), audio.get());
    });
  }
  return std::move(newScene);
}
