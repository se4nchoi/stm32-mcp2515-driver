#include "uart.h"

void UART::init() {
    // 1. Enable Clocks (GPIOA and USART2)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // 2. Configure PA2 (TX) and PA3 (RX) as Alternate Function
    GPIOA->MODER  &= ~((3 << 4) | (3 << 6)); // Clear
    GPIOA->MODER  |=  ((2 << 4) | (2 << 6)); // Set AF

    // 3. Set AF7 (USART2) for PA2 and PA3
    // AFR[0] is AFRL. Pin 2 is bits 8-11. Pin 3 is bits 12-15.
    GPIOA->AFR[0] |= (7 << 8) | (7 << 12);

    // 4. Configure USART2
    // Baud Rate: 9600 bps @ 16 MHz (HSI)
    // USART_BRR = APB1_Clock / Baud
    // 16,000,000 / 9600 = 1666.66 -> 1667 -> 0x0683
    USART2->BRR = 0x0683;

    // Enable TE (Transmitter), RE (Receiver), UE (USART Enable)
    USART2->CR1 = (1 << 3) | (1 << 2) | (1 << 13);
}

void UART::write(int ch) {
    // Wait for Transmit Data Register Empty (TXE)
    while (!(USART2->SR & (1 << 7)));
    // Write data
    USART2->DR = (ch & 0xFF);
}

// --- THE MAGIC SAUCE: Redirect printf ---
// This function is called by printf logic in the C standard library.
extern "C" int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        UART::write(ptr[i]);
    }
    return len;
}
