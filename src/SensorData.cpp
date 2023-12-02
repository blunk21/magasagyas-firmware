// sensor_data.cpp
#include "sensor_data.h"

// Private constructor to ensure singleton pattern
SensorData::SensorData() {}

// Public method to get the instance of the singleton
SensorData& SensorData::getInstance() {
    static SensorData instance;
    return instance;
}

// Setters for sensor data
void SensorData::setTemperature(int temp) {
    temperature = temp;
}

void SensorData::setAirHumidity(int humidity) {
    airHumidity = humidity;
}

void SensorData::setSoilHumidity(int soilHum) {
    soilHumidity = soilHum;
}

void SensorData::setWaterLevelCritical(bool isCritical) {
    isWaterLevelCritical = isCritical;
}

// Getter methods for sensor data
int SensorData::getTemperature() const {
    return temperature;
}

int SensorData::getAirHumidity() const {
    return airHumidity;
}

int SensorData::getSoilHumidity() const {
    return soilHumidity;
}

bool SensorData::isWaterLevelCritical() const {
    return isWaterLevelCritical;
}
