#include "App.h"
#include "stm32f4xx.h"
#include "spi.h"
#include "mcp2515.h" // Ensure this includes your register definitions

// --- LED Helper ---
void led_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
}
void led_toggle() { GPIOA->ODR ^= GPIO_ODR_OD5; }
void led_off() { GPIOA->ODR &= ~GPIO_ODR_OD5; }

// --- MAIN ---
void App_Main(void) {
    led_init();
    SPI::init();

    Mcp2515 can;
    can.reset();

    // 1. Switch to Loopback Mode
    // Register: CANCTRL (0x0F)
    // Mask: 0xE0 (Top 3 bits control the mode)
    // Value: 0x40 (Loopback Mode pattern)
    can.modifyRegister(REG_CANCTRL, 0xE0, 0x40);

    while (1) {
        // 2. Read Status
        uint8_t status = can.readRegister(REG_CANSTAT);

        // 3. Check if we are in Loopback Mode (0x40)
        // Note: We mask with 0xE0 to ignore other read-only flags
        if ((status & 0xE0) == 0x40) {
            // SUCCESS: Fast Blink (We are in Loopback!)
            led_toggle();
            for (volatile int i = 0; i < 50000; i++);
        } else {
            // FAIL: Slow Blink (Still in Config 0x80 or Error)
            led_toggle();
            for (volatile int i = 0; i < 500000; i++);
        }
    }
}
