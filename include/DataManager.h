#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "LittleFileSystem.h"
#include "SPIFBlockDevice.h"
#include "mbed.h"
#include <cstdint>

#define SPI_FLASH_MOSI PA_7
#define SPI_FLASH_MISO PA_6
#define SPI_FLASH_CS PF_12
#define SPI_FLASH_CLK PA_5
#define FS_MOUNT_NO_OF_TRIES 3

#define FILESYSTEM_MOUNTING_POINT "fs"
#define FILESYSTEM_MOUNTING_BASE_PATH "/fs/"

typedef struct {
  int32_t temperature;
  int32_t air_humidity;
  int32_t air_pressure;
  uint8_t soil_humidity;
  uint8_t water_level_critical;

} sensor_measurement_t;

class DataManager {
public:
  static DataManager &getDataManager();

  Mail<sensor_measurement_t, 16> sensor_data_mailbox;
  void storeSensorData();
  void printSensorMeasurements();

private:
  DataManager();
  bool mountFileSystem();

  SPIFBlockDevice _bd;
  LittleFileSystem _fs;

  Mutex file_system_mutex;
};

#endif // DATA_MANAGER_H
