#pragma once

#include "EventSysData.hpp"

class IEvent
{
    protected:
        bool isHandled;
    public:
        virtual ~IEvent() = default;
        virtual EventTypes getEventType() = 0;
};


class IEventEmitter
{
    public:
        virtual ~IEventEmitter() = default;
        virtual void emitEvent() = 0;
};

class IEventHandler
{
    public:
        virtual ~IEventHandler() = default;
        virtual void handleEvent(std::shared_ptr<IEvent>) = 0;    
};


class KeyboardPressEvent : public IEvent
{
    KeyPressPayload pl;

    public:
    KeyboardPressEvent(const KeyPressPayload& payload) : pl(payload)
    {}

    virtual EventTypes getEventType() override { return EventTypes::Event_Keyboad;}

    KeyPressPayload getEventPayload()
    {
        return pl;
    }

    void handled(bool value) {isHandled = value;}
};


class MouseClickEvent : public IEvent
{
    MouseClickPayload pl;

    public:
    MouseClickEvent(const MouseClickPayload& payload) : pl(payload)
    {}

    virtual EventTypes getEventType() override { return EventTypes::Event_Click;}

    MouseClickPayload getEventPayload()
    {
        return pl;
    }

    void handled(bool value) {isHandled = value;}

};

class MouseDragEvent : public IEvent
{
    MouseDragPayload pl;

    public:
    MouseDragEvent(const MouseDragPayload& payload) : pl(payload)
    {}

    virtual EventTypes getEventType() override { return EventTypes::Event_Drag;}

    MouseDragPayload getEventPayload()
    {
        return pl;
    }

    void handled(bool value) {isHandled = value;}

};


class MouseScrollEvent : public IEvent
{
    MouseDragPayload pl;

    public:
    MouseScrollEvent(const MouseDragPayload& payload) : pl(payload)
    {}

    virtual EventTypes getEventType() override { return EventTypes::Event_Scroll;}

    MouseDragPayload getEventPayload()
    {
        return pl;
    }
    
    void handled(bool value) {isHandled = value;}

};