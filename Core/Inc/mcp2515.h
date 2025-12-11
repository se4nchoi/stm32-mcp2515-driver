#ifndef MCP2515_H
#define MCP2515_H

#include <cstdint>

// --- INSTRUCTION SET ---
constexpr uint8_t MCP_RESET       = 0xC0;
constexpr uint8_t MCP_READ        = 0x03;
constexpr uint8_t MCP_WRITE       = 0x02;
constexpr uint8_t MCP_RTS_TX0     = 0x81; // Request-To-Send Buffer 0
constexpr uint8_t MCP_READ_STATUS = 0xA0;
constexpr uint8_t MCP_BIT_MOD     = 0x05; // Bit Modify (Crucial for setting bits)

// --- REGISTER MAP (Crucial Registers) ---
constexpr uint8_t REG_CANSTAT     = 0x0E; // Status Register
constexpr uint8_t REG_CANCTRL     = 0x0F; // Control Register
constexpr uint8_t REG_CNF1        = 0x2A; // Bit Timing 1
constexpr uint8_t REG_CNF2        = 0x29; // Bit Timing 2
constexpr uint8_t REG_CNF3        = 0x28; // Bit Timing 3

// --- BUFFERS ---
constexpr uint8_t REG_TXB0CTRL    = 0x30; // Transmit Buffer 0 Control
constexpr uint8_t REG_TXB0SIDH    = 0x31; // Standard ID High
constexpr uint8_t REG_TXB0SIDL    = 0x32; // Standard ID Low
constexpr uint8_t REG_TXB0DLC     = 0x35; // Data Length Code
constexpr uint8_t REG_TXB0D0      = 0x36; // Data Byte 0

// --- CLASS DEFINITION ---
class Mcp2515 {
public:
    void reset();
    uint8_t readRegister(uint8_t address);
    void writeRegister(uint8_t address, uint8_t data);
    void modifyRegister(uint8_t address, uint8_t mask, uint8_t data); // New!
};

#endif
