#pragma once
#include <functional>
#include <sdlpp/sdlpp.hpp>
#include <vector>

class Canvas
{
public:
  Canvas(sdl::Renderer &r);
  auto draw(const sdl::Texture &, float x, float y, float w, float h) -> void;
  auto drawRect(float x, float y, float w, float h) -> void;
  auto drawRectHud(float x, float y, float w, float h) -> void;
  auto drawText(const std::string &, float x, float y) -> void;
  auto drawTextHud(const std::string &, float x, float y) -> void;
  auto drawTextHudC(const std::string &, float y) -> void;
  auto setColor(int, int, int, int = 0xff) -> void;
  auto drawWhitePoint(float x, float y) -> void;
  auto drawGreenPoint(float x, float y) -> void;
  auto drawBluePoint(float x, float y) -> void;
  auto drawPurplePoint(float x, float y) -> void;
  auto drawGoldPoint(float x, float y) -> void;
  auto present() -> void;

  float offsetX = 0;
  float offsetY = 0;

private:
  auto drawPoint(std::vector<SDL_Rect> &, float x, float y) -> void;

  std::reference_wrapper<sdl::Renderer> r;
  sdl::Texture font;
  std::vector<SDL_Rect> white;
  std::vector<SDL_Rect> green;
  std::vector<SDL_Rect> blue;
  std::vector<SDL_Rect> purple;
  std::vector<SDL_Rect> gold;
};
