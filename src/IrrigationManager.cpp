#include "IrrigationManager.h"
#include "SystemConfig.h"
#include "SensorData.h"
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <ctime>

IrrigationManager::IrrigationManager()
    : _initialized(false), _pump_relay(PUMP_RELAY_PIN), _event(NULL),
      _irrigation_in_progress() {
  _pump_relay = 0;
}

IrrigationManager &IrrigationManager::getIrrigationManager() {
  static IrrigationManager instance;
  return instance;
}

void IrrigationManager::init() { /*
   if (_event == NULL) {
     printf("No event queue is attached to irrigation manager.\n");
     return;
   }
   SystemConfig config = SystemConfig::getSystemConfig();
   time_t currentTimestamp = time(NULL);

   tm alarmATime = config.getAlarmA();
   time_t nextIrrigationA = calculateNextIrrigationTime(alarmATime);

   tm alarmBTime = config.getAlarmB();
   time_t nextIrrigationB = calculateNextIrrigationTime(alarmBTime);

   if (nextIrrigationA < nextIrrigationB) {
     time_t nextIrrigation = nextIrrigationA;
     _next_alarm = ALARM_DURATION_A;
   } else {
     time_t nextIrrigation = nextIrrigationB;
     _next_alarm = ALARM_DURATION_B;
   }

   time_t nextIrrigation =
       (nextIrrigationA < nextIrrigationB) ? nextIrrigationA : nextIrrigationB;

   // Calculate the delay until the next irrigation
   int delaySeconds = static_cast<int>(nextIrrigation - currentTimestamp);
   _event->call_in(std::chrono::seconds(delaySeconds),
                   [this]() { this->executeIrrigation(); });*/
}

time_t IrrigationManager::calculateNextIrrigationTime() {
  time_t currentTime;
  return currentTime; /*
 if (SystemConfig::getSystemConfig().isTimeSynced() == false)
   return 0;
 time_t currentTimestamp = time(NULL);
 SystemConfig config = SystemConfig::getSystemConfig();
 tm currentTm, nextIrrigationTm;

 tm nextIrrigationTmA = config.getAlarmA();
 time_t alarm_a_timestamp = mktime(&nextIrrigationTmA);
 tm nextIrrigationTmB = config.getAlarmB();
 time_t alarm_b_timestamp = mktime(&nextIrrigationTmB);   // itt kene folytatni


 if (nextIrrigationTmA.tm_hour > nextIrrigationTmB.tm_hour ||
     (nextIrrigationTmA.tm_hour == nextIrrigationTmB.tm_hour &&
      nextIrrigationTmA.tm_min > nextIrrigationTmB.tm_min))

    nextIrrigationTm = nextIrrigationTmA;
 else
   tm nextIrrigationTm = nextIrrigationTmB;

 localtime_r(&currentTimestamp, &currentTm);

 // Set the date and seconds to 0 in nextIrrigationTm
 nextIrrigationTm.tm_sec = 0;
 nextIrrigationTm.tm_mday = currentTm.tm_mday;
 nextIrrigationTm.tm_mon = currentTm.tm_mon;
 nextIrrigationTm.tm_year = currentTm.tm_year;

 // Calculate the next irrigation time
 if (currentTm.tm_hour > nextIrrigationTm.tm_hour ||
     (currentTm.tm_hour == nextIrrigationTm.tm_hour &&
      currentTm.tm_min >= nextIrrigationTm.tm_min)) {
   // If the alarm time has already passed today, schedule for the next day
   nextIrrigationTm.tm_mday++;
 }

 // Set the alarm time in the tm struct
 nextIrrigationTm.tm_hour = alarmTime.tm_hour;
 nextIrrigationTm.tm_min = alarmTime.tm_min;

 // Calculate the Unix timestamp of the next irrigation time
 time_t nextIrrigationTimestamp = mktime(&nextIrrigationTm);

 return nextIrrigationTimestamp;*/
}

void IrrigationManager::startIrrigation(uint32_t duration) {

  if (_irrigation_in_progress || SensorData::getSensorData().isWaterLevelCritical() ) {
    printf("Unable to start irrigation.\n");
    return;
  }
  _irrigation_in_progress = true;
  _pump_relay = 1;
  printf("Irrigation started.\n");
  irrigation_stop_timer.attach(
      callback(this, &IrrigationManager::stopIrrigation), duration);
}

void IrrigationManager::stopIrrigation() {
  if (!_irrigation_in_progress)
    return;
  _pump_relay = 0;
  _irrigation_in_progress = false;
}

void IrrigationManager::attachEventQueue(EventQueue *event_p) {
  _event = event_p;
}

void IrrigationManager::releaseIrrigation() {}
