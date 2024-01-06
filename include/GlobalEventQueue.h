#ifndef GLOBAL_EVENT_QUEUE_H
#define GLOBAL_EVENT_QUEUE_H
#include "mbed.h"

class GlobalEventQueue {
private:
  GlobalEventQueue();
  static EventQueue *_instance;
  static Thread _queue_thread;

public:
  static EventQueue *getGlobalEventQueue();
};

#endif