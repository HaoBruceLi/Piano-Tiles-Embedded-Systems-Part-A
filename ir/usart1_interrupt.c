/** @file   usart1_interrupt.c
    @author Narottam Royal， Hao Li
    @date   16 October 2018
*/

#include <avr/interrupt.h>
#include "usart1_interrupt.h"


inline void usart1_interrupt_enable()
{
  UCSR1B |= (1 << RXCIE1);
}


inline void usart1_interrupt_disable()
{
  UCSR1B &= ~(1 << RXCIE1);
}


inline void usart1_interrupt_init()
{
  usart1_interrupt_enable();
  sei();
}
