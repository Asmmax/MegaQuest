#pragma once
#include <memory>

namespace QuestCore
{
	class ICaseContainer;

	class ICaseContainerFactory
	{
	public:
		virtual ~ICaseContainerFactory() = default;
		virtual ICaseContainer* GetCaseContainer() const = 0;
	};
}
