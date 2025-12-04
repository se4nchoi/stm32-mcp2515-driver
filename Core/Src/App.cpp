#include "App.h"
#include "stm32f4xx.h" // Hardware Map

// --- YOUR C++ CLASS ---
class Led {
public:
    void init() {
        // Enable Clock (Bit 0)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        // Set PA5 to Output (01)
        GPIOA->MODER &= ~GPIO_MODER_MODE5;
        GPIOA->MODER |= GPIO_MODER_MODE5_0;
    }

    void toggle() {
        GPIOA->ODR ^= GPIO_ODR_OD5;
    }
};

// --- THE ENTRY POINT ---
void App_Main(void) {
    Led statusLed;
    statusLed.init();

    while (1) {
        statusLed.toggle();
        for (volatile int i = 0; i < 100000; i++); // Delay
    }
}
