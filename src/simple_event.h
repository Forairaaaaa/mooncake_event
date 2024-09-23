/**
 * @file simple_event.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace SimpleEvent
{
    /**
     * @brief Override to create your own argument shit
     *
     */
    struct EventArgs_t
    {
    public:
        virtual ~EventArgs_t() = default;
    };

    /**
     * @brief A event broker to handle event firing and listening and shit
     *
     */
    class EventBroker
    {
    private:
        /* -------------------------------- Listener -------------------------------- */
        struct Listener_t
        {
            int id;
            std::function<void(EventArgs_t*)> callback;
        };

        typedef std::vector<Listener_t> ListenerList_t;

        int _next_listener_id = 0;
        std::unordered_map<std::string, ListenerList_t> _event_map;

        /* ------------------------------- Async fire ------------------------------- */
        struct AsyncEvent_t
        {
            std::string type;
            EventArgs_t* args = nullptr;
        };

        std::vector<AsyncEvent_t> _async_event_queue;

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
         * @param listenerId
         * @return true
         * @return false
         */
        bool stopListen(const std::string& eventType, int listenerId);

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

        /* -------------------------------------------------------------------------- */
        /*                               Singleton wrap                               */
        /* -------------------------------------------------------------------------- */
    public:
        /**
         * @brief Fire event
         *
         * @param eventType
         * @param args
         * @return true
         * @return false
         */
        static bool Fire(const std::string& eventType, EventArgs_t* args = nullptr);

        /**
         * @brief Start listening event, return listener id
         *
         * @param eventType
         * @param onNotify
         * @return int
         */
        static int StartListen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify);

        /**
         * @brief Stop listening event
         *
         * @param eventType
         * @param listenerId
         * @return true
         * @return false
         */
        static bool StopListen(const std::string& eventType, int listenerId);

        /**
         * @brief Fire event into async event queue
         *
         * @param eventType
         * @param args
         * @return true
         * @return false
         */
        static bool FireAsync(const std::string& eventType, EventArgs_t* args = nullptr);

        /**
         * @brief Handle easync event queue and clear
         *
         */
        static void HandleAsyncEvents();

        /**
         * @brief Reset and clear all shit
         *
         */
        static void Reset();

        /**
         * @brief Destroy all shit that singleton taking
         *
         */
        static void Destroy();
    };
} // namespace SimpleEvent
