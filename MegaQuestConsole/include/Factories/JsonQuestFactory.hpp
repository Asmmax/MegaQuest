#pragma once
#include "IRootFactory.hpp"
#include "TextString.hpp"
#include "FormatedString.hpp"
#include "json.hpp"

namespace QuestCore
{
	class Item;
	class FormBase;
	class IAction;
	class ICondition;
	class Value;
	struct Case;
	enum class Operation;
}

class ITextViewFactory;
class IButtonPanelFactory;

class JsonQuestFactory : public IRootFactory
{
public:
	JsonQuestFactory(const std::string& filename);

	virtual ParagraphPtr GetRootParagraph(const std::string& rootKey) override;
	virtual CaseContainerPtr GetRootCaseContainer(const std::string& rootKey) override;
	virtual InventoryPtr GetInventory(const std::string& inventoryKey) override;

private:
	bool Read();
	void ReadHotKeys(const nlohmann::json& keysNode);
	void ReadInputs(const nlohmann::json& inputsNode);
	void ReadItems(const nlohmann::json& itemsNode);
	void ReadForms(const nlohmann::json& formStrNode, QuestCore::FormatedString& formString);
	std::shared_ptr<QuestCore::FormBase> ReadForm(const nlohmann::json& formNode);
	void ReadInventory(const nlohmann::json& inventoriesNode);

	void CreateParagraphs(const nlohmann::json& paragraphsNode);
	void ReadParagraphs(const nlohmann::json& paragraphsNode);
	std::shared_ptr<QuestCore::IParagraph> CreateParagraph(const nlohmann::json& paragraphNode);
	void InitParagraph(const std::shared_ptr<QuestCore::IParagraph>& paragraph, const nlohmann::json& paragraphNode);

	void CreateContainers(const nlohmann::json& containersNode);
	void ReadContainers(const nlohmann::json& containersNode);
	std::shared_ptr<QuestCore::ICaseContainer> CreateContainer(const nlohmann::json& containerNode);
	void InitContainer(const std::shared_ptr<QuestCore::ICaseContainer>& container, const nlohmann::json& containerNode);

	QuestCore::Case ReadCase(const nlohmann::json& caseNode);
	std::vector<std::shared_ptr<QuestCore::IAction>> ReadActions(const nlohmann::json& actionsNode);
	std::shared_ptr<QuestCore::IAction> ReadAction(const nlohmann::json& actionNode);

	std::vector<std::shared_ptr<QuestCore::ICondition>> ReadConditions(const nlohmann::json& conditionsNode);
	std::shared_ptr<QuestCore::ICondition> ReadCondition(const nlohmann::json& conditionNode);
	std::shared_ptr<QuestCore::Value> ReadValue(const nlohmann::json& valueNode);
	QuestCore::Operation ReadOperation(const nlohmann::json& opNode);

	std::vector<std::pair<std::shared_ptr<QuestCore::Item>, int>> ReadGiftItems(const nlohmann::json& itemsNode);
	std::pair<std::shared_ptr<QuestCore::Item>, int> ReadGiftItem(const nlohmann::json& itemNode);

	std::vector<std::pair<std::shared_ptr<QuestCore::Item>, int>> ReadItemOrders(const nlohmann::json& itemsNode);
	std::pair<std::shared_ptr<QuestCore::Item>, int> ReadItemOrder(const nlohmann::json& itemNode);

	template<typename T> T Read(const nlohmann::json& node, const std::string& key, const T& defValue);
	template<> QuestCore::TextString Read(const nlohmann::json& node, const std::string& key, const QuestCore::TextString& defValue);

private:
	bool _isRed;
	std::string _filename;
	std::vector<std::string> _hotKeys;
	std::map<std::string, ParagraphPtr> _rootParagraphs;
	std::map<std::string, CaseContainerPtr> _rootContainers;
	std::map<std::string, std::shared_ptr<QuestCore::Item>> _items;
	std::map<std::string, std::shared_ptr<QuestCore::IParagraph>> _paragraphs;
	std::map<std::string, std::shared_ptr<QuestCore::ICaseContainer>> _containers;
	std::map<std::string, std::shared_ptr<QuestCore::Inventory>> _inventories;
};


template<typename T>
T JsonQuestFactory::Read(const nlohmann::json& node, const std::string& key, const T& defValue)
{
	auto foundIt = node.find(key);
	if (foundIt == node.end()) {
		return defValue;
	}

	return *foundIt;
}

template<>
QuestCore::TextString JsonQuestFactory::Read(const nlohmann::json& node, const std::string& key, const QuestCore::TextString& defValue)
{
	std::string rawDefValue = defValue.ToUtf8();
	return QuestCore::TextString::FromUtf8(Read(node,key, rawDefValue));
}
