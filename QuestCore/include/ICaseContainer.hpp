#pragma once
#include "Case.hpp"
#include <string>
#include <memory>
#include <vector>

namespace QuestCore
{
	class IButtonGroup;

	/// @serializable @shared @abstract
	class ICaseContainer
	{
	public:
		using Ptr = std::shared_ptr<ICaseContainer>;
		using WeakPtr = std::weak_ptr<ICaseContainer>;

		virtual ~ICaseContainer() = default;

		virtual void Print(IButtonGroup& buttons) = 0;
	};
}
