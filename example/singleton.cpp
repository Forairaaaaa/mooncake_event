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
#include <simple_event.h>
#include <iostream>

using namespace SimpleEvent;

void onTeaTime1(EventArgs_t* args) { std::cout << "饮茶先啦\n"; }
void onTeaTime2(EventArgs_t* args) { std::cout << "啊?\n"; }

int main()
{
    // Listen to the event
    EventBroker::Listen("三点几啦", onTeaTime1);
    EventBroker::Listen("三点几啦", onTeaTime2);

    // Fire at once with no argument
    EventBroker::Fire("三点几啦", nullptr, true);

    // Fire events into event queue
    std::cout << "firing..\n";
    for (int i = 0; i < 6; i++)
        EventBroker::Fire("三点几啦");

    // Handle by update
    std::cout << "handling..\n";
    EventBroker::Update();

    EventBroker::Destroy();

    return 0;
}