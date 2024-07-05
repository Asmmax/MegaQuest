#pragma once
#include <memory>

namespace QuestCore
{
	template <typename T>
	class IInput
	{
	public:

		virtual T* Get() const = 0;
	};
}
