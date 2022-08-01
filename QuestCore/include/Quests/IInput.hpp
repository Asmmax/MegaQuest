#pragma once
#include <memory>

namespace QuestCore
{
	template <typename T>
	class IInput
	{
		using TPtr = std::shared_ptr<T>;
	public:

		virtual TPtr Get() const = 0;
	};
}
