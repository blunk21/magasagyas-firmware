#include "IrrigationManager.h"
#include "GlobalEventQueue.h"
#include "SensorData.h"
#include "SystemConfig.h"
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <ctime>

IrrigationManager::IrrigationManager()
    : _initialized(false), _pump_relay(PUMP_RELAY_PIN), _event(NULL),
      _irrigation_in_progress(false), _irrigation_scheduled(false) {
  _pump_relay = 0;
  scheduleNextIrrigationTime();
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

void IrrigationManager::scheduleNextIrrigationTime() {
  if (_irrigation_scheduled)
    return;
  SystemConfig config = SystemConfig::getSystemConfig();
  EventQueue *global_queue = GlobalEventQueue::getGlobalEventQueue();
  if (config.isTimeSynced() == false) {
    printf("Time is not synced. Unable to schedule irrigation\n");
    return;
  }
  time_t currentTime = time(NULL);
  tm currentTm;
  localtime_r(&currentTime, &currentTm);
  currentTm.tm_sec = 0;
  tm alarmA = config.getAlarmA();
  tm alarmB = config.getAlarmB();
  alarmA.tm_mday = alarmB.tm_mday = currentTm.tm_mday;
  alarmA.tm_mon = alarmB.tm_mon = currentTm.tm_mon;
  alarmA.tm_year = alarmB.tm_year = currentTm.tm_year;

  time_t alarmA_time = mktime(&alarmA), alarmB_time = mktime(&alarmB);
  if ((alarmA_time > alarmB_time || alarmA_time < currentTime) &&
      alarmB_time > currentTime) {
    uint32_t irrigation_delay = alarmB_time - currentTime;
    int32_t duration = config.getIrrigationDurationB();
    auto irrigation_callback = [duration]() {
      IrrigationManager::getIrrigationManager().startIrrigation(duration);
    };

    // Schedule the lambda callback to be called after the delay
    global_queue->call_in(std::chrono::seconds(irrigation_delay),
                          irrigation_callback);
    printf("Irrigation scheduled for Alarm B\n");
    _irrigation_scheduled = true;
  } else if ((alarmB_time > alarmA_time || alarmB_time < currentTime) &&
             alarmA_time > currentTime) {
    uint32_t irrigation_delay = alarmA_time - currentTime;
    int32_t duration = config.getIrrigationDurationA();
    auto irrigation_callback = [duration]() {
      IrrigationManager::getIrrigationManager().startIrrigation(duration);
    };

    // Schedule the lambda callback to be called after the delay
    global_queue->call_in(std::chrono::seconds(irrigation_delay),
                          irrigation_callback);
    printf("Irrigation scheduled for Alarm A\n");
    _irrigation_scheduled = true;
  }
}

void IrrigationManager::startIrrigation(uint32_t duration) {

  if (_irrigation_in_progress ||
      SensorData::getSensorData().isWaterLevelCritical()) {
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
  _irrigation_scheduled = false;
  GlobalEventQueue::getGlobalEventQueue()->call(
      callback(this, &IrrigationManager::scheduleNextIrrigationTime));
}

void IrrigationManager::attachEventQueue(EventQueue *event_p) {
  _event = event_p;
}

void IrrigationManager::releaseIrrigation() {}
