/** @file   display_mode.h
    @author Narottam Royal
    @date   16 October 2018
*/

#ifndef DISPLAY_MODE_H
#define DISPLAY_MODE_H


#include <stdint.h>


#define NUM_MODES 2


enum {NORMAL, AUTO};


typedef struct
{
  const char *name;
  const uint8_t id;
} mode_t;


uint8_t display_mode_get(void);


void display_mode(void);


#endif
