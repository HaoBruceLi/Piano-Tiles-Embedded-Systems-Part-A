
#include "timer.h"
#include "pio.h"
#include "system.h"
#include "ir_uart.h"
#include "ledmat.h"
#include "navswitch.h"

#include "button.h"
#include "usart1_interrupt.h"

#define TIMER_CLOCK_DIVISOR 256


uint8_t player = 0;
bool start_blinking = false;


static void soft_reset(void)
{
    player = 0;
    start_blinking = false;
    pio_output_low(LED1_PIO);
    usart1_interrupt_enable();
}

int main(void)
{
  system_init();
  timer_init();
  ir_uart_init();
  ledmat_init();
  navswitch_init();

  button_init ();

  usart1_interrupt_init();
  pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);

  while (1)
  {
    navswitch_update();
    button_update();

    if (navswitch_push_event_p(NAVSWITCH_PUSH) && player == 0) {
      player = 1;
      ir_uart_putc('0');
      TCNT1 = 0;
    }

    if (button_push_event_p(0)) {
      soft_reset();
    }

    if (player != 0 && timer_get() > 50000 && !start_blinking) {
      soft_reset();
    }

    ledmat_display_column(0b01111111, player);

    ///////////////////////////////////////////////
    if (start_blinking) {
      pio_output_toggle(LED1_PIO);
      timer_wait(5000);
    }
  }
  return 0;
}


ISR(USART1_RX_vect)
{
  char message = ir_uart_getc();
  if (message == '0' && player == 0) {
    TCNT1 = 0;
    ir_uart_putc('1');
    player = 2;
  } else if (message == '1' && player == 1) {
    TCNT1 = 0;
    ir_uart_putc('2');
    start_blinking = true;
    usart1_interrupt_disable();
  } else if (message == '2' && player == 2){
    TCNT1 /= 2;
    start_blinking = true;
    usart1_interrupt_disable();
  }
}
