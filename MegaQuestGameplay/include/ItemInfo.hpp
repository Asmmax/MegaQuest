#pragma once
#include <string>
#include <memory>
#include <vector>

namespace QuestCore
{
	class FormBase;

	class ItemInfo
	{
		using FormPtr = std::shared_ptr<FormBase>;
	public:
		ItemInfo(bool isNullable = false);

		void ClearForms();
		void AddForm(const FormPtr& form);
		std::string GetContainsFor(int count);

		inline bool IsNullable() const { return _isNullable; }

	private:
		std::vector<FormPtr> _forms;
		bool _isNullable;
	};
}