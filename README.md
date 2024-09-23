# Mooncake Event

Simple cpp event broker for mooncake framework

很嗨简单的 cpp 事件调度器实现

```cpp
// 事件回调
void onTeaTime1(EventArgs_t* args) { std::cout << "饮茶先啦\n"; }
void onTeaTime2(EventArgs_t* args) { std::cout << "啊?\n"; }

EventBroker eb;

// 监听事件
eb.startListen("三点几啦", onTeaTime1);
eb.startListen("三点几啦", onTeaTime2);

// 发布事件
eb.fire("三点几啦");
// 输出:
// 饮茶先啦
// 啊?

// 发布异步事件
for (int i = 0; i < 6; i++)
    eb.fireAsync("三点几啦");

// 处理异步事件
eb.handleAsyncEvents();
// 输出:
// 饮茶先啦
// 啊?
// x6
```

单例封装：

```cpp
// 监听事件
EventBroker::StartListen("三点几啦", onTeaTime1);
EventBroker::StartListen("三点几啦", onTeaTime2);

// 发布事件
EventBroker::Fire("三点几啦");
// 输出:
// 饮茶先啦
// 啊?

// ... 一勾样的
```

