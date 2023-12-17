#include "DataManager.h"
#include <cstdint>
#include <cstdio>

DataManager::DataManager()
    : _bd(SPI_FLASH_MOSI, SPI_FLASH_MISO, SPI_FLASH_CLK, SPI_FLASH_CS),
      _fs(FILESYSTEM_MOUNTING_POINT) {}

DataManager::~DataManager() {}

DataManager &DataManager::getDataManager() {
  static DataManager instance;
  return instance;
}

void DataManager::storeSensorData() {
  sensor_measurement_t *measurement = sensor_data_mailbox.try_get();
  if (measurement == NULL) {
    printf("Not sensor data available\n");
    return;
  }
  bool success = mountFileSystem();
  if (success == false) {
    printf("Could not mount file system. Unable to store sensor data.\n\r");
    // file_system_mutex.unlock();
    return;
  }
  // file_system_mutex.lock();
  FILE *file = fopen("/fs/sensor_data.csv", "a");
  if (file == NULL) {
    printf("Could not open file");
    // file_system_mutex.unlock();
    return;
  } else {
    printf("Writing sensor data to file.\n\r");
    fprintf(file, "%ld,%ld,%ld,%d,%s\n", measurement->temperature,
            measurement->air_humidity, measurement->air_pressure,
            measurement->soil_humidity, measurement->water_level_critical);
    // fprintf(file, "%ld,%ld,%ld,%d,%s\n", measurement->temperature,
    //         measurement->air_humidity, measurement->air_pressure,
    //         measurement->soil_humidity, measurement->water_level_critical);
    fclose(file);
  }
  sensor_data_mailbox.free(measurement);
  return;
}

bool DataManager::mountFileSystem() {

  for (uint8_t i = 0; i < FS_MOUNT_NO_OF_TRIES; i++) {
    int err = _fs.mount(&_bd);
    if (err) {
      printf("Failed to mount filesystem. Try:%d\n", i + 1);
    } else {
      return true;
    }
  }

  _fs.reformat(&_bd);
  return false;
}
