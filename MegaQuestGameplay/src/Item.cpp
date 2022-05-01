#include "Item.hpp"

using namespace QuestCore;

Item::Item(const std::string& id, const FormatedString& text, bool isNullable):
	_id(id),
	_text(text),
	_isNullable(isNullable)
{
}

TextString Item::GetContains(int count) const
{
	if (!_isNullable && count == 0) {
		return TextString();
	}

	if (!_isNullable && count == 1) {
		return _text.GetContainsFor(count);
	}

	return TextString(count) + TextString::FromUtf8(u8" ") + _text.GetContainsFor(count);
}

bool Item::operator<(const Item& other) const
{
	return _id < other._id;
}
