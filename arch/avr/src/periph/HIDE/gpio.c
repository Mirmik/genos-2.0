#include <genos/drivers/gpio.h>
#include <gxx/debug/dprint.h>

inline void gpio_write(struct gpio_regs* g, gpio_mask_t mask, unsigned char level) {
	if (level) g->port |= mask;
	else g->port &= ~mask;	
}

inline gpio_mask_t gpio_read(struct gpio_regs* g, gpio_mask_t mask) {
	return g->pin;
}

inline void gpio_toggle(struct gpio_regs* g, gpio_mask_t mask) {
	g->pin = mask;
}

int gpio_settings(struct gpio_regs* g, gpio_mask_t mask, int32_t mode) {
	if ((mode & GPIO_MODE_OUT_SECTION) &&
		(mode & GPIO_MODE_IN_SECTION)) { /* mode is incorrect */
		return -1;
	}
	
	if (mode & GPIO_MODE_INPUT) {
		g->ddr &= ~mask; 
		return 0;
	};

	if (mode & GPIO_MODE_OUTPUT) {
		g->ddr |= mask;		
		return 0;
	};
}
/*
void pin_mode(int pin, int32_t mode) {
	gpio_settings(gpio_table[pin].regs, 
		(1<<gpio_table[pin].offset), mode);
}

uint8_t pin_get_level(int pin) {
	return gpio_read(gpio_table[pin].regs, 
		(1<<gpio_table[pin].offset));
}

void pin_set_level(int pin, uint8_t lvl) {
	gpio_write(gpio_table[pin].regs, 
		(1<<gpio_table[pin].offset), lvl);
}

void pin_tgl_level(int pin) {
	gpio_toggle(gpio_table[pin].regs, 
		(1<<gpio_table[pin].offset));
}
*/