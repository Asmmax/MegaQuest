#pragma once
#include "Quests/Quest.hpp"

namespace QuestCore
{
	/// @serializable
	class QuestTarget : public Quest
	{
	public:
		/// @inject
		void SetCurrent(const IQuest::Ptr& current);

		virtual void Init() override;

	private:
		IQuest::Ptr _current;
	};
}
