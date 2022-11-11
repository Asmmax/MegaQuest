#pragma once
#include <functional>
#include <vector>

class Context;

class Register
{
	using Initializer = std::function<void(Context&)>;
public:
	static Register& Instance()
	{
		static Register instance;
		return instance;
	}

	void RegisterContext(Context& context)
	{
		for (auto initializer : _initializers) {
			initializer(context);
		}
	}

	void AddInitializer(const Initializer& initializer)
	{
		_initializers.push_back(initializer);
	}
private:
	std::vector<Initializer> _initializers;
};
