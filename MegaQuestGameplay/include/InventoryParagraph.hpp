#pragma once
#include "IParagraph.hpp"
#include "ActionMap.hpp"
#include "FormatedString.hpp"
#include <vector>

namespace QuestCore
{
	class Inventory;

	class InventoryParagraph: public IParagraph
	{
		using FormPtr = std::shared_ptr<FormBase>;
	public:
		InventoryParagraph(const FormatedString& prefix,
			const TextString& gap,
			const FormatedString& postfix,
			const std::shared_ptr<Inventory>& inventory);

		virtual TextString GetQuest() const override;
		virtual ActionMap& GetActionContainer() override;

	private:
		ActionMap _container;
		FormatedString _prefix;
		TextString _gap;
		FormatedString _postfix;
		std::shared_ptr<Inventory> _inventory;
	};
}