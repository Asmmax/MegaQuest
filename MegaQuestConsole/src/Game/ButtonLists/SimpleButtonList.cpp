#include "Game/ButtonLists/SimpleButtonList.hpp"
#include "Game/IOutput.hpp"
#include "ICaseContainer.hpp"

using namespace Game;

SimpleButtonList::SimpleButtonList(const DialogWeakPtr& parent,
	const OutputPtr& output,
	const QuestCore::TextString& error,
	const CaseContainerPtr& container,
	bool show):

	ButtonListBase(parent, output, error),
	_container(container),
	_show(show)
{
}

void SimpleButtonList::Update()
{
	Clear();
	_container->Print(*this);

	if (_show) {
		Print();
	}
}
