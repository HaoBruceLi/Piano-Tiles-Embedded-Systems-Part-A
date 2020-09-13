/** @file   ir_sync.h
    @author Narottam Royal
    @date   16 October 2018
*/

#ifndef IR_SYNC_H
#define IR_SYNC_H


#include "system.h"


extern bool syncronised;


void ir_sync_start(void);


void ir_sync_reset(void);


void ir_sync_init(void);


#endif
