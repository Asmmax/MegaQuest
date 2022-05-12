#pragma once
#include "Case.hpp"
#include <string>
#include <memory>
#include <vector>

namespace QuestCore
{
	class IButtonPanel;

	class ICaseContainer
	{
	public:
		using Ptr = std::shared_ptr<ICaseContainer>;

		virtual ~ICaseContainer() = default;

		virtual void Print(IButtonPanel& buttonPanel) = 0;
	};
}
