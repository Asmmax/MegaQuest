#include "SimpleRoom.hpp"

using namespace QuestCore;

SimpleRoom::SimpleRoom(const std::string& name, const std::shared_ptr<IParagraph>& startParagraph):
	_name(name),
	_currentParagraph(startParagraph)
{
}

const std::string& SimpleRoom::GetName() const
{
	return _name;
}

const std::shared_ptr<IParagraph>& SimpleRoom::GetCurrentParagraph() const
{
	return _currentParagraph;
}
