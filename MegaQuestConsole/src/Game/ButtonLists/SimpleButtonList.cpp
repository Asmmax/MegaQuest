#include "Game/ButtonLists/SimpleButtonList.hpp"
#include "Game/IOutput.hpp"
#include "ICaseContainer.hpp"
#include "Quests/Slots/CaseContainerSlot.hpp"

using namespace Game;

SimpleButtonList::SimpleButtonList(const QuestCore::TextString& error,
	bool show,
	const ContainerFactoryPtr& containerFactory,
	const std::string& containerName):

	ButtonListBase(error, show),
	_containerFactory(containerFactory)
{
}

void SimpleButtonList::UpdateImpl()
{
	Clear();
	if (auto container = _containerFactory->GetCaseContainer()) {
		container->Print(*this);
	}
}

void SimpleButtonList::AddButton(const QuestCore::TextString& text, const QuestCore::IButtonGroup::Callback& callback)
{
	ButtonListBase::AddButton(Button{ text, callback });
}
