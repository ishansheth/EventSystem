cmake_minimum_required(VERSION 3.0)


set(CMAKE_CXX_KNOWN_FEATURES 14)

add_executable(eventSys 
main_file.cpp 
EventDispatcher.hpp 
EventGenerator.hpp 
EventKeyboardHandler.hpp 
EventMouseClickHandler.hpp
EventMouseScrollHandler.hpp
EventSysData.hpp
IEvent.hpp
)

target_link_libraries(eventSys pthread)