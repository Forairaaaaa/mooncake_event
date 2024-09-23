/**
 * @file mooncake_event.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mooncake_event.h"

using namespace Mooncake;

bool EventBroker::fire(const std::string& eventType, EventArgs_t* args)
{
    if (eventType.empty())
        return false;

    // Find event
    auto event_pair = _event_map.find(eventType);
    if (event_pair != _event_map.end())
    {
        // Invoke listener callbacks
        for (const auto& listener : event_pair->second)
            listener.callback((args));
    }
    else
        return false;

    return true;
}

int EventBroker::startListen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify)
{
    if (eventType.empty())
        return false;

    if (onNotify == nullptr)
        return false;

    // Create listener info and hash in
    _next_listener_id++;
    _event_map[eventType].push_back({_next_listener_id, onNotify});

    return _next_listener_id;
}

bool EventBroker::stopListen(const std::string& eventType, int listenerId)
{
    if (eventType.empty())
        return false;

    // Find event
    auto event_pair = _event_map.find(eventType);
    if (event_pair != _event_map.end())
    {
        // Find listener
        for (auto listener = event_pair->second.begin(); listener != event_pair->second.end(); listener++)
        {
            if (listener->id == listenerId)
            {
                event_pair->second.erase(listener);
                return true;
            }
        }
    }

    return false;
}

bool EventBroker::fireAsync(const std::string& eventType, EventArgs_t* args)
{
    if (eventType.empty())
        return false;

    // Queue in
    AsyncEvent_t new_event;
    new_event.type = eventType;
    new_event.args = args;
    _async_event_queue.push_back(new_event);

    return true;
}

void EventBroker::handleAsyncEvents()
{
    for (const auto& async_event : _async_event_queue)
    {
        // Find event
        auto event_pair = _event_map.find(async_event.type);
        if (event_pair != _event_map.end())
        {
            // Invoke listener callbacks
            for (const auto& i : event_pair->second)
                i.callback(async_event.args);
        }
    }

    // Pop all shit
    _async_event_queue.clear();
}

void EventBroker::reset()
{
    _async_event_queue.clear();
    _event_map.clear();
    _next_listener_id = 0;
}