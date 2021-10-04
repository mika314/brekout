#include "score_screen.hpp"
#include "audio.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "consts.hpp"
#include "fruit.hpp"
#include "loading.hpp"
#include "snake.hpp"
#include "sprite.hpp"
#include "title_screen.hpp"
#include <log/log.hpp>

ScoreScreen::ScoreScreen(int score, sdl::Renderer &r, Audio &audio)
  : score(score), audio(audio), r(r), canvas(r), t0(SDL_GetTicks()), bg(r.get(), LOAD_SPRITE(game_field))
{
  LOG("Score Screen:", score);
  audio.PLAY(intro, 0.2, 0);
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.regEvents(e);
}

auto ScoreScreen::loopOnce() -> std::unique_ptr<Scene>
{
  while (e.poll()) {}
  r.get().setDrawColor(0x00, 0x00, 0x00, 0xff);
  r.get().clear();
  canvas.draw(bg, 0, 0, ScreenWidth, ScreenHeight);
  {
    std::ostringstream st;
    st << "Score: " << score;
    canvas.drawTextHud(st.str(), 0, 0);
  }

  int y = ScreenHeight - 32 * std::min(20.f, time);
  for (auto line :
       {"Game Over", "Your score: -4294967296", "", "LD49 Submission", "Theme: Unstable", "", "Thank you for playing my game", "", "-- Mika"})
  {
    canvas.drawTextHudC(line, y);
    y += 64;
  }

  world.draw(canvas);

  if (time > 20.f && !isCrashed)
  {
    if (!isCrashed)
    {
      audio.get().PLAY(crash, 1, 0);
      world.newObj<Button>(r, audio, LOAD_SPRITE(last_crash), 100, 100, 516, 256);
      world.newObj<Button>(r, audio, LOAD_SPRITE(check_online), LOAD_SPRITE(check_online_down), 130, 230, 371, 18, [this]() {
        audio.get().stopAll();
        newScene = std::make_unique<TitleScreen>(1, r, audio);
      });
      world.newObj<Button>(r, audio, LOAD_SPRITE(close), LOAD_SPRITE(close_down), 130, 255, 155, 18, [this]() {
        audio.get().stopAll();
        newScene = std::make_unique<TitleScreen>(9, r, audio);
      });
    }
    isCrashed = true;
  }

  canvas.present();
  const auto t1 = SDL_GetTicks();
  const auto dt = 0.001f * (t1 - t0);
  world.tick(dt);
  time += dt;
  t0 = t1;
  world.housekeeping();
  return std::move(newScene);
}
