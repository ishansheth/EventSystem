#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include "EventSysData.hpp"
#include <chrono>
#include <map>

struct EventStat
{
    unsigned int totalEvents;
    std::map<EventTypes,unsigned int> eventNum;    
    unsigned int totalHandlers;
    std::size_t kb_eventq_size;
    std::size_t mouse_eventq_size;
};

class EventStatistics
{
    std::mutex stat_mutex;
    EventStat event_stat;
    std::thread display_stat;
    std::ostream& outStream;    

    public:
    EventStatistics() : outStream(std::cout)
    {

        event_stat.eventNum[EventTypes::None] = 0;
        event_stat.eventNum[EventTypes::Event_Keyboad] = 0;
        event_stat.eventNum[EventTypes::Event_Mouse] = 0;
        event_stat.eventNum[EventTypes::Event_Drag] = 0;
        event_stat.eventNum[EventTypes::Event_Click] = 0;
        event_stat.eventNum[EventTypes::Event_Scroll] = 0;
        event_stat.totalEvents = 0;

        event_stat.mouse_eventq_size = 0;
        event_stat.kb_eventq_size = 0;
    }

    ~EventStatistics()
    {
        if(display_stat.joinable())
            display_stat.join();
    }

    void displayStatistics()
    {
        using namespace std::chrono_literals;

        display_stat = std::thread([this]()
        {
            for(;;)
            {
                int upSteps = 1;
                std::this_thread::sleep_for(1000ms);
                std::lock_guard<std::mutex> lock(stat_mutex);
                outStream << "Total Events:"<<event_stat.totalEvents<<std::endl;
                for(auto& element: event_stat.eventNum)
                {
                    if(element.second > 0)
                    {
                        outStream <<"\t"<<eventTypesString(element.first)<<":"<<element.second<<"|"<<std::endl;
                        upSteps++;
                    }
                }

                for(unsigned int i = 0; i < upSteps; i++)
                    outStream << "\x1b[A";                

                outStream << "\t\t\t\t  |  Mouse Events Queue Size:"<< event_stat.mouse_eventq_size << std::endl;
                outStream << "\t\t\t\t  |  Keyboard Events Queue Size:"<< event_stat.kb_eventq_size << std::endl;

                outStream << "\x1b[A";                
                outStream << "\x1b[A";                

            }
        });
    }

    void updateMouseQSize(std::size_t sz)
    {
        event_stat.mouse_eventq_size = sz;
    }

    void updateKeyboadQSize(std::size_t sz)
    {
        event_stat.kb_eventq_size = sz;
    }

    void updateEvent(EventTypes e)
    {
        std::lock_guard<std::mutex> lock(stat_mutex);
        event_stat.totalEvents++;
        event_stat.eventNum[e]++;
    }
    
};
