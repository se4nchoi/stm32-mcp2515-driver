# STM32 MCP2515 Driver

A small C++ driver project for communicating with an MCP2515 CAN controller from an STM32F411 over SPI.

I built this as an embedded systems learning project. The current version covers basic SPI communication, a few MCP2515 commands, loopback-mode validation, and an initial mock-based test setup.

![C++](https://img.shields.io/badge/C%2B%2B-14-blue)
![STM32](https://img.shields.io/badge/MCU-STM32F411-blue)
![Protocol](https://img.shields.io/badge/Protocol-SPI%20%2F%20CAN-lightgrey)

## Preview

I plan to add the following once I recreate the hardware setup:

* STM32-to-MCP2515 wiring diagram
* Hardware photo
* Loopback test video
* GoogleTest output

<!--
![STM32F411 to MCP2515 wiring](docs/stm32-mcp2515-wiring.png)

![STM32F411 and MCP2515 hardware setup](docs/hardware-setup.jpg)

[Watch the loopback validation demo](VIDEO_URL)

![GoogleTest output](docs/gtest-output.png)
-->

## Implemented

* SPI setup using direct register access
* Manual chip-select control
* Full-duplex SPI byte transfer
* MCP2515 reset command
* Register reads
* Bit modification
* Loopback-mode configuration
* Controller-status readback
* LED feedback for hardware validation
* `ISPI` interface for hardware and mock SPI implementations
* Initial GoogleTest setup

> **Current status:** Basic SPI communication and MCP2515 mode control were previously tested on hardware. CAN frame transmission and reception are not implemented yet.

## Structure

```text
Application
    ↓
Mcp2515 driver
    ↓
ISPI
   ↙    ↘
STM32SPI  MockSPI
```

The MCP2515 driver talks through `ISPI`.

On the board, it uses `STM32SPI`. For host-side tests, it can use `MockSPI` instead.

## Validation

The original hardware test did the following:

1. Initialized SPI
2. Reset the MCP2515
3. Switched the controller into loopback mode
4. Read the controller status back
5. Used the STM32 LED to indicate success or failure

The repository also includes an initial test that checks whether `reset()` sends the expected MCP2515 reset command.

## Development Environment

Originally used:

* Windows 11
* STM32CubeIDE
* STM32F411 development board
* MCP2515 CAN controller module
* C and C++
* CMake
* GoogleTest

The STM32 firmware and the host-side tests are built separately.

## Prerequisites for Host-Side Tests

Install:

* Git
* CMake
* A C++14-compatible compiler

On Windows, Visual Studio Build Tools with the **Desktop development with C++** workload is recommended.

Install CMake:

```powershell
winget install Kitware.CMake
```

Check that it is available:

```powershell
cmake --version
```

When using Visual Studio Build Tools, open a **Developer PowerShell for Visual Studio** and check the compiler:

```powershell
cl
```

The first CMake configuration also needs internet access because GoogleTest is downloaded with `FetchContent`.

## Local Test Build

```powershell
git clone https://github.com/se4nchoi/stm32-mcp2515-driver.git
cd stm32-mcp2515-driver

cmake -S . -B build
cmake --build build --config Debug
```

Run the test executable:

```powershell
.\build\Debug\run_tests.exe
```

Or run through CTest:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

## Limitations

The project does not yet include:

* CAN frame transmission or reception
* Acceptance filters
* Interrupt-based communication
* Timeout handling
* Error-state handling
* Configurable CAN bit timing
* A documented firmware flashing workflow

## Development Process

This project was built with AI assistance.

I chose the project, assembled the hardware, asked implementation questions, adjusted the generated code, and used the board behavior to check whether the result worked.

I did not independently design every part of the driver or test setup. The project is best understood as a record of my early embedded systems learning rather than fully original driver work.

## What I Learned

* How an STM32 communicates with an external CAN controller over SPI
* How chip select and full-duplex SPI transfers work
* How MCP2515 commands and registers are used
* How loopback mode can help validate the setup
* Why hardware-specific code and driver logic are easier to manage when separated
* How a mock SPI implementation can be used for host-side tests
* How C startup code can hand control over to C++ application code
* Which parts of AI-generated embedded code need closer review

## Next Steps

* Recreate the wiring
* Record the hardware test
* Rerun the GoogleTest build
* Add more driver tests
* Implement CAN transmission and reception
* Add timeout and error handling

## License

No license has been added yet.
