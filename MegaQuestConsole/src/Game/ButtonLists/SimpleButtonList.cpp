#include "Game/ButtonLists/SimpleButtonList.hpp"
#include "Game/IOutput.hpp"
#include "ICaseContainer.hpp"

using namespace Game;

SimpleButtonList::SimpleButtonList(const OutputPtr& output,
	const QuestCore::TextString& error,
	bool show,
	const CaseContainerPtr& container):

	ButtonListBase(output, error, show),
	_container(container)
{
}

void SimpleButtonList::Update()
{
	ButtonListBase::Update();
	Clear();
	_container->Print(*this);
}

void SimpleButtonList::AddButton(const QuestCore::TextString& text, const QuestCore::IButtonGroup::Callback& callback)
{
	ButtonListBase::AddButton(Button{ text, callback });
}
