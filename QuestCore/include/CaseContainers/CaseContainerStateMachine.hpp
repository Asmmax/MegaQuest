#pragma once
#include "ICaseContainer.hpp"
#include "Quests/QuestInitable.hpp"

namespace QuestCore
{
	class CaseContainerStateMachine : public ICaseContainer, public QuestInitable
	{
	public:
		CaseContainerStateMachine(Quest* quest);
		void InitState(ICaseContainer* state);
		void SetState(ICaseContainer* state);

		virtual void Print(IButtonGroup& buttons) override;
		virtual void Init() override;

	private:
		ICaseContainer* _initState;
		ICaseContainer* _state;
	};
}
