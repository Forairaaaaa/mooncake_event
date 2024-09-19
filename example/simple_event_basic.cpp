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
    EventManager em;

    // Listen to the event
    em.listen("三点几啦", onTeaTime1);
    em.listen("三点几啦", onTeaTime2);

    // Fire at once with no argument
    em.fire("三点几啦", nullptr, true);

    // Fire events into event queue
    std::cout << "firing..\n";
    for (int i = 0; i < 6; i++)
        em.fire("三点几啦");

    // Handle by update
    std::cout << "handling..\n";
    em.update();

    return 0;
}
