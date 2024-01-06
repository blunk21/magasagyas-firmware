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
  set_time(1704530047);
  // instantiate singletons
  SystemConfig::getSystemConfig();
  EventQueue *global_queue = GlobalEventQueue::getGlobalEventQueue();

  global_queue->call_every(
      std::chrono::seconds(SENSOR_READ_INTERVAL_SECONDS),
      callback(&SensorData::getSensorData(), &SensorData::readSensorData));

  while (true) {

    ThisThread::sleep_for(1s);
  }
}
