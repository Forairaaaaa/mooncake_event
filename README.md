# Mooncake

Simple cpp event broker

很嗨简单的 cpp 事件调度器实现

```cpp
// 事件回调
void onTeaTime1(EventArgs_t* args) { std::cout << "饮茶先啦\n"; }
void onTeaTime2(EventArgs_t* args) { std::cout << "啊?\n"; }

EventBroker eb;

// 监听事件
eb.listen("三点几啦", onTeaTime1);
eb.listen("三点几啦", onTeaTime2);

// 发布事件
eb.fire("三点几啦");
// 输出:
// 饮茶先啦
// 啊?

// 发布事件到事件队列
for (int i = 0; i < 6; i++)
    eb.fireAsync("三点几啦");

// 处理事件队列
eb.handleEventQueue();
// 输出:
// 饮茶先啦
// 啊?
// x6
```

单例封装：

```cpp
// 监听事件
EventBroker::Listen("三点几啦", onTeaTime1);
EventBroker::Listen("三点几啦", onTeaTime2);

// 发布事件
EventBroker::Fire("三点几啦");
// 输出:
// 饮茶先啦
// 啊?

// ... 一勾样的
```

