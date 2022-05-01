#pragma once
#include "IRoomFactory.hpp"
#include "TextString.hpp"
#include "FormatedString.hpp"
#include <map>
#include <vector>
#include <string>
#include "json.hpp"

namespace QuestCore
{
	class Item;
	class IParagraph;
	class FormBase;
	class IAction;
	class Inventory;
	class CaseContainer;
	class ICondition;
	class Value;
	enum class Operation;
}

class JsonRoomFactory : public QuestCore::IRoomFactory
{
public:
	JsonRoomFactory(const std::string& filename);
	std::shared_ptr<QuestCore::IRoom> GetRoom() override;

private:
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

	void ReadCases(const nlohmann::json& casesNode, QuestCore::CaseContainer& cases);
	std::vector<std::shared_ptr<QuestCore::IAction>> ReadActions(const nlohmann::json& actionsNode);
	std::shared_ptr<QuestCore::IAction> ReadAction(const nlohmann::json& actionNode);

	std::vector<std::shared_ptr<QuestCore::ICondition>> ReadConditions(const nlohmann::json& conditionsNode);
	std::shared_ptr<QuestCore::ICondition> ReadCondition(const nlohmann::json& conditionNode);
	std::shared_ptr<QuestCore::Value> ReadValue(const nlohmann::json& valueNode);
	QuestCore::Operation ReadOperation(const nlohmann::json& opNode);

	std::vector<std::pair<std::shared_ptr<QuestCore::Item>, int>> ReadGiftItems(const nlohmann::json& itemsNode);
	std::pair<std::shared_ptr<QuestCore::Item>, int> ReadGiftItem(const nlohmann::json& itemNode);

	template<typename T> T Read(const nlohmann::json& node, const std::string& key, const T& defValue);
	template<> QuestCore::TextString Read(const nlohmann::json& node, const std::string& key, const QuestCore::TextString& defValue);

	std::shared_ptr<QuestCore::IParagraph> GetRootParagraph();

private:
	std::string _filename;
	std::vector<std::string> _hotKeys;
	std::map<std::string, std::shared_ptr<QuestCore::IParagraph>> _inputs;
	std::map<std::string, std::shared_ptr<QuestCore::Item>> _items;
	std::map<std::string, std::shared_ptr<QuestCore::IParagraph>> _paragraphs;
	std::map<std::string, std::shared_ptr<QuestCore::Inventory>> _inventories;
};


template<typename T>
T JsonRoomFactory::Read(const nlohmann::json& node, const std::string& key, const T& defValue)
{
	auto foundIt = node.find(key);
	if (foundIt == node.end()) {
		return defValue;
	}

	return *foundIt;
}

template<>
QuestCore::TextString JsonRoomFactory::Read(const nlohmann::json& node, const std::string& key, const QuestCore::TextString& defValue)
{
	std::string rawDefValue = defValue.ToUtf8();
	return QuestCore::TextString::FromUtf8(Read(node,key, rawDefValue));
}
