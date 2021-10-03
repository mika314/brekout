#include "game_play_screen.hpp"
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

GamePlayScreen::GamePlayScreen(sdl::Renderer &r, Audio &audio)
  : audio(audio), r(r), canvas(r), t0(SDL_GetTicks()), bg(r.get(), LOAD_SPRITE(game_field)), snake(world.newObj<Snake>(r, audio))
{
  e.quit = [&done = done](const SDL_QuitEvent &) { done = true; };
  e.keyDown = [&snake = snake, this, &audio = audio, &r = r](const SDL_KeyboardEvent &e) {
    switch (e.keysym.sym)
    {
    case SDLK_UP:
    case SDLK_w: snake.get().move(Dir::u); break;
    case SDLK_DOWN:
    case SDLK_s: snake.get().move(Dir::d); break;
    case SDLK_LEFT:
    case SDLK_d: snake.get().move(Dir::r); break;
    case SDLK_RIGHT:
    case SDLK_a: snake.get().move(Dir::l); break;
    case SDLK_ESCAPE: {
      audio.PLAY(crash, 1, 0);
      if (!isCrashed)
      {
        world.newObj<Button>(r, LOAD_SPRITE(crash), 100, 100, 516, 256, []() {});
        world.newObj<Button>(
          r, LOAD_SPRITE(check_online), 130, 230, 371, 18, [this, &r, &audio]() { newScene = std::make_unique<TitleScreen>(6, r, audio); });
        world.newObj<Button>(r, LOAD_SPRITE(close), 130, 255, 155, 18, [this, &r, &audio]() { newScene = std::make_unique<TitleScreen>(6, r, audio); });
      }
      isCrashed = true;
      break;
    }
    }
  };

  fruits.emplace_back(world.newObj<Fruit>(r));
  world.regEvents(e);
}

auto GamePlayScreen::loopOnce() -> std::unique_ptr<Scene>
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
  for (auto &fruit : fruits)
  {
    if (snake.get().headX == fruit.get().x && snake.get().headY == fruit.get().y)
    {
      snake.get().eat();
      fruit.get().eat();
      ++score;
    }
  }

  if (snake.get().headX < 0 || snake.get().headY < 0 || snake.get().headX > 1280 / 16 || snake.get().headY > 720 / 16)
  {

    if (!isCrashed)
    {
      audio.get().PLAY(crash, 1, 0);
      world.newObj<Button>(r, LOAD_SPRITE(crash), 100, 100, 516, 256, []() {});
      world.newObj<Button>(r, LOAD_SPRITE(check_online), 130, 230, 371, 18, [this]() { newScene = std::make_unique<TitleScreen>(6, r, audio); });
      world.newObj<Button>(r, LOAD_SPRITE(close), 130, 255, 155, 18, [this]() { newScene = std::make_unique<TitleScreen>(6, r, audio); });
    }

    if (rand() % 100 == 0)
      audio.get().PLAY(crash, 1, 0);
    isCrashed = true;
  }

  auto freq = static_cast<int>(1000.f * (sinf(0.0011f * SDL_GetTicks()) + 1.f)) + 10;
  if (rand() % freq == 0)
  {
    ++score;
    snake.get().eat();
    audio.get().PLAY(bite, 2, 0);
    fruits.emplace_back(world.newObj<Fruit>(r));
  }
  world.tick(dt);
  t0 = t1;
  world.housekeeping();
  return std::move(newScene);
}
