#ifndef MCP2515_HPP
#define MCP2515_HPP

#include "ISPI.hpp" // <--- Include the Interface
#include <cstdint>

// --- INSTRUCTION SET ---
constexpr uint8_t MCP_RESET       = 0xC0;
constexpr uint8_t MCP_READ        = 0x03;
constexpr uint8_t MCP_WRITE       = 0x02;
constexpr uint8_t MCP_BIT_MOD     = 0x05;
constexpr uint8_t REG_CANCTRL     = 0x0F;
constexpr uint8_t REG_CANSTAT     = 0x0E;

class Mcp2515 {
public:
    /**
     * @brief Constructor now REQUIRES a tool to talk to the hardware.
     * @param spi_interface Pointer to any class that implements ISPI
     */
    Mcp2515(ISPI* spi_interface);

    void reset();
    uint8_t readRegister(uint8_t address);
    void modifyRegister(uint8_t address, uint8_t mask, uint8_t data);

private:
    ISPI* spi; // <--- The handle to the tool (Mock or Real)
};

#endif // MCP2515_HPP
