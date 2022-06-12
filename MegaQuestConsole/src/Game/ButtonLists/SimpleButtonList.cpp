#include "Game/ButtonLists/SimpleButtonList.hpp"
#include "Game/IOutput.hpp"
#include "ICaseContainer.hpp"

using namespace Game;

SimpleButtonList::SimpleButtonList(const OutputPtr& output,
	const QuestCore::TextString& error,
	const CaseContainerPtr& container,
	bool show):

	ButtonListBase(output, error),
	_container(container),
	_show(show)
{
}

void SimpleButtonList::Update()
{
	Clear();
	_container->Print(*this);

	ButtonListBase::Update();

	if (_show) {
		Print();
	}
}

void SimpleButtonList::AddButton(const QuestCore::TextString& text, const QuestCore::IButtonGroup::Callback& callback)
{
	ButtonListBase::AddButton(Button{ text, callback });
}
