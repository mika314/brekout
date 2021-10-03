#include "title_screen.hpp"
#include "audio.hpp"
#include "booting.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "loading.hpp"
#include "loading_screen.hpp"
#include "log/log.hpp"
#include "sprite.hpp"
#include "title_screen.hpp"
#include <log/log.hpp>

TitleScreen::TitleScreen(int n, sdl::Renderer &r, Audio &audio)
  : n(n),
    audio(audio),
    r(r),
    canvas(r),
    t0(SDL_GetTicks()),
    bg(r.get(), LOAD_SPRITE(title_screen)),
    playButton([&]() -> Button & {
      switch (n)
      {
      case 1:
        return world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, [this, &r, &audio]() {
          audio.PLAY(crash, 1, 0);
          world.newObj<Button>(r, LOAD_SPRITE(crash), 100, 100, 516, 256, []() {});
          world.newObj<Button>(
            r, LOAD_SPRITE(check_online), 130, 230, 371, 18, [this, &r, &audio]() { newScene = std::make_unique<TitleScreen>(2, r, audio); });
          world.newObj<Button>(
            r, LOAD_SPRITE(close), 130, 255, 155, 18, [this, &r, &audio]() { newScene = std::make_unique<TitleScreen>(2, r, audio); });
        });

      case 2:
      default: return world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, []() {});
      case 3:
        return world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, [this, &r, &audio]() {
          newScene = std::make_unique<LoadingScreen>(1, r, audio);
        });
      case 4: return world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, []() {});
      case 5:
        return world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, [this, &r, &audio]() {
          newScene = std::make_unique<LoadingScreen>(2, r, audio);
        });
      case 6:
        return world.newObj<Button>(r, LOAD_SPRITE(issue_fixed_3), (ScreenWidth - 446) / 2, (ScreenHeight - 349) / 2, 446, 349, [this, &r, &audio]() {
          newScene = std::make_unique<Booting>(4, r, audio);
        });
      case 7:
        return world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, [this, &r, &audio]() {
          newScene = std::make_unique<LoadingScreen>(3, r, audio);
        });
      case 8:
        return world.newObj<Button>(r, LOAD_SPRITE(issue_fixed_4), (ScreenWidth - 526) / 2, (ScreenHeight - 352) / 2, 526, 352, [this, &r, &audio]() {
          newScene = std::make_unique<Booting>(5, r, audio);
        });
      case 9:
        return world.newObj<Button>(r, LOAD_SPRITE(play_button), (ScreenWidth - 200) / 2, 450, 200, 100, [this, &r, &audio]() {
          newScene = std::make_unique<LoadingScreen>(4, r, audio);
        });
      }
    }()),
    loading([&]() -> Loading * {
      switch (n)
      {
      case 2:
      case 4: return &world.newObj<Loading>(r, (ScreenWidth - 300) / 2, (ScreenHeight - 300) / 2); break;
      }
      return nullptr;
    }())
{
  LOG("Title Screen:", n);
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.regEvents(e);
  switch (n)
  {
  case 3:
  case 4: world.newObj<Button>(r, LOAD_SPRITE(ver_b), ScreenWidth - 60, ScreenHeight - 90, 56, 80, []() {}); break;
  case 5:
  case 6: world.newObj<Button>(r, LOAD_SPRITE(ver_r), ScreenWidth - 60, ScreenHeight - 90, 56, 80, []() {}); break;
  case 7:
  case 8: world.newObj<Button>(r, LOAD_SPRITE(ver_2), ScreenWidth - 110, ScreenHeight - 90, 106, 80, []() {}); break;
  case 9:
    world.newObj<Button>(r, LOAD_SPRITE(ver_3), ScreenWidth - 110, ScreenHeight - 90, 106, 80, []() {});
    world.newObj<Button>(r, LOAD_SPRITE(snekout), 0, 0, 1280, 720, []() {});
    break;
  }
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
  wait += dt;
  t0 = t1;
  world.housekeeping();
  switch (n)
  {
  case 2:
    if (wait > 5 && !didShowDialog)
    {
      didShowDialog = true;
      loading->kill();
      audio.get().PLAY(crash, 1, 0);
      world.newObj<Button>(r, LOAD_SPRITE(issue_fixed), (ScreenWidth - 507) / 2, (ScreenHeight - 238) / 2, 507, 238, [this]() {
        newScene = std::make_unique<Booting>(2, r.get(), audio.get());
      });
    }
    break;
  case 4:
    if (wait > 5 && !didShowDialog)
    {
      didShowDialog = true;
      loading->kill();
      audio.get().PLAY(crash, 1, 0);
      world.newObj<Button>(r, LOAD_SPRITE(issue_fixed_2), (ScreenWidth - 507) / 2, (ScreenHeight - 238) / 2, 507, 238, [this]() {
        newScene = std::make_unique<Booting>(3, r.get(), audio.get());
      });
    }
    break;
  }
  return std::move(newScene);
}
