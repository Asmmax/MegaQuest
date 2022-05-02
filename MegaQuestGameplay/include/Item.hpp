#pragma once
#include "FormatedString.hpp"

namespace QuestCore
{
	class Item
	{
	public:
		Item(const FormatedString& text, bool isNullable = false);
		TextString GetContains(int count) const;
		inline bool IsNullable() const { return _isNullable; }

	private:
		FormatedString _text;
		bool _isNullable;
	};
}
