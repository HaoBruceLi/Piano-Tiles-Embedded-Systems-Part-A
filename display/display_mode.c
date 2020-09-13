/** @file   display_mode.c
    @author Narottam Royal， Hao Li
    @date   16 October 2018
*/

#include "button.h"
#include "display_mode.h"
#include "navswitch.h"
#include "timer.h"
#include "display_menu.h"


// Stops button press from being registered by the next state
#define DEBOUNCE_DELAY 5000
#define EXIT_DELAY 10000


mode_t modes[2] = {{"Normal Mode ", NORMAL},
                   {"Auto Mode ", AUTO}};


uint8_t mode_index = 0;


uint8_t display_mode_get()
{
  return modes[mode_index].id;
}


static void debounce(void)
{
 uint16_t current_time = timer_get();
 uint16_t previous_time = current_time;
 while (current_time - previous_time < DEBOUNCE_DELAY) {
   current_time = timer_get();
 }
}


void display_mode()
{
  display_menu_init(modes[mode_index].name);

  button_init();
  navswitch_init();
  timer_init();

  uint16_t current_time = 0;
  uint16_t previous_time = 0;

  while (1)
  {
    button_update();
    navswitch_update();

    // Increment mode index
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
      display_menu_clear();
      debounce();
      mode_index = (mode_index + 1) % NUM_MODES;
      display_menu_update_name(modes[mode_index].name);
    }

    // Decrement mode index
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
      display_menu_clear();
      debounce();
      mode_index = (mode_index - 1 + NUM_MODES) % NUM_MODES;
      display_menu_update_name(modes[mode_index].name);
    }

    // Select mode and exit
    if (button_push_event_p(0) || navswitch_push_event_p(NAVSWITCH_PUSH)) {
      display_menu_clear();
      previous_time = current_time;
      while (current_time - previous_time < EXIT_DELAY) {
        current_time = timer_get();
      }
      break;
    }

    // Update display
    current_time = timer_get();
    if (current_time - previous_time > TIMER_RATE / UPDATE_RATE) {
      display_menu_update();
      previous_time = current_time;
    }
  }
}
