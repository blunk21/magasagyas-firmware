// sensor_data.cpp
#include "SensorData.h"
#include <cstdint>




// Private constructor to ensure singleton pattern
SensorData::SensorData()
    : _tph_sensor(TPH_SENSOR_SDA, TPH_SENSOR_SCL, false),
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

void SensorData::measureSoilHumidity() {}

bool SensorData::isWaterLevelCritical() {
  if (_wtr_lvl == 0)
    return false;
  else
    return true;
}

void SensorData::measureAirPressure(){
    airPressure = _tph_sensor.getCompensatePressure();
}


// Getter methods for sensor data
int32_t SensorData::getTemperature() const { return temperature; }

int32_t SensorData::getAirHumidity() const { return airHumidity; }

uint8_t SensorData::getSoilHumidity() const { return soilHumidity; }

int32_t SensorData::getAirPressure() const { return airPressure; }

void SensorData::makeAllMeasurements() {
    _tph_sensor.setForcedMode();
    ThisThread::sleep_for(10ms);
    measureAirPressure();
    measureAirHumidity();
    measureTemperature();
}


void read_sensors_handler()
{
    while (true) {
        SensorData &sensor_data = SensorData::getSensorData();
        sensor_data.makeAllMeasurements();

        ThisThread::sleep_for(SENSOR_READ_INTERVAL_MS);
    }
}