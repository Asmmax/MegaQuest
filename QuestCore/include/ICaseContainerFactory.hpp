#pragma once
#include <memory>

namespace QuestCore
{
	class ICaseContainer;

	/// @serializable @abstract @shared
	class ICaseContainerFactory
	{
	protected:
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;
	public:
		virtual ~ICaseContainerFactory() = default;
		virtual CaseContainerPtr GetCaseContainer() const = 0;
	};
}
