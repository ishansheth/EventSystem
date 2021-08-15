#pragma once

#include <functional>
#include <thread>
#include <pthread.h>
#include <cstring>
#include <iostream>

static sched_param scheduling_param;

enum class EventTypes
{
    None = 0,
    Event_Keyboad = 1,
    Event_Mouse = 2,
    Event_Drag = 3,
    Event_Click = 4,
    Event_Scroll = 5    
};


struct MouseClickPayload 
{
    double x,y;
};

struct KeyPressPayload 
{
    double key_code;
};

struct MouseDragPayload
{
    double x,y;
};


std::string eventTypesString(EventTypes ev)
{
    switch(ev)
    {
        case EventTypes::None:
            return "None";
        case EventTypes::Event_Keyboad:
            return "Event_Keyboard";
        case EventTypes::Event_Mouse:
            return "Event_Mouse";
        case EventTypes::Event_Drag:
            return "Event_Drag";
        case EventTypes::Event_Click:
            return "Event_Click";
        case EventTypes::Event_Scroll:
            return "Event_Scroll";        
        default:
            return "";
    }
}


void setScheduling(std::thread& th, int policy, int priority)
{
    scheduling_param.sched_priority = priority;
    if(pthread_setschedparam(th.native_handle(),policy,&scheduling_param))
        std::cerr<<"Failed to set thread scheduling:"<<std::strerror(errno)<<std::endl;
}
