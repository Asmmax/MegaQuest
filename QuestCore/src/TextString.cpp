#include "TextString.hpp"
#include <codecvt>

using namespace QuestCore;

TextString::TextString()
{
}

TextString::TextString(const TextString& other):
	_u8(other._u8)
{
}

TextString::TextString(const std::string& u8) :
	_u8(u8)
{
}

TextString::TextString(int value):
	_u8(std::to_string(value))
{
}

TextString TextString::operator+(const TextString& other) const
{
	return TextString(_u8 + other._u8);
}

TextString& TextString::operator=(const TextString& other)
{
	_u8 = other._u8;
	return *this;
}

TextString& TextString::operator+=(const TextString& other)
{
	_u8 += other._u8;
	return *this;
}

bool TextString::IsEmpty() const
{
	return _u8.empty();
}

std::string TextString::ToUtf8() const
{
	return _u8;
}

std::wstring TextString::ToUtf16() const
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(_u8);
}

TextString TextString::FromUtf8(const std::string& text)
{
	return TextString(text);
}
