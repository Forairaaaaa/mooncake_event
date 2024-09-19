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

bool EventBroker::fire(const std::string& eventType, EventArgs_t* args)
{
    if (eventType.empty())
        return false;

    // Find listener
    auto iter = _listener_list.find(eventType);
    if (iter != _listener_list.end())
    {
        // Invoke callbacks
        for (const auto& i : iter->second)
            i(args);
    }

    return true;
}

bool EventBroker::listen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify)
{
    if (eventType.empty())
        return false;

    if (onNotify == nullptr)
        return false;

    _listener_list[eventType].push_back(onNotify);

    return true;
}

bool EventBroker::fireAsync(const std::string& eventType, EventArgs_t* args)
{
    if (eventType.empty())
        return false;

    // Queue in
    Event_t new_event;
    new_event.type = eventType;
    new_event.args = args;
    _event_queue.push_back(new_event);

    return true;
}

void EventBroker::handleEventQueue()
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

void EventBroker::reset()
{
    _event_queue.clear();
    _listener_list.clear();
}
