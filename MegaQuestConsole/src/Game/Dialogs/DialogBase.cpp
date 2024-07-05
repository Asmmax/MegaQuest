#include "Game/Dialogs/DialogBase.hpp"
#include "Game/IOutput.hpp"
#include "Game/IButtonList.hpp"
#include "Game/Model.hpp"

using namespace Game;

DialogBase::DialogBase(const QuestCore::TextString& intro, const std::vector<IButtonList*> buttonGroups) :

	_intro(intro)
{
	for (auto& buttonGroup : buttonGroups) {
		AddButtonList(buttonGroup);
	}
}

void DialogBase::SetModel(Model* model)
{
	_model = model;
}

void DialogBase::Init(IOutput& output)
{
	output.WriteLn(_intro);
}

void DialogBase::Update()
{
	for (auto& buttonGroup : _buttonGroups) {
		buttonGroup->Update();
	}
}

void DialogBase::Draw(IOutput& output)
{
	for (auto& buttonGroup : _buttonGroups) {
		buttonGroup->Draw(output);
	}
}

void DialogBase::AddButtonList(IButtonList* buttonList)
{
	if (buttonList->IsUpdateAfterDone()) {
		buttonList->AddDoneCallback([this]() {
			if (_model) {
				_model->Update();
			}
			});
	}
	_buttonGroups.push_back(buttonList);
}

Model* DialogBase::GetModel()
{
	return _model;
}
