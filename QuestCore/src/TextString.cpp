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

TextString TextString::FromUtf16(const std::wstring& text)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return TextString(converter.to_bytes(text));
}

std::vector<TextString> TextString::SplitBy(const TextString& delimiter) const
{
	std::string strDelimiter = delimiter.ToUtf8();
	std::string strFull = _u8;

	std::vector<TextString> strs;
	size_t pos = 0;
	while ((pos = strFull.find(strDelimiter)) != std::string::npos) {
		strs.push_back(TextString::FromUtf8(strFull.substr(0, pos)));
		strFull.erase(0, pos + strDelimiter.length());
	}
	strs.push_back(TextString::FromUtf8(strFull));

	return strs;
}
