#include "Forms.hpp"

using namespace QuestCore;

SpecificForm::SpecificForm(const std::vector<int>& counts, const TextString& text):
	FormBase(text),
	_counts(counts)
{
}

bool SpecificForm::HasRuleFor(int count) 
{
	for (auto _count : _counts) {
		if (_count == count) {
			return true;
		}
	}
	return false;
}




TailForm::TailForm(int notation, const std::vector<int>& digits, const TextString& text):
	FormBase(text),
	_notation(notation),
	_digits(digits)
{
}

bool TailForm::HasRuleFor(int count)
{
	for (auto digit : _digits) {
		if (count % _notation == digit) {
			return true;
		}
	}
	return false;
}