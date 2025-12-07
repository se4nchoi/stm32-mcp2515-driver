#include "App.h"
#include "stm32f4xx.h"
#include "spi.h"

// --- LED CLASS  ---
class Led {
public:
    void init() {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        GPIOA->MODER &= ~GPIO_MODER_MODE5;
        GPIOA->MODER |= GPIO_MODER_MODE5_0;
    }
    void on()  { GPIOA->ODR |= GPIO_ODR_OD5; }
    void off() { GPIOA->ODR &= ~GPIO_ODR_OD5; }
};

// --- THE NEW MAIN ---
void App_Main(void) {
    Led statusLed;
    statusLed.init();

    // 1. Initialize the Nervous System
    SPI::init();

    while (1) {
        // 2. The Loopback Test
        // We pull CS Low (Select), send 'A', and pull CS High (Deselect)
        SPI::csSelect(true);
        uint8_t received = SPI::transfer(0x41); // 0x41 is 'A'
        SPI::csSelect(false);

        // 3. The Verdict
        if (received == 0x41) {
            // SUCCESS: Blink FAST (The wire is connected!)
            // Toggle Speed: ~50ms
            statusLed.on();
            for (volatile int i = 0; i < 50000; i++);
            statusLed.off();
            for (volatile int i = 0; i < 50000; i++);
        } else {
            // FAIL: Blink SLOW (The wire is missing!)
            // Toggle Speed: ~500ms
            statusLed.on();
            for (volatile int i = 0; i < 500000; i++);
            statusLed.off();
            for (volatile int i = 0; i < 500000; i++);
        }
    }
}
