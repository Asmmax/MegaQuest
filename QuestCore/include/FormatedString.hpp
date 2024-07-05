#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class FormBase;

	class FormatedString
	{
	public:
		FormatedString(const std::vector<FormBase*>& forms = std::vector<FormBase*>());
		void ClearForms();
		void AddForm(FormBase* form);
		TextString GetContainsFor(int count) const;

	private:
		std::vector<FormBase*> _forms;
	};
}