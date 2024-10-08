/**
 * @file mooncake_event.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace mooncake {

/**
 * @brief Override to create your own argument shit
 *
 */
struct EventArgs_t {
public:
    virtual ~EventArgs_t() = default;
};

/**
 * @brief A event broker to handle event firing and listening and shit
 *
 */
class EventBroker {

public:
    /**
     * @brief Fire event
     *
     * @param eventType
     * @param args
     * @return true
     * @return false
     */
    bool fire(const std::string& eventType, EventArgs_t* args = nullptr);

    /**
     * @brief Start listening event, return listener id
     *
     * @param eventType
     * @param onNotify
     * @return int
     */
    int startListen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify);

    /**
     * @brief Stop listening event
     *
     * @param eventType
     * @param listenerID
     * @return true
     * @return false
     */
    bool stopListen(const std::string& eventType, int listenerID);

    /**
     * @brief Get how many shit is listening the target event
     *
     * @param eventType
     * @return int
     */
    int getListenerNum(const std::string& eventType);

    /**
     * @brief Fire event into async event queue
     *
     * @param eventType
     * @param args
     * @return true
     * @return false
     */
    bool fireAsync(const std::string& eventType, EventArgs_t* args = nullptr);

    /**
     * @brief Handle easync event queue and clear
     *
     */
    void handleAsyncEvents();

    /**
     * @brief Reset and clear all shit
     *
     */
    void reset();

private:
    struct Listener_t {
        int id;
        std::function<void(EventArgs_t*)> callback;
    };

    typedef std::vector<Listener_t> ListenerList_t;

    struct AsyncEvent_t {
        std::string type;
        EventArgs_t* args = nullptr;
    };

    int _next_listener_id = 0;
    std::vector<int> _available_ability_id_list;
    std::unordered_map<std::string, ListenerList_t> _event_map;
    std::vector<AsyncEvent_t> _async_event_queue;

    int get_next_listener_id();
};

/* -------------------------------------------------------------------------- */
/*                                  Singleton                                 */
/* -------------------------------------------------------------------------- */
// 全局单例

/**
 * @brief 获取 EventBroker 单例
 *
 * @return EventBroker&
 */
EventBroker& GetEventBroker();

/**
 * @brief 销毁 EventBroker 单例
 *
 */
void DestroyEventBroker();

} // namespace mooncake
