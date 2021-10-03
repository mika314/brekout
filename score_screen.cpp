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
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  world.regEvents(e);
}

auto ScoreScreen::loopOnce() -> std::unique_ptr<Scene>
{
  while (e.poll()) {}
  r.get().setDrawColor(0x00, 0x00, 0x00, 0xff);
  r.get().clear();
  canvas.draw(bg, 0, 0, ScreenWidth, ScreenHeight);
  world.draw(canvas);
  {
    std::ostringstream st;
    st << "Score: " << score;
    canvas.drawTextHud(st.str(), 0, 0);
  }
  canvas.present();
  const auto t1 = SDL_GetTicks();
  const auto dt = 0.001f * (t1 - t0);
  world.tick(dt);
  t0 = t1;
  world.housekeeping();
  return std::move(newScene);
}
