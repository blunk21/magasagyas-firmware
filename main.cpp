#include "DataManager.h"
#include "SensorData.h"
#include "mbed.h"
#include <cstddef>
#include <cstdint>
#include <cstdio>

void save_sensor_data(void){
    DataManager::getDataManager().storeSensorData();
}


// main() runs in its own thread in the OS
int main() {
    Thread dataManagerThread(osPriorityHigh,8192,nullptr,"datamanager_thread");
    DataManager::getDataManager();
    SensorData &sensors = SensorData::getSensorData();
    dataManagerThread.start(save_sensor_data);
    
    while (true) {
        sensors.readSensorData();
        ThisThread::sleep_for(5s);
    }
  
}
