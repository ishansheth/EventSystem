#pragma once

#include "EventDispatcher.hpp"
#include "IEvent.hpp"

class EventMouseScrollHandler
{
    EventDispatcher& ev_d;
    std::function<void(std::shared_ptr<IEvent>)> eventhandler;

    public:
    EventMouseScrollHandler(EventDispatcher& ev): ev_d(ev),eventhandler(std::bind(&EventMouseScrollHandler::handleEvent,this,std::placeholders::_1))
    {
        ev_d.subscribeForEvent(EventTypes::Event_Scroll, eventhandler);
    }

    void handleEvent(std::shared_ptr<IEvent> ev)
    {
        auto b = std::dynamic_pointer_cast<MouseScrollEvent>(ev);    
        b->handled(true);
    }

};