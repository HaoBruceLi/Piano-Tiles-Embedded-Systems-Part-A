/** @file   ir_sync.c
    @author Narottam Royal， Hao Li
    @date   16 October 2018
*/

#include <stdlib.h>
#include "display_menu.h"
#include "ir_sync.h"
#include "ir_uart.h"
#include "usart1_interrupt.h"
#include "select_song.h"
#include "songs.h"
#include "system.h"
#include "timer.h"


bool syncronised = false;


void ir_sync_start()
{
  srand(timer_get());
  timer_set(0);
  ir_uart_putc(select_song_index_get() + '0');
}


void ir_sync_reset()
{
  syncronised = false;
  usart1_interrupt_enable();
}


void ir_sync_init()
{
  ir_uart_init();
  usart1_interrupt_init();
}


ISR(USART1_RX_vect)
{
  uint8_t message = ir_uart_getc();

  switch (select_song_player_get())
  {
    case NONE:
      if (message - '0' < NUM_SONGS) {
        select_song_player_set(PLAYER2);
        srand(timer_get());
        timer_set(0);
        ir_uart_putc(message + 1);
        select_song_index_set(message - '0');
        display_menu_update_name(songs[select_song_index_get()].song_name);
      }
      break;

    case PLAYER1:
      if (message - '0' == select_song_index_get() + 1) {
        timer_set(0);
        ir_uart_putc(message - 1);
        syncronised = true;
        usart1_interrupt_disable();
      }
      break;

    case PLAYER2:
      if (message - '0' == select_song_index_get()) {
        timer_set(timer_get() / 2);
        syncronised = true;
        usart1_interrupt_disable();
      }
      break;
  }
}
