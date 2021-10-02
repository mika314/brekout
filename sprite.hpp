#pragma once
#include <sdlpp/sdlpp.hpp>

#define LOAD_SPRITE(name) loadSprite(sprite_##name##_bmp, sprite_##name##_bmp_len)

auto loadSprite(unsigned char *, unsigned) -> SDL_Surface *;

// clang-format off
extern unsigned char sprite_title_screen_bmp[];
extern unsigned      sprite_title_screen_bmp_len;
extern unsigned char sprite_font_bmp[];
extern unsigned      sprite_font_bmp_len;
extern unsigned char sprite_play_button_bmp[];
extern unsigned      sprite_play_button_bmp_len;
extern unsigned char sprite_crash_bmp[];
extern unsigned      sprite_crash_bmp_len;
extern unsigned char sprite_check_online_bmp[];
extern unsigned      sprite_check_online_bmp_len;
extern unsigned char sprite_close_bmp[];
extern unsigned      sprite_close_bmp_len;
extern unsigned char sprite_loading_00_bmp[];
extern unsigned      sprite_loading_00_bmp_len;
extern unsigned char sprite_loading_01_bmp[];
extern unsigned      sprite_loading_01_bmp_len;
extern unsigned char sprite_loading_02_bmp[];
extern unsigned      sprite_loading_02_bmp_len;
extern unsigned char sprite_loading_03_bmp[];
extern unsigned      sprite_loading_03_bmp_len;
extern unsigned char sprite_loading_04_bmp[];
extern unsigned      sprite_loading_04_bmp_len;
extern unsigned char sprite_loading_05_bmp[];
extern unsigned      sprite_loading_05_bmp_len;
extern unsigned char sprite_loading_06_bmp[];
extern unsigned      sprite_loading_06_bmp_len;
extern unsigned char sprite_loading_07_bmp[];
extern unsigned      sprite_loading_07_bmp_len;
extern unsigned char sprite_loading_08_bmp[];
extern unsigned      sprite_loading_08_bmp_len;
extern unsigned char sprite_loading_09_bmp[];
extern unsigned      sprite_loading_09_bmp_len;
extern unsigned char sprite_loading_10_bmp[];
extern unsigned      sprite_loading_10_bmp_len;
extern unsigned char sprite_loading_11_bmp[];
extern unsigned      sprite_loading_11_bmp_len;
extern unsigned char sprite_loading_12_bmp[];
extern unsigned      sprite_loading_12_bmp_len;
extern unsigned char sprite_loading_13_bmp[];
extern unsigned      sprite_loading_13_bmp_len;
extern unsigned char sprite_loading_14_bmp[];
extern unsigned      sprite_loading_14_bmp_len;
extern unsigned char sprite_loading_15_bmp[];
extern unsigned      sprite_loading_15_bmp_len;
extern unsigned char sprite_loading_16_bmp[];
extern unsigned      sprite_loading_16_bmp_len;
extern unsigned char sprite_loading_17_bmp[];
extern unsigned      sprite_loading_17_bmp_len;
extern unsigned char sprite_issue_fixed_bmp[];
extern unsigned      sprite_issue_fixed_bmp_len;
extern unsigned char sprite_issue_fixed_2_bmp[];
extern unsigned      sprite_issue_fixed_2_bmp_len;
extern unsigned char sprite_boot_screen_bmp[];
extern unsigned      sprite_boot_screen_bmp_len;
extern unsigned char sprite_ver_b_bmp[];
extern unsigned      sprite_ver_b_bmp_len;
extern unsigned char sprite_ver_r_bmp[];
extern unsigned      sprite_ver_r_bmp_len;
