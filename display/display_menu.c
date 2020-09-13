/** @file   display_menu.c
    @author Narottam Royal， Hao Li
    @date   16 October 2018
*/

#include "display_menu.h"
#include "font5x7_1.h"
#include "tinygl.h"
#include <stdint.h>


void display_menu_clear()
{
  tinygl_clear();
  tinygl_update();
}


void display_menu_update()
{
  tinygl_update();
}


void display_menu_step_mode()
{
  tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
}


void display_menu_update_name(const char *str)
{
  tinygl_clear();
  tinygl_text(str);
}


void display_menu_init(const char *str)
{
  tinygl_init(UPDATE_RATE);
  tinygl_font_set(&font5x7_1);
  tinygl_text_speed_set(MESSAGE_RATE);
  tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
  tinygl_text(str);
}
