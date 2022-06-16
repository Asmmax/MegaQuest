#include "FormatedString.hpp"
#include "FormBase.hpp"

using namespace QuestCore;

FormatedString::FormatedString(const std::vector<FormPtr>& forms):
	_forms(forms)
{
}

void FormatedString::ClearForms()
{
	_forms.clear();
}

void FormatedString::AddForm(const FormPtr& form)
{
	_forms.emplace_back(form);
}

TextString FormatedString::GetContainsFor(int count) const
{
	for (auto& form : _forms) {
		if (form->HasRuleFor(count)) {
			return form->GetForm();
		}
	}
	return TextString();
}