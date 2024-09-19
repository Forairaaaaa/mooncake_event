/**
 * @file simple_event_basic.cpp
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
    EventBroker em;

    // Listen to the event
    em.listen("三点几啦", onTeaTime1);
    em.listen("三点几啦", onTeaTime2);

    // Fire event
    em.fire("三点几啦");
    // Output:
    // 饮茶先啦
    // 啊?

    // Fire events into event queue, without argument (nullptr)
    std::cout << "firing..\n";
    for (int i = 0; i < 6; i++)
        em.fire("三点几啦", nullptr, false);

    // Handle by update
    std::cout << "handling..\n";
    em.update();
    // Output:
    // 饮茶先啦
    // 啊?
    // x6

    return 0;
}
