#include "ItemInfo.hpp"
#include "FormBase.hpp"

using namespace QuestCore;

ItemInfo::ItemInfo(bool isNullable):
	_isNullable(isNullable)
{
}

void ItemInfo::ClearForms()
{
	_forms.clear();
}

void ItemInfo::AddForm(const FormPtr& form)
{
	_forms.emplace_back(form);
}

TextString ItemInfo::GetContainsFor(int count)
{
	for (auto& form : _forms) {
		if (form->HasRuleFor(count)) {
			return form->GetForm();
		}
	}
	return TextString();
}