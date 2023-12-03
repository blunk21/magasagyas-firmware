#include "DataManager.h"
#include "SensorData.h"
#include "mbed.h"
#include <cstddef>
#include <cstdint>
#include <cstdio>


SPIFBlockDevice spif(SPI_FLASH_MOSI, SPI_FLASH_MISO, SPI_FLASH_CLK,
                     SPI_FLASH_CS);
LittleFileSystem fs("fs");

// main() runs in its own thread in the OS
int main() {

  
}
