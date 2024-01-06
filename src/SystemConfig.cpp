#include "SystemConfig.h"
#include <cstdint>

SystemConfig::SystemConfig()
    : alarmA{0, 1, 6}, alarmB{0, 3, 6}, durationA_sec(10), durationB_sec(15),
      _time_synced(false), sensor_measurement_freq(SENSOR_READ_INTERVAL_SECONDS) {



  _time_synced = true;
}

SystemConfig &SystemConfig::getSystemConfig() {
  static SystemConfig instance;
  return instance;
}

int32_t SystemConfig::getSensorMeasurementFreq() {
  return sensor_measurement_freq;
}

int32_t SystemConfig::getIrrigationDurationA() { return durationA_sec; }

int32_t SystemConfig::getIrrigationDurationB() { return durationB_sec; }

tm SystemConfig::getAlarmA() { return alarmA; }

tm SystemConfig::getAlarmB() { return alarmB; }

bool SystemConfig::isTimeSynced() { return _time_synced; }
