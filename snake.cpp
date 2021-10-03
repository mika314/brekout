#include "snake.hpp"
#include "audio.hpp"
#include "canvas.hpp"
#include "sprite.hpp"

Snake::Snake(int n, sdl::Renderer &r, Audio &audio)
  : n(n),
    audio(audio),
    r(r),
    bodyBL(r.get(), LOAD_SPRITE(snake_08)),
    bodyBR(r.get(), LOAD_SPRITE(snake_04)),
    bodyLR(r.get(), LOAD_SPRITE(snake_09)),
    bodyTB(r.get(), LOAD_SPRITE(snake_07)),
    bodyTL(r.get(), LOAD_SPRITE(snake_14)),
    bodyTR(r.get(), LOAD_SPRITE(snake_13)),
    headB(r.get(), LOAD_SPRITE(snake_12)),
    headL(r.get(), LOAD_SPRITE(snake_11)),
    headR(r.get(), LOAD_SPRITE(snake_05)),
    headT(r.get(), LOAD_SPRITE(snake_06)),
    tailB(r.get(), LOAD_SPRITE(snake_03)),
    tailL(r.get(), LOAD_SPRITE(snake_02)),
    tailR(r.get(), LOAD_SPRITE(snake_10)),
    tailT(r.get(), LOAD_SPRITE(snake_01))
{
  snake.push_front(Dir::d);
}

auto Snake::draw(Canvas &c) -> void
{
  if (snake.empty())
    return;
  const int dx[] = {0, -1, 0, 1};
  const int dy[] = {-1, 0, 1, 0};
  auto x = headX;
  auto y = headY;
  switch (snake[0])
  {
  case Dir::u: c.draw(headT, x * 16, y * 16, 16, 16); break;
  case Dir::r: c.draw(headR, x * 16, y * 16, 16, 16); break;
  case Dir::d: c.draw(headB, x * 16, y * 16, 16, 16); break;
  case Dir::l: c.draw(headL, x * 16, y * 16, 16, 16); break;
  }

  for (size_t i = 0; i < snake.size() - 1; ++i)
  {
    x -= dx[static_cast<size_t>(snake[i])];
    y -= dy[static_cast<size_t>(snake[i])];

    if (n >= 3 && x == headX && y == headY)
    {
      headX = -100;
    }
    switch (static_cast<int>(snake[i]) + static_cast<int>(snake[i + 1]) * 4)
    {
    case 3 + 4 * 2:
    case 0 + 4 * 1: c.draw(bodyTR, x * 16, y * 16, 16, 16); break;
    case 1 + 4 * 2:
    case 0 + 4 * 3: c.draw(bodyTL, x * 16, y * 16, 16, 16); break;
    case 1 + 4 * 1:
    case 3 + 4 * 3: c.draw(bodyLR, x * 16, y * 16, 16, 16); break;
    case 0 + 4 * 0:
    case 2 + 4 * 2: c.draw(bodyTB, x * 16, y * 16, 16, 16); break;
    case 3 + 4 * 0:
    case 2 + 4 * 1: c.draw(bodyBR, x * 16, y * 16, 16, 16); break;
    case 1 + 4 * 0:
    case 2 + 4 * 3: c.draw(bodyBL, x * 16, y * 16, 16, 16); break;
    }
  }

  x -= dx[static_cast<size_t>(snake.back())];
  y -= dy[static_cast<size_t>(snake.back())];
  switch (snake.back())
  {
  case Dir::u: c.draw(tailT, x * 16, y * 16, 16, 16); break;
  case Dir::r: c.draw(tailR, x * 16, y * 16, 16, 16); break;
  case Dir::d: c.draw(tailB, x * 16, y * 16, 16, 16); break;
  case Dir::l: c.draw(tailL, x * 16, y * 16, 16, 16); break;
  }
}

auto Snake::tick(float dt) -> void
{
  acc += dt;
  gameTime += dt;
  const auto speed = [n = n, gameTime = gameTime]() {
    switch (n)
    {
    case 1: return 0.36f * (sinf(0.001f * SDL_GetTicks()) + 1.1f);
    case 2: return std::max(0.001f, 0.18f - gameTime * 0.005f);
    case 3:
    default: return std::max(0.01f, 0.18f - gameTime * 0.001f);
    }
  }();
  while (acc > speed)
  {
    acc -= speed;
    snake.push_front(curDir);
    lastDir = curDir;
    if (speed > 0.001f)
      audio.get().PLAY(tick, .02f, 0);
    if (fruits == 0)
      snake.pop_back();
    else
    {
      --fruits;
      audio.get().PLAY(bite, 1, 0);
    }
    const int dx[] = {0, -1, 0, 1};
    const int dy[] = {-1, 0, 1, 0};
    headX += dx[static_cast<size_t>(curDir)];
    headY += dy[static_cast<size_t>(curDir)];
  }
  if (n == 1 && gameTime > 20)
    headX = -100;
}

auto Snake::move(Dir val) -> void
{
  if (n >= 3)
  {
    if ((val == Dir::r || val == Dir::l) && (lastDir == Dir::r || lastDir == Dir::l))
      return;
    if ((val == Dir::u || val == Dir::d) && (lastDir == Dir::u || lastDir == Dir::d))
      return;
  }
  else
  {
    if ((val == Dir::r || val == Dir::l) && (curDir == Dir::r || curDir == Dir::l))
      return;
    if ((val == Dir::u || val == Dir::d) && (curDir == Dir::u || curDir == Dir::d))
      return;
  }
  curDir = val;
}

auto Snake::eat() -> void
{
  ++fruits;
}
