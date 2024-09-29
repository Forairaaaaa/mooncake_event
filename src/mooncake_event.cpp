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

using namespace mooncake;

bool EventBroker::fire(const std::string& eventType, EventArgs_t* args)
{
    if (eventType.empty())
        return false;

    // Find event
    auto event_pair = _event_map.find(eventType);
    if (event_pair != _event_map.end()) {
        // Invoke listener callbacks
        for (const auto& listener : event_pair->second)
            listener.callback((args));
    } else
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
    Listener_t new_listener;
    new_listener.id = get_next_listener_id();
    new_listener.callback = onNotify;
    _event_map[eventType].push_back(new_listener);

    return new_listener.id;
}

bool EventBroker::stopListen(const std::string& eventType, int listenerID)
{
    if (eventType.empty())
        return false;

    // Find event
    auto event_pair = _event_map.find(eventType);
    if (event_pair != _event_map.end()) {
        // Find listener
        for (auto listener = event_pair->second.begin(); listener != event_pair->second.end(); listener++) {
            if (listener->id == listenerID) {
                event_pair->second.erase(listener);
                _available_ability_id_list.push_back(listenerID);
                return true;
            }
        }
    }

    return false;
}

int EventBroker::getListenerNum(const std::string& eventType)
{
    if (eventType.empty())
        return 0;

    // Find event
    auto event_pair = _event_map.find(eventType);
    if (event_pair != _event_map.end()) {
        return event_pair->second.size();
    }

    return 0;
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
    for (const auto& async_event : _async_event_queue) {
        // Find event
        auto event_pair = _event_map.find(async_event.type);
        if (event_pair != _event_map.end()) {
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
    _available_ability_id_list.clear();
    _next_listener_id = 0;
}

int EventBroker::get_next_listener_id()
{
    int next_listener_id = -1;

    // 检查可用 ID 列表
    if (!_available_ability_id_list.empty()) {
        next_listener_id = _available_ability_id_list.front();
        _available_ability_id_list.erase(_available_ability_id_list.begin());
        return next_listener_id;
    }

    // 如果没有，继续自加
    next_listener_id = _next_listener_id;
    _next_listener_id++;

    return next_listener_id;
}
