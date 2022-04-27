#include "SimpleRoom.hpp"

using namespace QuestCore;

SimpleRoom::SimpleRoom(const TextString& name, const std::shared_ptr<IParagraph>& startParagraph, const std::vector<std::string>& hotKeys):
	_name(name),
	_hotKeys(hotKeys),
	_currentParagraph(startParagraph)
{
}

const TextString& SimpleRoom::GetName() const
{
	return _name;
}

const std::shared_ptr<IParagraph>& SimpleRoom::GetCurrentParagraph() const
{
	return _currentParagraph;
}

std::vector<std::string> SimpleRoom::GetHotKeys() const
{
	return _hotKeys;
}
