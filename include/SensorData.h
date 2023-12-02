// sensor_data.h
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

class SensorData {
private:
    // Private constructor to ensure singleton pattern
    SensorData();

    // Sensor data variables
    int temperature;
    int airHumidity;
    int soilHumidity;
    bool isWaterLevelCritical;

public:
    // Public method to get the instance of the singleton
    static SensorData& getInstance();

    // Setters for sensor data
    void setTemperature(int temp);
    void setAirHumidity(int humidity);
    void setSoilHumidity(int soilHum);
    void setWaterLevelCritical(bool isCritical);

    // Getter methods for sensor data
    int getTemperature() const;
    int getAirHumidity() const;
    int getSoilHumidity() const;
    bool isWaterLevelCritical() const;
};

#endif // SENSOR_DATA_H
