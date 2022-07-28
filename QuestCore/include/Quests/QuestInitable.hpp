#pragma once
#include <memory>

namespace QuestCore
{
	class QuestHeader;

	class QuestInitable
	{
	protected:
		using QuestHeaderPtr = std::shared_ptr<QuestHeader>;
	public:
		QuestInitable(const QuestHeaderPtr& quest);

		virtual ~QuestInitable() = default;
		virtual void Init() = 0;

	private:
		QuestHeaderPtr _quest;
	};
}
