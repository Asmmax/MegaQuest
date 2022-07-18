#include "Game/Dialogs/DialogBase.hpp"
#include "Game/IOutput.hpp"
#include "Game/IButtonList.hpp"
#include "Game/Model.hpp"

using namespace Game;

DialogBase::DialogBase(const QuestCore::TextString& intro, const std::vector<ButtonListPtr> buttonGroups) :

	_intro(intro)
{
	for (auto& buttonGroup : buttonGroups) {
		AddButtonList(buttonGroup);
	}
}

void DialogBase::SetModel(const ModelPtr& model)
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

void DialogBase::AddButtonList(const IButtonList::Ptr& buttonList)
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

const Model::Ptr& DialogBase::GetModel()
{
	return _model;
}
