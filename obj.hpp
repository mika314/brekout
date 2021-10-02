#pragma once

enum class Btn { l, m, r };

class Obj
{
public:
  Obj(float x = 0, float y = 0) : x(x), y(y) {}
  auto getIsAlive() const -> bool { return isAlive; }
  auto getX() const { return x; }
  auto getY() const { return y; }
  virtual auto draw(class Canvas &) -> void = 0;
  virtual auto tick(float /*dt*/) -> void {}
  virtual auto mouseMove(int /*x*/, int /*y*/) -> void {}
  virtual auto mouseDown(Btn, int /*x*/, int /*y*/) -> void {}
  virtual auto mouseUp(Btn, int /*x*/, int /*y*/) -> void {}
  virtual ~Obj() = default;
  auto kill() { isAlive = false; }

protected:
  float x;
  float y;
  bool isAlive = true;
};
