#include "GlobalEventQueue.h"


EventQueue* GlobalEventQueue::_instance = nullptr;
Thread GlobalEventQueue::_queue_thread;

GlobalEventQueue::GlobalEventQueue(){}

EventQueue *GlobalEventQueue::getGlobalEventQueue(){
    if(!_instance)
    {
        _instance = new EventQueue(32*EVENTS_EVENT_SIZE);
        _queue_thread.start(callback(_instance,&EventQueue::dispatch_forever));
    }
    return _instance;
}