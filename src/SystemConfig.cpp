#include "SystemConfig.h"
#include <cstdint>

SystemConfig::SystemConfig()
    : alarmA{0, 0, 7}, alarmB{0, 0, 17}, durationA_sec(10), durationB_sec(15),
      _time_synced(false), sensor_measurement_freq(SENSOR_READ_INTERVAL_SECONDS) {



  tm currentTm;
  time_t currentTimestamp = time(NULL);
  localtime_r(&currentTimestamp, &currentTm);

  alarmA.tm_mday = alarmB.tm_mday = currentTm.tm_mday;
  alarmA.tm_mon = alarmB.tm_mon = currentTm.tm_mon;
  alarmA.tm_year = alarmB.tm_year = currentTm.tm_year;
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
