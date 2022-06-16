#pragma once
#include <string>
#include <vector>

namespace QuestCore 
{
	/// @serializable
	class TextString
	{
	public:
		TextString(int value);
		TextString(const TextString& other);
		/// @inject
		TextString(const std::string& u8 = std::string());
		TextString operator+(const TextString& other) const;
		TextString& operator=(const TextString& other);
		TextString& operator+=(const TextString& other);

		bool IsEmpty() const;
		std::string ToUtf8() const;
		std::wstring ToUtf16() const;

		static TextString FromUtf8(const std::string& text);
		static TextString FromUtf16(const std::wstring& text);

		std::vector<TextString> SplitBy(const TextString& delimiter) const;

	private:
		std::string _u8;
	};
}
