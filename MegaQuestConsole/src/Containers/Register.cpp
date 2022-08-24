#include "Containers/Register.hpp"

Register& Register::Instance()
{
	static Register instance;
	return instance;
}

void Register::RegisterContext(Context& context)
{
	for (auto initializer : _initializers) {
		initializer(context);
	}
}

void Register::AddInitializer(const Initializer& initializer)
{
	_initializers.push_back(initializer);
}
