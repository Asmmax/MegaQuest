#pragma once
#include "IRootFactory.hpp"

class JsonQuestFactory : public IRootFactory
{
public:
	JsonQuestFactory(const std::string& filename);

	virtual ParagraphPtr GetParagraph(const std::string& rootKey) override;
	virtual CaseContainerPtr GetCaseContainer(const std::string& rootKey) override;
	virtual InventoryPtr GetInventory(const std::string& inventoryKey) override;

	bool Read();

private:
	bool _isRed;
	std::string _filename;
};
