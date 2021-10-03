#pragma once
#include <array>
#include <deque>
#include <sdlpp/sdlpp.hpp>
#include <unordered_map>

#define PLAY(name, vol, pan) play(snd_##name##_wav, snd_##name##_wav_len, (vol), (pan))

struct Wav
{
  SDL_AudioSpec spec;
  Uint8 *buf;
  Uint32 len;
};

class Audio
{
public:
  Audio();
  ~Audio();
  auto play(unsigned char *, unsigned, float vol, float pan) -> void;

private:
  SDL_AudioSpec want;
  SDL_AudioSpec have;
  sdl::Audio audio;
  std::deque<std::array<int16_t, 2>> playBuf;
  std::unordered_map<unsigned char *, Wav> cache;
};

#define DEF_SND(x)                      \
  extern unsigned char snd_##x##_wav[]; \
  extern unsigned int snd_##x##_wav_len

DEF_SND(crash);
DEF_SND(booting);
DEF_SND(booting_short);
DEF_SND(tick);
DEF_SND(bite);

#undef DEF_SND
