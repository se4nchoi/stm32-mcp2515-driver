#include <spi.h>

void SPI::init() {
	// CLOCK
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// GPIO CONFIG

	// PA6 PA7 (MISO MOSI) + PB3 (SCK)
	GPIOA->MODER &= ~((3 << 6*2) | (3 << 7*2)); // clear
	GPIOA->MODER |= ((2 << 6*2) | (2 << 7*2));	// set to AF mode [10] (2 = 10)

	GPIOB->MODER &= ~(3 << 3*2); 	// clear
	GPIOB->MODER |= (2 << 3*2); 	// mode AF 2 (10)

	// PB6 (CS) -> output mode (01)
	GPIOB->MODER &= ~(3 << 6*2); 	// clear
	GPIOB->MODER |= (1 << 6*2);		// set to 01; * no need to set AFR

	// AFR CONFIG
	// AF5 (SPI1) = 5 (0101)
	// PA6, 7 in AFR[0]
	GPIOA->AFR[0] |= (5 << 6*4) | (5 << 7*4);
	// PB3 also in AFR[0]
	GPIOB->AFR[0] |= (5 << 3*4);

	// SPI CONFIG
	SPI1->CR1 |= (4 << 3) |  // Baud Rate: Div/32
				 (1 << 2) |  // Master Mode
				 (1 << 9) |  // SSM (Software Slave Management)
				 (1 << 8) |  // SSI (Internal Slave Select)
				 (1 << 6);   // SPE (Enable)

	// initially set CS as inactive (high)
	csSelect(false);
}

uint8_t SPI::transfer(uint8_t data) {
	SPI1->DR = data;				// Write
	while (!(SPI1->SR & (1 << 0)));	// wait until RXNE (receive not empty)
	return (uint8_t)SPI1->DR;		// Read
}

void SPI::csSelect(bool state) {
	// toggle
	if (state) 	GPIOB->ODR &= ~(1 << 2*3); 	// low (active)
	else		GPIOB->ODR |= (1 << 2*3); 	// high (inactive)
}
