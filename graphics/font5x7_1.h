/** @file    font5x7_1.h
    @author  fontgen
    @date    24 Sep 2011

    @defgroup font5x7_1  This is a 5x7 font with uppercase, lowercase, digits, and symbols.
 M.P. Hayes 2 Sep 2010

*/

#ifndef FONT5X7_1_H_
#define FONT5X7_1_H_

#define FONT5X7_1_WIDTH 5
#define FONT5X7_1_HEIGHT 7
#define FONT5X7_1_OFFSET 32
#define FONT5X7_1_SIZE 95

#ifndef FONT_WIDTH
#define FONT_WIDTH 5
#endif
#ifndef FONT_HEIGHT
#define FONT_HEIGHT 7
#endif
#ifndef FONT_OFFSET
#define FONT_OFFSET 32
#endif
#ifndef FONT_SIZE_MAX
#define FONT_SIZE_MAX 95
#endif

#include "font.h"
#include <avr/pgmspace.h>

static font_t font5x7_1 =
{
    .flags = 1, /* (packed)  */
    .width = 5,
    .height = 7,
    .offset = 32,
    .size = 95,
    .bytes = 5
};

extern font_data_t font_data[];

#endif  /* FONT5X7_1_H_  */
