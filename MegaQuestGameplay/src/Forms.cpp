#include "Forms.hpp"

using namespace QuestCore;

SpecificForm::SpecificForm(int count, const std::string& text):
	FormBase(text),
	_count(count)
{
}

bool SpecificForm::HasRuleFor(int count) 
{
	return _count == count;
}




TailForm::TailForm(int notation, int digit, const std::string& text):
	FormBase(text),
	_notation(notation),
	_digit(digit)
{
}

bool TailForm::HasRuleFor(int count)
{
	return count % _notation == _digit;
}