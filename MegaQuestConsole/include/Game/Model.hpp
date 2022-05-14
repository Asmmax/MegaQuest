#pragma once
#include <memory>
#include <vector>

namespace QuestCore
{
	class QuestBase;
}

namespace Game
{
	class ButtonList;
	class Dialog;

	class Model
	{
		using DialogPtr = std::shared_ptr<Dialog>;
		using QuestPtr = std::shared_ptr<QuestCore::QuestBase>;

	public:
		using Ptr = std::shared_ptr<Model>;

		Model(const std::vector<DialogPtr>& dialogs, const QuestPtr& quest);
		void OpenInventory();
		bool Handle(int answer);
		void Init();

	private:
		std::vector<DialogPtr> _dialogs;
		DialogPtr _currentDialog;
		QuestPtr _quest;
	};
}
