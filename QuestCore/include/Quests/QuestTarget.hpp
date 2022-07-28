#pragma once
#include "Quests/QuestHeader.hpp"

namespace QuestCore
{
	/// @serializable
	class QuestTarget : public QuestHeader
	{
	public:
		/// @inject
		void SetCurrent(const IQuest::Ptr& current);

		virtual void Init() override;

	private:
		IQuest::Ptr _current;
	};
}
