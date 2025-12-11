#include "mcp2515.h"
#include "spi.h"

void Mcp2515::reset() {
    SPI::csSelect(true);          // Pull Low (Active)
    SPI::transfer(MCP_RESET);     // Send 0xC0
    SPI::csSelect(false);         // Pull High (Inactive)

    // Tiny delay to let the chip wake up
    for (volatile int i = 0; i < 10000; i++);
}

uint8_t Mcp2515::readRegister(uint8_t address) {
    SPI::csSelect(true);

    SPI::transfer(MCP_READ);      // Send Read Command (0x03)
    SPI::transfer(address);       // Send Address
    uint8_t data = SPI::transfer(0xFF); // Send dummy to read data

    SPI::csSelect(false);
    return data;
}

void Mcp2515::modifyRegister(uint8_t address, uint8_t mask, uint8_t data) {
    SPI::csSelect(true);

    SPI::transfer(MCP_BIT_MOD); // Command (0x05)
    SPI::transfer(address);     // Address to touch
    SPI::transfer(mask);        // Mask: Which bits allowed to change? (1=Allow)
    SPI::transfer(data);        // Data: The new values

    SPI::csSelect(false);
}
