#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class FormBase;

	/// @serializable
	class FormatedString
	{
		using FormPtr = std::shared_ptr<FormBase>;
	public:
		FormatedString(const std::vector<std::shared_ptr<FormBase>>& forms = std::vector<std::shared_ptr<FormBase>>());
		void ClearForms();
		void AddForm(const FormPtr& form);
		TextString GetContainsFor(int count) const;

	private:
		std::vector<FormPtr> _forms;
	};
}