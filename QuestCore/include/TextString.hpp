#pragma once
#include <string>

namespace QuestCore 
{
	class TextString
	{
	public:
		TextString();
		TextString(int value);
		TextString(const TextString& other);
		TextString operator+(const TextString& other) const;
		TextString& operator=(const TextString& other);
		TextString& operator+=(const TextString& other);

		bool IsEmpty() const;
		std::string ToUtf8() const;
		std::wstring ToUtf16() const;

		static TextString FromUtf8(const std::string& text);

	private:
		TextString(const std::string& u8);

	private:
		std::string _u8;
	};
}
