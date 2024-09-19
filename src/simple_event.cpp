/**
 * @file simple_event.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "simple_event.h"

using namespace SimpleEvent;

bool EventManager::fire(const std::string& eventType, EventArgs_t* args, bool handleAtOnce)
{
    if (eventType.empty())
        return false;

    // Handle right away
    if (handleAtOnce)
    {
        auto iter = _listener_list.find(eventType);
        if (iter != _listener_list.end())
        {
            // Invoke callbacks
            for (const auto& i : iter->second)
                i(args);
        }

        return true;
    }

    // Stack new event
    Event_t new_event;
    new_event.type = eventType;
    new_event.args = args;
    _event_queue.push_back(new_event);

    return true;
}

bool EventManager::listen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify)
{
    if (eventType.empty())
        return false;

    if (onNotify == nullptr)
        return false;

    _listener_list[eventType].push_back(onNotify);

    return true;
}

void EventManager::update()
{
    for (const auto& event : _event_queue)
    {
        auto iter = _listener_list.find(event.type);
        if (iter != _listener_list.end())
        {
            // Invoke callbacks
            for (const auto& i : iter->second)
                i(event.args);
        }
    }

    // Pop!
    _event_queue.clear();
}

void EventManager::reset()
{
    _event_queue.clear();
    _listener_list.clear();
}
