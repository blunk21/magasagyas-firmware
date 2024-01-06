// sensor_data.h
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include "BME680.h"
#include <cstdint>
#include "DataManager.h"
#include "IrrigationManager.h"


#define TPH_SENSOR_SDA PB_9
#define TPH_SENSOR_SCL PB_8
#define WTR_LVL_PIN PG_3
#define SOIL_HUMIDITY_PIN PC_0











class SensorData {
private:
    // Private constructor to ensure singleton pattern
    SensorData();
    uint8_t remapSoilHumidity(float analogValue);

    // Sensor data variables
    int32_t temperature;
    int32_t airHumidity;
    int32_t airPressure;
    uint8_t soilHumidity;

    BME680 _tph_sensor;
    InterruptIn _wtr_lvl;
    AnalogIn _soil_sensor;

public:
    // Public method to get the instance of the singleton
    static SensorData& getSensorData();

    // Do measurements
    void measureTemperature();
    void measureAirHumidity();
    void measureSoilHumidity();
    void measureAirPressure();
    uint8_t isWaterLevelCritical();
    void makeAllMeasurements();
    void readSensorData();

    // Getter methods for sensor data
    int32_t getTemperature() const;
    int32_t getAirHumidity() const;
    int32_t getAirPressure() const;
    uint8_t getSoilHumidity() const;

    
   
};

#endif // SENSOR_DATA_H
