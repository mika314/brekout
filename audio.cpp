#include "audio.hpp"
#include "bite.wav.gen.hpp"
#include "booting.wav.gen.hpp"
#include "booting_short.wav.gen.hpp"
#include "click.wav.gen.hpp"
#include "crash.wav.gen.hpp"
#include "intro.wav.gen.hpp"
#include "tick.wav.gen.hpp"

Audio::Audio()
  : want([]() {
      SDL_AudioSpec want;
      want.freq = 44100;
      want.format = AUDIO_S16;
      want.channels = 2;
      want.samples = 2048;
      return want;
    }()),
    audio(nullptr, false, &want, &have, 0, [this](Uint8 *stream, int len) {
      auto out = reinterpret_cast<std::array<int16_t, 2> *>(stream);
      for (; len > 0; len -= sizeof(int16_t) * 2, ++out)
      {
        if (!playBuf.empty())
        {
          *out = playBuf.front();
          playBuf.pop_front();
        }
        else
          *out = {};
      }
    })
{
  audio.pause(false);
}

auto Audio::play(unsigned char *buf, unsigned len, float vol, float pan) -> void
{
  audio.lock();

  auto it = cache.find(buf);
  if (it == std::end(cache))
  {
    Wav wav;
    SDL_RWops *src = SDL_RWFromConstMem(buf, len);
    SDL_LoadWAV_RW(src, 1, &wav.spec, &wav.buf, &wav.len);
    auto tmp = cache.insert(std::make_pair(buf, wav));
    it = tmp.first;
  }
  const auto sz = it->second.len / sizeof(int16_t) + std::abs(pan) * 26;
  if (playBuf.size() < sz)
    playBuf.resize(sz);
  auto in = reinterpret_cast<int16_t *>(it->second.buf);
  auto wavLen = it->second.len;
  switch (it->second.spec.channels)
  {
  case 1:
    for (auto i = 0U; wavLen > 0U; wavLen -= sizeof(int16_t), ++in, ++i)
    {
      playBuf[i + static_cast<int>(pan > 0 ? std::abs(pan) * 26 : 0)][0] += (1 - pan) * vol * *in;
      playBuf[i + static_cast<int>(pan < 0 ? std::abs(pan) * 26 : 0)][1] += (pan + 1) * vol * *in;
    }
    break;
  case 2:
    for (auto i = 0U; wavLen > 0U; wavLen -= 2 * sizeof(int16_t), in += 2, ++i)
    {
      playBuf[i + static_cast<int>(pan > 0 ? std::abs(pan) * 26 : 0)][0] += (1 - pan) * vol * in[0];
      playBuf[i + static_cast<int>(pan < 0 ? std::abs(pan) * 26 : 0)][1] += (pan + 1) * vol * in[1];
    }
    break;
  }
  audio.unlock();
}

Audio::~Audio()
{
  for (auto &wav : cache)
    SDL_FreeWAV(wav.second.buf);
}

auto Audio::stopAll() -> void
{
  audio.lock();
  playBuf.resize(0);
  audio.unlock();
}
