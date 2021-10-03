#include "sprite.hpp"
#include "boot_screen.bmp.gen.hpp"
#include "check_online.bmp.gen.hpp"
#include "close.bmp.gen.hpp"
#include "crash.bmp.gen.hpp"
#include "font.bmp.gen.hpp"
#include "fruit.bmp.gen.hpp"
#include "game_field.bmp.gen.hpp"
#include "issue_fixed.bmp.gen.hpp"
#include "issue_fixed_2.bmp.gen.hpp"
#include "issue_fixed_3.bmp.gen.hpp"
#include "issue_fixed_4.bmp.gen.hpp"
#include "loading_00.bmp.gen.hpp"
#include "loading_01.bmp.gen.hpp"
#include "loading_02.bmp.gen.hpp"
#include "loading_03.bmp.gen.hpp"
#include "loading_04.bmp.gen.hpp"
#include "loading_05.bmp.gen.hpp"
#include "loading_06.bmp.gen.hpp"
#include "loading_07.bmp.gen.hpp"
#include "loading_08.bmp.gen.hpp"
#include "loading_09.bmp.gen.hpp"
#include "loading_10.bmp.gen.hpp"
#include "loading_11.bmp.gen.hpp"
#include "loading_12.bmp.gen.hpp"
#include "loading_13.bmp.gen.hpp"
#include "loading_14.bmp.gen.hpp"
#include "loading_15.bmp.gen.hpp"
#include "loading_16.bmp.gen.hpp"
#include "loading_17.bmp.gen.hpp"
#include "play_button.bmp.gen.hpp"
#include "snake_01.bmp.gen.hpp"
#include "snake_02.bmp.gen.hpp"
#include "snake_03.bmp.gen.hpp"
#include "snake_04.bmp.gen.hpp"
#include "snake_05.bmp.gen.hpp"
#include "snake_06.bmp.gen.hpp"
#include "snake_07.bmp.gen.hpp"
#include "snake_08.bmp.gen.hpp"
#include "snake_09.bmp.gen.hpp"
#include "snake_10.bmp.gen.hpp"
#include "snake_11.bmp.gen.hpp"
#include "snake_12.bmp.gen.hpp"
#include "snake_13.bmp.gen.hpp"
#include "snake_14.bmp.gen.hpp"
#include "snekout.bmp.gen.hpp"
#include "title_screen.bmp.gen.hpp"
#include "ver_2.bmp.gen.hpp"
#include "ver_3.bmp.gen.hpp"
#include "ver_b.bmp.gen.hpp"
#include "ver_r.bmp.gen.hpp"

auto loadSprite(unsigned char *buf, unsigned len) -> SDL_Surface *
{
  SDL_RWops *src = SDL_RWFromConstMem(buf, len);
  return SDL_LoadBMP_RW(src, 1);
}
