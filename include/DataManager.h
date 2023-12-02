#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "mbed.h"
#include "LittleFileSystem.h"
#include "W25Q64FV.h"

#define SPI_FLASH_MOSI PA_7
#define SPI_FLASH_MISO PA_6
#define SPI_FLASH_CS PF_12
#define SPI_FLASH_CLK PA_5


class DataManager {
public:
    // Get the singleton instance
    static DataManager& getDataManager();

    // Initialize the DataManager
    void initialize();

    // Write data to the filesystem
    bool writeData(const char* filePath, const char* data);

    // Read data from the filesystem
    bool readData(const char* filePath, char* buffer, int bufferSize);

private:
    // Private constructor for singleton
    DataManager();

    // Private destructor
    ~DataManager();

    // Private copy constructor and assignment operator to prevent duplication
    DataManager(const DataManager&);
    DataManager& operator=(const DataManager&);


    // W25Q64 flash memory driver
    W25Q64FV flash;

    

    // LittleFileSystem instance
    LittleFileSystem fs;
};

#endif // DATA_MANAGER_H
