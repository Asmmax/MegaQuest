#include "Game/Model.hpp"
#include "Game/DialogFactory.hpp"
#include "Game/Dialog.hpp"
#include "QuestBase.hpp"
#include "IQuestFactory.hpp"

using namespace Game;

Model::Model(const OutputPtr& output, const QuestFactoryPtr& questFactory):
	_output(output),
	_questFactory(questFactory)
{
	_dialogFactory = std::make_shared<DialogFactory>(output);
	_quest = _questFactory->GetQuest(_dialogFactory, _dialogFactory);
	_currentDialog = _dialogFactory->GetDialog("root");
	_currentDialog->SetQuest(_quest);
}

void Model::OpenInventory()
{
	_currentDialog->OpenInventory();
	_currentDialog->Update();
}

bool Model::Handle(int answer)
{
	if (_currentDialog->Answer(answer)) {
		_currentDialog->Update();
		return true;
	}

	return false;
}

void Model::Init()
{
	_quest->Update();
	_currentDialog->Update();
}
