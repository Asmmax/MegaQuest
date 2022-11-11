#pragma once
#include "Containers/Register.hpp"

template<typename Type>
class RegisterBinder
{
public:
	RegisterBinder()
	{
		Register::Instance().AddInitializer([](Context& context) {
			Init(context); 
			});
	}
private:
	static void Init(Context& context);
};
