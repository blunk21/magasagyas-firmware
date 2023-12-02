// sensor_data.h
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include "BME680.h"
#include <cstdint>


#define TPH_SENSOR_SDA PB_9
#define TPH_SENSOR_SCL PB_8
#define WTR_LVL_PIN PF_12
#define SENSOR_READ_INTERVAL_MS 5000ms


void read_sensors_handler();


class SensorData {
private:
    // Private constructor to ensure singleton pattern
    SensorData();

    // Sensor data variables
    int32_t temperature;
    int32_t airHumidity;
    int32_t airPressure;
    uint8_t soilHumidity;

    BME680 _tph_sensor;
    DigitalIn _wtr_lvl;

public:
    // Public method to get the instance of the singleton
    static SensorData& getSensorData();

    // Setters for sensor data
    void measureTemperature();
    void measureAirHumidity();
    void measureSoilHumidity();
    void measureAirPressure();
    bool isWaterLevelCritical();

    // Getter methods for sensor data
    int32_t getTemperature() const;
    int32_t getAirHumidity() const;
    int32_t getAirPressure() const;
    uint8_t getSoilHumidity() const;

    void makeAllMeasurements();
   
};

#endif // SENSOR_DATA_H
