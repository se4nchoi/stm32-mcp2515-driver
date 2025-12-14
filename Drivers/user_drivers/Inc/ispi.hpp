#ifndef ISPI_HPP
#define ISPI_HPP

#include <cstdint>

/**
 * @brief Abstract Interface for SPI Communication.
 * This allows us to swap "Real Hardware" for "Fake Test Hardware".
 */
class ISPI {
public:
    virtual ~ISPI() = default;

    /**
     * @brief Assert Chip Select (Low)
     */
    virtual void select() = 0;

    /**
     * @brief Release Chip Select (High)
     */
    virtual void deselect() = 0;

    /**
     * @brief Send a byte and receive a byte (Full Duplex)
     * @param data Byte to send
     * @return Byte received
     */
    virtual uint8_t transfer(uint8_t data) = 0;
};

#endif // ISPI_HPP
