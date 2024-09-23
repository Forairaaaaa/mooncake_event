/**
 * @file basic.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <mooncake_event.h>
#include <iostream>

using namespace Mooncake;

// 事件回调
void onTeaTime1(EventArgs_t* args) { std::cout << "饮茶先啦\n"; }
void onTeaTime2(EventArgs_t* args) { std::cout << "啊?\n"; }

int main()
{
    EventBroker eb;

    // 监听事件
    eb.startListen("三点几啦", onTeaTime1);
    eb.startListen("三点几啦", onTeaTime2);

    // 发布事件
    std::cout << ">> firing..\n";
    eb.fire("三点几啦");
    // 输出:
    // 饮茶先啦
    // 啊?

    // 发布异步事件
    std::cout << ">> firing..\n";
    for (int i = 0; i < 6; i++)
        eb.fireAsync("三点几啦");

    // 处理异步事件
    std::cout << ">> handling..\n";
    eb.handleAsyncEvents();
    // 输出:
    // 饮茶先啦
    // 啊?
    // x6

    return 0;
}
