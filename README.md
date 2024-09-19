# SimpleEvent

Simple cpp event broker

很嗨简单的 cpp 事件调度器实现

```cpp
// 事件回调
void onTeaTime1(EventArgs_t* args) { std::cout << "饮茶先啦\n"; }
void onTeaTime2(EventArgs_t* args) { std::cout << "啊?\n"; }

EventBroker em;

// 监听事件
em.listen("三点几啦", onTeaTime1);
em.listen("三点几啦", onTeaTime2);

// 发布事件，不带参，并且要求立即触发
em.fire("三点几啦", nullptr, true);
// 输出:
// 饮茶先啦
// 啊?

// 发布到事件队列（不立即触发）
std::cout << "firing..\n";
for (int i = 0; i < 6; i++)
    em.fire("三点几啦");

// 用 update() 统一触发
std::cout << "handling..\n";
em.update();
// 输出:
// 饮茶先啦
// 啊?
// x6
```

单例封装：

```cpp
void onTeaTime1(EventArgs_t* args) { std::cout << "饮茶先啦\n"; }
void onTeaTime2(EventArgs_t* args) { std::cout << "啊?\n"; }

EventBroker::Listen("三点几啦", onTeaTime1);
EventBroker::Listen("三点几啦", onTeaTime2);

EventBroker::Fire("三点几啦", nullptr, true);
// 输出:
// 饮茶先啦
// 啊?

// ... 一勾样的
```

