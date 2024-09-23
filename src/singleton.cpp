/**
 * @file singleton.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mooncake_event.h"

using namespace Mooncake;

static EventBroker* _event_manger = nullptr;

static EventBroker* _get()
{
    if (_event_manger == nullptr)
        _event_manger = new Mooncake::EventBroker;
    return _event_manger;
}

bool EventBroker::Fire(const std::string& eventType, EventArgs_t* args) { return _get()->fire(eventType, args); }

bool EventBroker::FireAsync(const std::string& eventType, EventArgs_t* args) { return _get()->fireAsync(eventType, args); }

int EventBroker::StartListen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify)
{
    return _get()->startListen(eventType, onNotify);
}

bool EventBroker::StopListen(const std::string& eventType, int listenerId) { return _get()->stopListen(eventType, listenerId); }

void EventBroker::HandleAsyncEvents() { _get()->handleAsyncEvents(); }

void EventBroker::Reset() { _get()->reset(); }

void EventBroker::Destroy()
{
    if (_event_manger != nullptr)
        return;

    delete _event_manger;
    _event_manger = nullptr;
}
