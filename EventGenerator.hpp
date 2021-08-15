#pragma once
#include "EventSysData.hpp"
#include "IEvent.hpp"
#include "EventDispatcher.hpp"
#include <memory>

class EventGenerator : public IEventEmitter
{
    EventDispatcher& ev_d;

    std::thread event_generator;
    unsigned int ev_index;
    public:
    EventGenerator(EventDispatcher& ev): ev_d(ev),ev_index(0)
    {}

    ~EventGenerator()
    {
        if(event_generator.joinable())
            event_generator.join();
    }

    void emitEvent() override
    {
        using namespace std::chrono_literals;
        
        event_generator = std::thread([this]()
        {
            for(;;)
            {                                
                std::this_thread::sleep_for(5000ms);
                if(ev_index % 3 == 0)
                {
                    KeyPressPayload pl;
                    pl.key_code = 100;
                    std::shared_ptr<IEvent> event = std::make_shared<KeyboardPressEvent>(pl);
                    ev_d.addEvent(event);
                }
                else if (ev_index % 3 == 1)
                {
                    MouseClickPayload pl;
                    pl.x = 10;
                    pl.y = 50;
                    std::shared_ptr<IEvent> event = std::make_shared<MouseClickEvent>(pl);
                    ev_d.addEvent(event);

                }
                else if (ev_index % 3 == 2)
                {
                    MouseDragPayload pl;
                    pl.x = 100;
                    pl.y = 50;
                    std::shared_ptr<IEvent> event = std::make_shared<MouseScrollEvent>(pl);
                    ev_d.addEvent(event);
                }

                ev_index++;
            }
        });

    }
};
