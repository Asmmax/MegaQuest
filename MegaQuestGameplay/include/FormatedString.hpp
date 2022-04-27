#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class FormBase;

	class FormatedString
	{
		using FormPtr = std::shared_ptr<FormBase>;
	public:
		void ClearForms();
		void AddForm(const FormPtr& form);
		TextString GetContainsFor(int count) const;

	private:
		std::vector<FormPtr> _forms;
	};
}