/** @file   display_menu.h
    @author Narottam Royal
    @date   16 October 2018
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <stdint.h>


#define UPDATE_RATE 1000
#define MESSAGE_RATE 18


void display_menu_clear(void);


void display_menu_update(void);


void display_menu_step_mode(void);


void display_menu_update_name(const char *str);


void display_menu_init(const char *str);


#endif
