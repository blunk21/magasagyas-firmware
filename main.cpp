#include "mbed.h"
#include "SensorData.h"
#include <cstdio>
#include "DataManager.h"

#include "SPIFBlockDevice.h"
#include "LittleFileSystem.h"
SPIFBlockDevice spif(SPI_FLASH_MOSI, SPI_FLASH_MISO, SPI_FLASH_CLK, SPI_FLASH_CS);


// main() runs in its own thread in the OS
int main()
{
    spif.init();
    printf("spif size: %llu\n",         spif.size());
    printf("spif read size: %llu\n",    spif.get_read_size());
    printf("spif program size: %llu\n", spif.get_program_size());
    printf("spif erase size: %llu\n",   spif.get_erase_size());
    // Write "Hello World!" to the first block
    char *buffer = (char *)malloc(spif.get_erase_size());
    sprintf(buffer, "Hello World!\n");
    spif.erase(0, spif.get_erase_size());
    spif.program(buffer, 0, spif.get_erase_size());

    // Read back what was stored
    spif.read(buffer, 0, spif.get_erase_size());
    printf("%s", buffer);

    // Deinitialize the device
    spif.deinit();
}

