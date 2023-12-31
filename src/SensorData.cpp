// sensor_data.cpp
#include "SensorData.h"
#include <algorithm>
#include <cstdint>
#include <cstdlib>

// Private constructor to ensure singleton pattern
SensorData::SensorData()
    : _soil_sensor(SOIL_HUMIDITY_PIN),
      _tph_sensor(TPH_SENSOR_SDA, TPH_SENSOR_SCL, false),
      _wtr_lvl(WTR_LVL_PIN, PinMode::PullDown) {
  _tph_sensor.init();
  _tph_sensor.setForcedMode();
}

// Public method to get the instance of the singleton
SensorData &SensorData::getSensorData() {
  static SensorData instance;
  return instance;
}

// Setters for sensor data
void SensorData::measureTemperature() {
  temperature = _tph_sensor.getCompensatedTemperature();
}

void SensorData::measureAirHumidity() {
  airHumidity = _tph_sensor.getCompensateHumidity();
}

void SensorData::measureSoilHumidity() {
  float analog_value = _soil_sensor.read();
  soilHumidity = remapSoilHumidity(analog_value);
}

uint8_t SensorData::isWaterLevelCritical() {
  if (_wtr_lvl == 0)
    return 0 ;
  else
    return 1;
}

void SensorData::measureAirPressure() {
  airPressure = _tph_sensor.getCompensatePressure();
}

// Getter methods for sensor data
int32_t SensorData::getTemperature() const { return temperature; }

int32_t SensorData::getAirHumidity() const { return airHumidity; }

uint8_t SensorData::getSoilHumidity() const { return soilHumidity; }

int32_t SensorData::getAirPressure() const { return airPressure; }

void SensorData::makeAllMeasurements() {
  _tph_sensor.setForcedMode();
  //   ThisThread::sleep_for(5ms);
  measureAirPressure();
  measureAirHumidity();
  measureTemperature();
  measureSoilHumidity();
}

void SensorData::readSensorData() {
  printf("Reading all sensor data.\n");
  DataManager &data_manager = DataManager::getDataManager();
  sensor_measurement_t *measurement =
      data_manager.sensor_data_mailbox.try_alloc();
  if (measurement == NULL) {
    printf("Unable to allocate mail\n");
    free(measurement);
    return;
  }

  makeAllMeasurements();

  measurement->air_humidity = getAirHumidity();
  measurement->soil_humidity = getSoilHumidity();
  measurement->temperature = getTemperature();
  measurement->air_pressure = getAirPressure();
  measurement->water_level_critical = isWaterLevelCritical();
  osStatus event = data_manager.sensor_data_mailbox.put(measurement);
  if (event == osOK)
    printf("Successfully put sensor data to queue.\n\r");
  else
    printf("Unable to put sensor data to queue.\n\r");
}

uint8_t SensorData::remapSoilHumidity(float analogValue) {
  const float inputMin = 0.003f;
  const float inputMax = 0.75f;
  const uint8_t outputMin = 100;
  const uint8_t outputMax = 0;

  analogValue = std::max(inputMin, std::min(analogValue, inputMax));

  float outputValue = outputMin + (outputMax - outputMin) *
                                      (analogValue - inputMin) /
                                      (inputMax - inputMin);

  return static_cast<uint8_t>(outputValue);
}

void read_sensors_handler() {
  while (true) {
    SensorData &sensor_data = SensorData::getSensorData();
    sensor_data.makeAllMeasurements();

    ThisThread::sleep_for(SENSOR_READ_INTERVAL_MS);
  }
}