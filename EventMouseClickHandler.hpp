#pragma once

#include "EventDispatcher.hpp"
#include "IEvent.hpp"

class EventMouseClickHandler
{
    EventDispatcher& ev_d;
    std::function<void(std::shared_ptr<IEvent>)> eventhandler;

    public:
    EventMouseClickHandler(EventDispatcher& ev): ev_d(ev),eventhandler(std::bind(&EventMouseClickHandler::handleEvent,this,std::placeholders::_1))
    {
        ev_d.subscribeForEvent(EventTypes::Event_Click, eventhandler);
    }

    void handleEvent(std::shared_ptr<IEvent> ev)
    {
        auto b = std::dynamic_pointer_cast<MouseClickEvent>(ev);    
        b->handled(true);

    }

};