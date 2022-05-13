#pragma once
#include "IModel.hpp"

namespace QuestCore
{
	class QuestBase;
	class IQuestFactory;
}

namespace Game
{
	class ButtonList;
	class Dialog;
	class DialogFactory;
	class IOutput;

	class Model : public IModel
	{
		using OutputPtr = std::shared_ptr<IOutput>;
		using QuestFactoryPtr = std::shared_ptr<QuestCore::IQuestFactory>;
		using DialogFactoryPtr = std::shared_ptr<DialogFactory>;
		using DialogPtr = std::shared_ptr<Dialog>;
		using QuestPtr = std::shared_ptr<QuestCore::QuestBase>;

	public:
		Model(const OutputPtr& output, const QuestFactoryPtr& questFactory);
		virtual void OpenInventory() override;
		virtual bool Handle(int answer) override;
		virtual void Init() override;

	private:
		OutputPtr _output;
		QuestFactoryPtr _questFactory;
		DialogFactoryPtr _dialogFactory;
		DialogPtr _currentDialog;
		QuestPtr _quest;
	};
}
