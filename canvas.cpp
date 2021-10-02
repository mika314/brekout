#include "canvas.hpp"
#include "consts.hpp"
#include "sprite.hpp"
#include <array>
#include <sdlpp/sdlpp.hpp>

Canvas::Canvas(sdl::Renderer &r) : r(r), font(r.get(), LOAD_SPRITE(font)) {}

auto Canvas::drawRect(float x, float y, float w, float h) -> void
{
  const auto rect =
    SDL_Rect{static_cast<int>(x - offsetX), static_cast<int>(y - offsetY), std::max(1, static_cast<int>(w)), std::max(1, static_cast<int>(h))};
  if (rect.x > ScreenWidth)
    return;
  if (rect.y > ScreenHeight)
    return;
  if (rect.x + rect.w < 0)
    return;
  if (rect.y + rect.h < 0)
    return;
  r.get().fillRect(&rect);
}

auto Canvas::drawRectHud(float x, float y, float w, float h) -> void
{
  const auto rect = SDL_Rect{static_cast<int>(x), static_cast<int>(y), std::max(1, static_cast<int>(w)), std::max(1, static_cast<int>(h))};
  r.get().fillRect(&rect);
}

auto Canvas::draw(const sdl::Texture &tex, float x, float y, float w, float h) -> void
{
  const auto rect =
    SDL_Rect{static_cast<int>(x - offsetX), static_cast<int>(y - offsetY), std::max(1, static_cast<int>(w)), std::max(1, static_cast<int>(h))};

  if (rect.x > ScreenWidth)
    return;
  if (rect.y > ScreenHeight)
    return;
  if (rect.x + rect.w < 0)
    return;
  if (rect.y + rect.h < 0)
    return;
  r.get().copy(const_cast<SDL_Texture *>(tex.get()), nullptr, &rect);
}

static std::array s = {0,    14,   32,   47,   75,   104,  144,  179,  187,  200,  213,  234,  200,  270,  285,  294,  310,  337,  352,  375,
                       405,  430,  462,  487,  509,  535,  561,  571,  581,  607,  632,  659,  686,  740,  773,  806,  846,  881,  912,  938,
                       978,  1006, 1024, 1053, 1087, 1116, 1157, 1185, 1226, 1254, 1294, 1324, 1357, 1385, 1418, 1450, 1495, 1527, 1556, 1587,
                       1600, 1616, 1628, 1647, 1677, 1691, 1723, 1753, 1780, 1808, 1839, 1860, 1890, 1916, 1934, 1952, 1980, 1987, 2027, 2056,
                       2084, 2110, 2137, 2154, 2171, 2185, 2212, 2236, 2274, 2299, 2323, 2342, 2362, 2371, 2392, 2418};
auto Canvas::drawTextHud(const std::string &text, float x, float y) -> void
{
  float pos = x;
  for (auto ch : text)
  {
    if (ch >= ' ' && ch < static_cast<char>(' ' + s.size() - 1))
    {
      auto w = s[ch - ' ' + 1] - s[ch - ' '];
      const auto src = SDL_Rect{s[ch - ' '], 0, w, 64};
      const auto dest = SDL_Rect{static_cast<int>(pos), static_cast<int>(y), w, 64};
      r.get().copy(font.get(), &src, &dest);
      pos += w;
    }
  }
}
auto Canvas::drawTextHudC(const std::string &text, float y) -> void
{
  float pos = 0;
  for (auto ch : text)
  {
    if (ch >= ' ' && ch < static_cast<char>(' ' + s.size() - 1))
    {
      auto w = s[ch - ' ' + 1] - s[ch - ' '];
      pos += w;
    }
  }
  drawTextHud(text, (ScreenWidth - pos) / 2, y);
}

auto Canvas::drawText(const std::string &text, float x, float y) -> void
{
  float pos = x - offsetX;
  const auto iy = static_cast<int>(y - offsetY);
  if (iy > ScreenHeight)
    return;
  if (iy + 64 < 0)
    return;
  for (auto ch : text)
  {
    if (pos > ScreenWidth)
      return;
    if (ch >= ' ' && ch < static_cast<char>(' ' + s.size() - 1))
    {
      auto w = s[ch - ' ' + 1] - s[ch - ' '];
      const auto src = SDL_Rect{s[ch - ' '], 0, w, 64};
      const auto dest = SDL_Rect{static_cast<int>(pos), iy, w, 64};

      if (pos + w < 0)
        continue;

      r.get().copy(font.get(), &src, &dest);
      pos += w;
    }
  }
}

auto Canvas::setColor(int red, int green, int blue, int alpha) -> void
{
  r.get().setDrawColor(red, green, blue, alpha);
}

auto Canvas::drawPoint(std::vector<SDL_Rect> &points, float x, float y) -> void
{
  auto ix = static_cast<int>(x - offsetX);
  auto iy = static_cast<int>(y - offsetY);
  if (ix > ScreenWidth)
    return;
  if (iy > ScreenHeight)
    return;
  if (ix < 0)
    return;
  if (iy < 0)
    return;
  points.push_back({ix - 1, iy - 1, 3, 3});
}

auto Canvas::drawWhitePoint(float x, float y) -> void
{
  drawPoint(white, x, y);
}

auto Canvas::drawGreenPoint(float x, float y) -> void
{
  drawPoint(green, x, y);
}

auto Canvas::drawBluePoint(float x, float y) -> void
{
  drawPoint(blue, x, y);
}

auto Canvas::drawPurplePoint(float x, float y) -> void
{
  drawPoint(purple, x, y);
}

auto Canvas::drawGoldPoint(float x, float y) -> void
{
  drawPoint(gold, x, y);
}

auto Canvas::present() -> void
{

  if (!white.empty())
  {
    setColor(0xff, 0xff, 0xff);
    r.get().drawRects(white.data(), white.size());
  }
  if (!green.empty())
  {
    setColor(0x00, 0xff, 0x00);
    r.get().drawRects(green.data(), green.size());
  }

  if (!blue.empty())
  {
    setColor(0x00, 0x00, 0xff);
    r.get().drawRects(blue.data(), blue.size());
  }
  if (!purple.empty())
  {
    setColor(0xff, 0x00, 0xff);
    r.get().drawRects(purple.data(), purple.size());
  }

  if (!gold.empty())
  {
    setColor(0xff, 0xff, 0x00);
    r.get().drawRects(gold.data(), gold.size());
  }

  r.get().present();
  white.clear();
  green.clear();
  blue.clear();
  purple.clear();
  gold.clear();
}
