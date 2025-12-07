#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f4xx.h"

class SPI {
public:
	static void init();

	// byte out, byte in
	static uint8_t transfer(uint8_t data);

	// TRUE (low) = select; False (high) = Deselect
	static void csSelect(bool state);
};

#endif
