#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H
#include "mbed.h"
#include "time.h"
#include <cstdint>


#define SENSOR_READ_INTERVAL_SECONDS 60


class SystemConfig {
private:
  SystemConfig();

  int32_t sensor_measurement_freq;
  tm alarmA;
  tm alarmB;
  int32_t durationA_sec;
  int32_t durationB_sec;

  bool _time_synced;

public:
  static SystemConfig &getSystemConfig();


  // getters
  int32_t getSensorMeasurementFreq();
  int32_t getIrrigationDurationA();
  int32_t getIrrigationDurationB();
  tm getAlarmA();
  tm getAlarmB();

  bool isTimeSynced();

  // setters
};

#endif