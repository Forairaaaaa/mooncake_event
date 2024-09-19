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

// 事件回调
void onTeaTime1(EventArgs_t* args) { std::cout << "饮茶先啦\n"; }
void onTeaTime2(EventArgs_t* args) { std::cout << "啊?\n"; }

int main()
{
    EventBroker em;

    // 监听事件
    em.listen("三点几啦", onTeaTime1);
    em.listen("三点几啦", onTeaTime2);

    // 发布事件
    std::cout << ">> firing..\n";
    em.fire("三点几啦");
    // 输出:
    // 饮茶先啦
    // 啊?

    // 发布事件到事件队列
    std::cout << ">> firing..\n";
    for (int i = 0; i < 6; i++)
        em.fireAsync("三点几啦");

    // 处理事件队列
    std::cout << ">> handling..\n";
    em.handleEventQueue();
    // 输出:
    // 饮茶先啦
    // 啊?
    // x6

    return 0;
}
