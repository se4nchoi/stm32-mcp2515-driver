#include "MCP2515.hpp"

// Constructor: Save the pointer so we can use it later
Mcp2515::Mcp2515(ISPI* spi_interface) : spi(spi_interface) {}

void Mcp2515::reset() {
    spi->select();          // Use the interface!
    spi->transfer(MCP_RESET);
    spi->deselect();

    // Simple delay loop (Keep it simple for MVP)
    for (volatile int i = 0; i < 10000; i++);
}

uint8_t Mcp2515::readRegister(uint8_t address) {
    spi->select();
    spi->transfer(MCP_READ);      // Command
    spi->transfer(address);       // Address
    uint8_t data = spi->transfer(0xFF); // Dummy to read
    spi->deselect();
    return data;
}

void Mcp2515::modifyRegister(uint8_t address, uint8_t mask, uint8_t data) {
    spi->select();
    spi->transfer(MCP_BIT_MOD);
    spi->transfer(address);
    spi->transfer(mask);
    spi->transfer(data);
    spi->deselect();
}
