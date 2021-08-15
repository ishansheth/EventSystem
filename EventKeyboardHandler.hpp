#pragma once

#include "EventDispatcher.hpp"
#include "EventSysData.hpp"
#include "IEvent.hpp"

class EventKeyboardHandler : public IEventHandler
{
    EventDispatcher& ev_d;
    std::function<void(std::shared_ptr<IEvent>)> eventhandler;

    public:
    EventKeyboardHandler(EventDispatcher& ev): ev_d(ev),eventhandler(std::bind(&EventKeyboardHandler::handleEvent,this,std::placeholders::_1))
    {
        ev_d.subscribeForEvent(EventTypes::Event_Keyboad, eventhandler);
    }

    void handleEvent(std::shared_ptr<IEvent> ev) override
    {        
        auto b = std::dynamic_pointer_cast<KeyboardPressEvent>(ev);    
        b->handled(true);
    }

};
