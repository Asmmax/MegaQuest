#pragma once
#include "FormBase.hpp"

namespace QuestCore
{
	class SpecificForm : public FormBase
	{
	public:
		SpecificForm(int count, const std::string& text);
		virtual bool HasRuleFor(int count) override;
	private:
		int _count;
	};

	class TailForm : public FormBase
	{
	public:
		TailForm(int notation, int digit, const std::string& text);
		virtual bool HasRuleFor(int count) override;
	private:
		int _notation;
		int _digit;
	};
}