#ifndef UART_H
#define UART_H

#include "stm32f4xx.h"
#include <cstdio> // For printf

class UART {
public:
    static void init();
    static void write(int ch);
};

#endif
