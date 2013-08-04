#ifndef HW_SPI_H
#define HW_SPI_H

#include <stdint.h>

void spi_init(void);
void spi_send(const uint8_t);
void spi_send9(const uint16_t);

#endif
