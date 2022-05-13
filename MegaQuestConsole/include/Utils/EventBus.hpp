#pragma once
#include <functional>
#include <vector>

template<typename... Args>
class EventBus
{
	using Subscription = std::function<void(Args...)>;

public:
	void Subscribe(const Subscription& subsription);
	void Send(Args&... args);

private:
	std::vector<Subscription> _subsriptions;
};

template<typename... Args>
void EventBus<Args...>::Subscribe(const Subscription& subsription)
{
	_subsriptions.push_back(subsription);
}

template<typename... Args>
void EventBus<Args...>::Send(Args&... args)
{
	for (auto& subsription : _subsriptions) {
		subsription(args...);
	}
}
