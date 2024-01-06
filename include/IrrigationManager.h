#ifndef IRRIGATION_MANAGER_H
#define IRRIGATION_MANAGER_H
#include <cstdint>
#define PUMP_RELAY_PIN PB_4
#include "mbed.h"
#include "time.h"

enum alarm_duration {
  ALARM_DURATION_A,
  ALARM_DURATION_B

};

class IrrigationManager {
private:
  bool _irrigation_in_progress, _irrigation_scheduled;
  Timeout irrigation_stop_timer;
  DigitalOut _pump_relay;
  bool _initialized;
  EventQueue *_event;
  uint8_t _next_alarm;
  IrrigationManager();

  

public:
  static IrrigationManager &getIrrigationManager();
  void startIrrigation(uint32_t duration);
  void stopIrrigation();
  void attachEventQueue(EventQueue *event_p);
  void init();
  void releaseIrrigation();
  void scheduleNextIrrigationTime();
};

#endif