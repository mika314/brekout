#pragma once
#include "obj.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

struct pair_hash
{
  inline std::size_t operator()(const std::pair<int, int> &v) const { return std::hash<int>{}(v.first * 1023 + v.second); }
};

namespace sdl
{
  class EventHandler;
}

class World
{
public:
  auto draw(Canvas &) -> void;
  auto getObjsN() const -> int;
  auto housekeeping() -> void;
  auto tick(float dt) -> void;

  template <typename T, typename... Args>
  auto newObj(Args &&...args) -> T &
  {
    return static_cast<T &>(*objs.emplace_back(std::make_unique<T>(std::forward<Args>(args)...)));
  }

  auto regEvents(sdl::EventHandler &) -> void;

private:
  std::vector<std::unique_ptr<Obj>> objs;
};
