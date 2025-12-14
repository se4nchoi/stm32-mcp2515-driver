#include <gtest/gtest.h>
#include "MCP2515.hpp"
#include "ISPI.hpp"
#include <vector>

// 1. The Mock (The "Liar")
class MockSPI : public ISPI {
public:
    std::vector<uint8_t> tx_log; // Log what the driver sent

    void select() override {}
    void deselect() override {}

    uint8_t transfer(uint8_t data) override {
        tx_log.push_back(data); // Record the command
        return 0x00;
    }
};

// 2. The Test
TEST(Mcp2515Test, ResetSendsCorrectCommand) {
    // Setup
    MockSPI fakeSPI;
    Mcp2515 driver(&fakeSPI);

    // Action
    driver.reset();

    // Assertion: Did it send 0xC0 (Reset Command)?
    // Note: It might send dummy bytes or other things, but 0xC0 must be there.
    bool found_reset = false;
    for (uint8_t byte : fakeSPI.tx_log) {
        if (byte == 0xC0) found_reset = true;
    }

    EXPECT_TRUE(found_reset);
}
