#pragma once
#include <functional>
#include <vector>

class Context;

class Register
{
	using Initializer = std::function<void(Context&)>;
public:
	static Register& Instance();

	void RegisterContext(Context& context);
	void AddInitializer(const Initializer& initializer);
private:
	std::vector<Initializer> _initializers;
};
