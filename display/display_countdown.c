/** @file   display_countdown.c
    @author Narottam Royal， Hao Li
    @date   16 October 2018
*/

#include "display_countdown.h"
#include "timer.h"
#include "display_menu.h"
#include <stdlib.h>


#define DELAY 25000


void display_countdown()
{
  timer_init();

  uint8_t count = 3;
  char count_str[2];
  itoa(count, count_str, 10);
  display_menu_init(count_str);
  display_menu_step_mode();

  uint16_t current_time = 0;
  uint16_t previous_time = 0;

  while (count-- > 0) {
    timer_set(0);

    while ((current_time = timer_get()) < DELAY) {
      // Update display
      if (current_time - previous_time > TIMER_RATE / UPDATE_RATE) {
        display_menu_update();
        previous_time = current_time;
      }
    }

    display_menu_clear();
    itoa(count, count_str, 10);
    display_menu_update_name(count_str);
  }
}
