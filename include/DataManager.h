#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "mbed.h"
#include "LittleFileSystem.h"
#include "SPIFBlockDevice.h"


#define SPI_FLASH_MOSI PA_7
#define SPI_FLASH_MISO PA_6
#define SPI_FLASH_CS PF_12
#define SPI_FLASH_CLK PA_5


class DataManager {
public:
    


    // Get the singleton instance
    static DataManager& getDataManager();

    




private:
    // Private constructor for singleton
    DataManager();

    // Private destructor
    ~DataManager();

    // Private copy constructor and assignment operator to prevent duplication
    DataManager(const DataManager&);
    DataManager& operator=(const DataManager&);


    SPIFBlockDevice bd;
    LittleFileSystem fs;
};

#endif // DATA_MANAGER_H
