#ifndef AVR_USART_DEVICE_H
#define AVR_USART_DEVICE_H

#include <drivers/serial/Uart.h>
#include <drivers/serial/avr/UsartDriver.h>
#include <kernel/file/file.h>
#include <periph/usart.h>
#include <utilxx/classes/ByteRing.h>

class UsartDevice : public CharDevFile, public UsartDriver {

private:
	usart_regs* m_regs;
	uint8_t m_irqbase;

	ByteRing m_txring;
	ByteRing m_rxring;

public:
	int write(const char* data, size_t size);
	int read(char* data, size_t size);
	int flush();

	int avail();
	int room();

	int begin();
	int end();

	UsartDevice(usart_regs* regs, int irqbase, char* txbuffer, size_t txsize, char* rxbuffer, size_t rxsize);

	friend void interruptHandler_UsartRX(UsartDevice* usart);
	friend void interruptHandler_UsartTX(UsartDevice* usart);
	friend void interruptHandler_UsartTC(UsartDevice* usart);
};

#endif