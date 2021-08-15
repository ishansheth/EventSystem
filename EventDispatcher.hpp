#pragma once
#include <map>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>
#include <memory>

#include "EventSysData.hpp"
#include "IEvent.hpp"
#include "EventStatistics.hpp"

using EventCallback = std::function<void(std::shared_ptr<IEvent>)>;

class EventDispatcher
{    
    std::map<EventTypes,std::vector<EventCallback>> event_handler_q;

    std::queue<std::shared_ptr<IEvent>> kb_event_q;
    std::queue<std::shared_ptr<IEvent>> mouse_event_q;

    std::mutex kb_event_q_mtx;
    std::mutex mouse_event_q_mtx;

    std::thread kb_event_loop;
    std::thread mouse_event_loop;

    EventStatistics evStat;

    public:
    EventDispatcher()
    {}

    ~EventDispatcher()
    {
        if(kb_event_loop.joinable())
            kb_event_loop.join();

        if(mouse_event_loop.joinable())
            mouse_event_loop.join();        
    }

    void startEventLoop()
    {
        evStat.displayStatistics();

        using namespace std::chrono_literals;

        kb_event_loop = std::thread([this]()
        {
            for(;;)
            {
                std::this_thread::sleep_for(2000ms);
                std::shared_ptr<IEvent> gen_ev; 
                {
                    std::lock_guard<std::mutex> lock(kb_event_q_mtx);
                    if(!kb_event_q.empty())
                    {
                        evStat.updateKeyboadQSize(kb_event_q.size());
                        gen_ev = kb_event_q.front();
                        kb_event_q.pop();
                    }
                }

                if(gen_ev.get())
                {                
                    if(event_handler_q.count(gen_ev->getEventType()) > 0)
                    {
                        for(auto& element: event_handler_q[gen_ev->getEventType()])
                        {
                            element(gen_ev);
                        }
                    }
                }
            }
        });


        mouse_event_loop = std::thread([this]()
        {
            for(;;)
            {
                std::this_thread::sleep_for(2000ms);
                std::shared_ptr<IEvent> gen_ev; 
                {
                    std::lock_guard<std::mutex> lock(mouse_event_q_mtx);
                    if(!mouse_event_q.empty())
                    {
                        evStat.updateMouseQSize(mouse_event_q.size());

                        gen_ev = mouse_event_q.front();
                        mouse_event_q.pop();
                    }
                }

                if(gen_ev.get())
                {                
                    if(event_handler_q.count(gen_ev->getEventType()) > 0)
                    {
                        for(auto& element: event_handler_q[gen_ev->getEventType()])
                        {
                            element(gen_ev);
                        }
                    }
                }
            }

        });
    }   

    void addEvent(std::shared_ptr<IEvent>& ev)
    {
        if(ev->getEventType() == EventTypes::Event_Keyboad)
        {
            std::lock_guard<std::mutex> lock(kb_event_q_mtx);
            kb_event_q.push(ev);
            evStat.updateKeyboadQSize(kb_event_q.size());
            evStat.updateEvent(ev->getEventType());
        }
        else if(ev->getEventType() == EventTypes::Event_Scroll || 
        ev->getEventType() == EventTypes::Event_Click)
        {
            std::lock_guard<std::mutex> lock(mouse_event_q_mtx);
            mouse_event_q.push(ev);
            evStat.updateMouseQSize(mouse_event_q.size());
            evStat.updateEvent(ev->getEventType());
        }
    }

    void subscribeForEvent(EventTypes ev, std::function<void(std::shared_ptr<IEvent>)>& callback)
    {
        event_handler_q[ev].push_back(callback);
    }

};
