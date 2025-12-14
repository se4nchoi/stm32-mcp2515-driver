#include "STM32SPI.hpp"

STM32SPI::STM32SPI(SPI_TypeDef* spi_instance, GPIO_TypeDef* cs_port, uint16_t cs_pin)
    : _spi(spi_instance), _cs_port(cs_port), _cs_pin(cs_pin) {}

void STM32SPI::select() {
    // Direct Register Access to pull CS Low (Reset Bit)
    // BSRR (Bit Set/Reset Register) is faster than HAL_GPIO_WritePin
    _cs_port->BSRR = (uint32_t)_cs_pin << 16U;
}

void STM32SPI::deselect() {
    // Direct Register Access to pull CS High (Set Bit)
    _cs_port->BSRR = _cs_pin;
}

uint8_t STM32SPI::transfer(uint8_t data) {
    // 1. Wait until Transmit Buffer is Empty (TXE flag)
    while (!(_spi->SR & SPI_SR_TXE));

    // 2. Write Data to Data Register (DR)
    _spi->DR = data;

    // 3. Wait until Receive Buffer is Not Empty (RXNE flag)
    // Note: SPI is full-duplex; for every byte sent, one is received.
    while (!(_spi->SR & SPI_SR_RXNE));

    // 4. Return the data from the Data Register
    return (uint8_t)(_spi->DR);
}
