#pragma once
#include "Quests/QuestHeader.hpp"
#include <vector>

namespace QuestCore
{
	/// @serializable
	class QuestTarget : public QuestHeader
	{
	public:
		QuestTarget(const std::vector<SlotPtr>& slots);
		/// @inject
		void SetCurrent(const IQuest::Ptr& current);

		virtual void Init() override;

	private:
		IQuest::Ptr _current;
	};
}
