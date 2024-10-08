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

`fireAsync` 并非线程异步实现，只是把事件暂时队列起来，在调用 `handleAsyncEvents` 时再统一处理

如果需要线程异步，可以把 `handleAsyncEvents` 放线程里，给实例加锁就行

#### 全局单例：

```cpp
// 监听事件
GetEventBroker().startListen("三点几啦", onTeaTime1);
GetEventBroker().startListen("三点几啦", onTeaTime2);

// 发布事件
GetEventBroker().fire("三点几啦");
// 输出:
// 饮茶先啦
// 啊?

// ... 一勾样的
```

#### 数据交换：

提供了事件参数的基类，以便派生自定义参数：

```cpp
/**
 * @brief Override to create your own argument shit
 *
 */
struct EventArgs_t
{
public:
    virtual ~EventArgs_t() = default;
};
```

所以可以实现类似 `发布/订阅` 的交换模式：

```cpp
// 订阅者
GetEventBroker().startListen("topic-player-status", onPlayerStatusUpdate);

// 派生事件参数
struct PlayerStatus_t : public EventArgs_t
{
    int hp;
    // ...
};

// 发布者
player_status.hp = 66;
GetEventBroker().fire("topic-player-hp", &player_status);
```

或者反过来 `请求/应答` 模式：

```cpp
// 应答服务
GetEventBroker().startListen("service-player-status", [](EventArgs_t* args){
    auto player_status = (PlayerStatus_t*)args;
    player_status.hp = 233;
});

// 发送请求
GetEventBroker().fire("service-player-status", &player_status);
```
