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
#include "simple_event.h"

using namespace SimpleEvent;

static EventBroker* _event_manger = nullptr;

static EventBroker* _get()
{
    if (_event_manger == nullptr)
        _event_manger = new SimpleEvent::EventBroker;
    return _event_manger;
}

bool EventBroker::Fire(const std::string& eventType, EventArgs_t* args, bool handleAtOnce)
{
    return _get()->fire(eventType, args, handleAtOnce);
}

bool EventBroker::Listen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify)
{
    return _get()->listen(eventType, onNotify);
}

void EventBroker::Update() { _get()->update(); }

void EventBroker::Reset() { _get()->reset(); }

void EventBroker::Destroy()
{
    if (_event_manger != nullptr)
        return;

    delete _event_manger;
    _event_manger = nullptr;
}
