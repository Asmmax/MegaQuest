#include "Game/Dialogs/DialogBase.hpp"
#include "Game/IOutput.hpp"
#include "Game/IButtonList.hpp"

using namespace Game;

DialogBase::DialogBase(const OutputPtr& output,
	const QuestCore::TextString& intro) :

	_output(output),
	_intro(intro)
{
}

void DialogBase::Init()
{
	_output->WriteLn(_intro);
}

void DialogBase::Update()
{
	for (auto& buttonGroup : _buttonGroups) {
		buttonGroup->Update();
	}
}

void DialogBase::Draw()
{
	for (auto& buttonGroup : _buttonGroups) {
		buttonGroup->Draw();
	}
}

void DialogBase::AddButtonList(const IButtonList::Ptr& buttonList)
{
	if (buttonList->IsUpdateAfterDone()) {
		buttonList->AddDoneCallback([this]() {
			Update();
			Draw();
			});
	}
	_buttonGroups.push_back(buttonList);
}

IOutput::Ptr DialogBase::GetOutput()
{
	return _output;
}
