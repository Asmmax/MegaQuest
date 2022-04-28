#include "SimpleRoom.hpp"

using namespace QuestCore;

SimpleRoom::SimpleRoom(const std::shared_ptr<IParagraph>& startParagraph, const std::vector<std::string>& hotKeys):
	_hotKeys(hotKeys),
	_currentParagraph(startParagraph)
{
}

const std::shared_ptr<IParagraph>& SimpleRoom::GetCurrentParagraph() const
{
	return _currentParagraph;
}

std::vector<std::string> SimpleRoom::GetHotKeys() const
{
	return _hotKeys;
}
