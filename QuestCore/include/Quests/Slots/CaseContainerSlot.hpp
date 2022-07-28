#pragma once
#include "Quests/QuestInitable.hpp"
#include <memory>

namespace QuestCore
{
	class CaseContainerInput;
	class ICaseContainer;

	/// @serializable @shared slots
	class CaseContainerSlot : public QuestInitable
	{
		using CaseContainerPtr = std::shared_ptr<ICaseContainer>;
	public:
		CaseContainerSlot(const QuestHeaderPtr& quest);
		virtual void Init() override;
		void SetInput(CaseContainerInput* input);
		CaseContainerPtr GetCaseContainer() const;

	private:
		CaseContainerInput* _input;
	};
}
