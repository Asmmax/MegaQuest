#pragma once
#include "TextString.hpp"

namespace QuestCore 
{
	/// @serializable @unique
	class FormBase
	{
	public:
		FormBase(const TextString& text);
		virtual ~FormBase() = default;
		virtual bool HasRuleFor(int count) { return true; }
		inline TextString GetForm() const { return _text; }
	private:
		TextString _text;
	};
}