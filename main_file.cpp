
#include "EventSysData.hpp"
#include "EventKeyboardHandler.hpp"
#include "EventMouseClickHandler.hpp"
#include "EventMouseScrollHandler.hpp"
#include "EventGenerator.hpp"

#include <chrono>

int main()
{
    EventDispatcher evD;
    EventKeyboardHandler ev_handler1(evD);
    EventMouseScrollHandler ev_handler2(evD);
    EventMouseClickHandler ev_handler3(evD);

    EventGenerator ev_gen(evD);
    ev_gen.emitEvent();
    evD.startEventLoop();
}