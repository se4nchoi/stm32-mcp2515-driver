#include <gtest/gtest.h>
#include "MCP2515.hpp"
#include "ISPI.hpp"
#include <vector>

// The Mock (Updated with RX Logic)
class MockSPI : public ISPI {
public:
    std::vector<uint8_t> tx_log;   // Logs what the driver sent
    std::vector<uint8_t> rx_queue; // Fake data we want to send back

    void select() override {}
    void deselect() override {}

    uint8_t transfer(uint8_t data) override {
        tx_log.push_back(data); // Record the command sent by Driver

        // If we have fake data queued up, return it. Otherwise return 0.
        if (!rx_queue.empty()) {
            uint8_t val = rx_queue.front();
            rx_queue.erase(rx_queue.begin()); // Remove from queue
            return val;
        }
        return 0x00;
    }
};

// Test 1: Reset Command (The one you already ran)
TEST(Mcp2515Test, ResetSendsCorrectCommand) {
    MockSPI fakeSPI;
    Mcp2515 driver(&fakeSPI);

    driver.reset();

    bool found_reset = false;
    for (uint8_t byte : fakeSPI.tx_log) {
        if (byte == 0xC0) found_reset = true;
    }
    EXPECT_TRUE(found_reset);
}

// Test 2: Read Register
TEST(Mcp2515Test, ReadRegisterReturnsDataFromSlave) {
    // Setup
    MockSPI fakeSPI;
    Mcp2515 driver(&fakeSPI);

    // PRE-LOAD the Mock with "Fake Answers"
    // The MCP2515 transaction is 3 bytes long: [Command, Address, Dummy]
    // We need to provide 3 return values.
    // Byte 1: 0x00 (Ignored response to Command)
    // Byte 2: 0x00 (Ignored response to Address)
    // Byte 3: 0x55 (The ACTUAL data we want the driver to read)
    fakeSPI.rx_queue = {0x00, 0x00, 0x55};

    // Action: Read register 0x0E
    uint8_t result = driver.readRegister(0x0E);

    // Assertion 1: Did the driver return the 0x55 we planted?
    EXPECT_EQ(result, 0x55);

    // Assertion 2: Did the driver send the Dummy Byte (0xFF) to get the answer?
    ASSERT_GE(fakeSPI.tx_log.size(), 3); // Must be at least 3 bytes
    EXPECT_EQ(fakeSPI.tx_log[2], 0xFF);  // The 3rd byte must be 0xFF
}
