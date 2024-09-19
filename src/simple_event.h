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

    class EventBroker
    {
    private:
        struct Event_t
        {
            std::string type;
            EventArgs_t* args = nullptr;
        };

        typedef std::vector<std::function<void(EventArgs_t*)>> Listener_t;

        std::vector<Event_t> _event_queue;
        std::unordered_map<std::string, Listener_t> _listener_list;

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
         * @brief Listen to event
         *
         * @param eventType
         * @param onNotify
         * @return true
         * @return false
         */
        bool listen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify);

        /**
         * @brief Fire event into event queue
         *
         * @param eventType
         * @param args
         * @return true
         * @return false
         */
        bool fireAsync(const std::string& eventType, EventArgs_t* args = nullptr);

        /**
         * @brief Handle event queue
         *
         */
        void handleEventQueue();

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
         * @brief Listen event
         *
         * @param eventType
         * @param onNotify
         * @return true
         * @return false
         */
        static bool Listen(const std::string& eventType, std::function<void(EventArgs_t*)> onNotify);

        /**
         * @brief Fire event into event queue
         *
         * @param eventType
         * @param args
         * @return true
         * @return false
         */
        static bool FireAsync(const std::string& eventType, EventArgs_t* args = nullptr);

        /**
         * @brief Handle event queue and notify listeners
         *
         */
        static void HandleEventQueue();

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
