#pragma once
#include "ICaseContainer.hpp"
#include "Quests/QuestInitable.hpp"

namespace QuestCore
{
	/// @serializable
	class CaseContainerStateMachine : public ICaseContainer, public QuestInitable
	{
	public:
		CaseContainerStateMachine(const QuestHeaderPtr& quest);
		/// @inject
		void InitState(const ICaseContainer::WeakPtr& state);
		void SetState(const ICaseContainer::WeakPtr& state);

		virtual void Print(IButtonGroup& buttons) override;
		virtual void Init() override;

	private:
		ICaseContainer::WeakPtr _initState;
		ICaseContainer::WeakPtr _state;
	};
}
