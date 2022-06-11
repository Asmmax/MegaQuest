#pragma once
#include "Case.hpp"
#include <string>
#include <memory>
#include <vector>

namespace QuestCore
{
	class IButtonGroup;

	class ICaseContainer
	{
	public:
		using Ptr = std::shared_ptr<ICaseContainer>;

		virtual ~ICaseContainer() = default;

		virtual void Print(IButtonGroup& buttons) = 0;
	};
}
