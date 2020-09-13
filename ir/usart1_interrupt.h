/** @file   usart1_interrupt.h
    @author Narottam Royal
    @date   16 October 2018
*/

#ifndef USART1_INTERRUPTS_H
#define USART1_INTERRUPTS_H

#include <avr/interrupt.h>


void usart1_interrupt_enable(void);


void usart1_interrupt_disable(void);


void usart1_interrupt_init(void);


#endif
