/** @file   display_score.c
    @author Narottam Royal， Hao Li
    @date   16 October 2018
*/

#include "button.h"
#include "display_score.h"
#include "navswitch.h"
#include "timer.h"
#include "display_menu.h"
#include <stdlib.h>


// Stops button press from being registered by the next state
#define EXIT_DELAY 10000


void display_score(uint8_t score)
{
  char score_str[11] = "Score ";
  itoa(score, score_str + 6, 10);
  display_menu_init(score_str);

  button_init();
  navswitch_init();
  timer_init();

  uint16_t current_time = 0;
  uint16_t previous_time = 0;

  while (1)
  {
    button_update();
    navswitch_update();
    if (button_push_event_p(0) || navswitch_push_event_p(NAVSWITCH_PUSH)) {
      display_menu_clear();
      previous_time = current_time;
      while (current_time - previous_time < EXIT_DELAY) {
        current_time = timer_get();
      }
      break;
    }

    current_time = timer_get();
    // Update display
    if (current_time - previous_time > TIMER_RATE / UPDATE_RATE) {
      display_menu_update();
      previous_time = current_time;
    }
  }
}
