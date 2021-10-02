#pragma once
#include <memory>

class Scene
{
public:
  virtual ~Scene() = default;
  virtual auto loopOnce() -> std::unique_ptr<Scene> = 0;
  bool done = false;
};
