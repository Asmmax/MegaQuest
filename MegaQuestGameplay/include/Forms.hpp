#pragma once
#include "FormBase.hpp"
#include <vector>

namespace QuestCore
{
	class SpecificForm : public FormBase
	{
	public:
		SpecificForm(const std::vector<int>& counts, const TextString& text);
		virtual bool HasRuleFor(int count) override;
	private:
		std::vector<int> _counts;
	};

	class TailForm : public FormBase
	{
	public:
		TailForm(int notation, const std::vector<int>& digits, const TextString& text);
		virtual bool HasRuleFor(int count) override;
	private:
		int _notation;
		std::vector<int> _digits;
	};
}