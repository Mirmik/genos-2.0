#ifndef STM32F4DISCOVERY_V2_BOARD
#define STM32F4DISCOVERY_V2_BOARD

#include <sys/cdefs.h>
#include <drivers/gpio/pin.h>
#include <drivers/serial/stm32_usart.h>

#define HSE_FREQ 8000000

extern struct gpio_pin board_led;

extern struct stm32_usart_device usart2;
extern struct stm32_usart_device usart6;

namespace board 
{
	extern gpio_pin sysled;
}

__BEGIN_DECLS

void board_init(int freqmode = 0);

__END_DECLS

#endif