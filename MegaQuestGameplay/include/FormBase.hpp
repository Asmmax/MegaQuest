#pragma once
#include <string>

namespace QuestCore 
{
	class FormBase
	{
	public:
		FormBase(const std::string& text);
		virtual ~FormBase() = default;
		virtual bool HasRuleFor(int count) { return true; }
		inline std::string GetForm() const { return _text; }
	private:
		std::string _text;
	};
}