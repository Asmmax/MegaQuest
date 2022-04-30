#include "SimpleRoom.hpp"

using namespace QuestCore;

SimpleRoom::SimpleRoom(const InputList& inputs, const std::vector<std::string>& hotKeys):
	_hotKeys(hotKeys),
	_paragraphs(inputs)
{
}

const std::shared_ptr<IParagraph>& SimpleRoom::GetParagraph(const std::string& key) const
{
	return _paragraphs[key];
}

std::vector<std::string> SimpleRoom::GetHotKeys() const
{
	return _hotKeys;
}
