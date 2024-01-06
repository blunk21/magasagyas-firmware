#include "DataManager.h"
#include "GlobalEventQueue.h"
#include "IrrigationManager.h"
#include "SensorData.h"
#include "SystemConfig.h"

#include "mbed.h"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <ctime>

int main() {
  set_time(1704520800);
  // instantiate singletons
  SystemConfig::getSystemConfig();
  EventQueue *global_queue = GlobalEventQueue::getGlobalEventQueue();
  IrrigationManager::getIrrigationManager();
  global_queue->call_every(
      60s, callback(&IrrigationManager::getIrrigationManager(),
                    &IrrigationManager::scheduleNextIrrigationTime));
  global_queue->call_every(
      std::chrono::seconds(SENSOR_READ_INTERVAL_SECONDS),
      callback(&SensorData::getSensorData(), &SensorData::readSensorData));
  uint32_t tick_counter = 0;
  while (true) {

    ThisThread::sleep_for(1s);
    tick_counter++;
    if (tick_counter % 5 == 0) {
      printf("Ticks %d\n", tick_counter);
    }
  }
}
