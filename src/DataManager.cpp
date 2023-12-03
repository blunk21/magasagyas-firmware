#include "DataManager.h"

DataManager::DataManager() : bd(SPI_FLASH_MOSI, SPI_FLASH_MISO, SPI_FLASH_CLK, SPI_FLASH_CS), fs("fs") {}

DataManager::~DataManager() {}

DataManager& DataManager::getDataManager() {
    static DataManager instance;
    return instance;
}

void DataManager::initialize() {
    // Mount the filesystem
    int err = fs.mount(&bd);
    if (err) {
        printf("Error mounting the filesystem: %d\n", err);
        // Handle the error appropriately, e.g., by resetting or logging
    }
}

bool DataManager::writeData(const char* filePath, const char* data) {
    FILE* file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filePath);
        return false;
    }

    fprintf(file, "%s", data);
    fclose(file);

    return true;
}

bool DataManager::readData(const char* filePath, char* buffer, int bufferSize) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening file for reading: %s\n", filePath);
        return false;
    }

    fgets(buffer, bufferSize, file);
    fclose(file);

    return true;
}