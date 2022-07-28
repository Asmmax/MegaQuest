#pragma once
#include "Quests/QuestHeader.hpp"

namespace QuestCore
{
	/// @serializable
	class QuestList : public QuestHeader
	{
	public:
		QuestList(const std::vector<IQuest::Ptr>& quests);
		/// @inject
		void SetCurrent(size_t currentId);

		void Up();
		void Down();

		virtual void Init() override;

	private:
		size_t _currentId;
		IQuest::Ptr _current;
		std::vector<IQuest::Ptr> _quests;
	};
}
