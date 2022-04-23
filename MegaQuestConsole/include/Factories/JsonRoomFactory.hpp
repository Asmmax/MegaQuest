#pragma once
#include "Factories/IRoomFactory.hpp"
#include "TextString.hpp"
#include <map>
#include <string>
#include "json.hpp"

namespace QuestCore
{
	class Inventory;
	class ItemInfo;
	class IParagraph;
	class FormBase;
	class IAction;
}

class JsonRoomFactory : public QuestCore::IRoomFactory
{
public:
	JsonRoomFactory(const std::string& filename, const std::shared_ptr<QuestCore::Inventory>& playerInventory);
	std::shared_ptr<QuestCore::IRoom> GetRoom() override;

private:
	void ReadItems(const nlohmann::json& itemsNode);
	void ReadForms(const nlohmann::json& formsNode, const std::shared_ptr<QuestCore::ItemInfo>& itemInfo);
	std::shared_ptr<QuestCore::FormBase> ReadForm(const nlohmann::json& formNode);
	void CreateParagraphs(const nlohmann::json& paragraphsNode);
	void ReadParagraphs(const nlohmann::json& paragraphsNode);

	std::shared_ptr<QuestCore::IParagraph> CreateParagraph(const nlohmann::json& paragraphNode);
	void InitParagraph(const std::shared_ptr<QuestCore::IParagraph>& paragraph, const nlohmann::json& paragraphNode);

	std::vector<std::shared_ptr<QuestCore::IAction>> ReadActions(const nlohmann::json& actionsNode);
	std::shared_ptr<QuestCore::IAction> ReadAction(const nlohmann::json& actionNode);

	std::map<std::shared_ptr<QuestCore::ItemInfo>, int> ReadGiftItems(const nlohmann::json& itemsNode);
	std::pair<std::shared_ptr<QuestCore::ItemInfo>, int> ReadGiftItem(const nlohmann::json& itemNode);

	template<typename T> T Read(const nlohmann::json& node, const std::string& key, const T& defValue);
	template<> QuestCore::TextString Read(const nlohmann::json& node, const std::string& key, const QuestCore::TextString& defValue);

	std::shared_ptr<QuestCore::IParagraph> GetRootParagraph();

private:
	std::string _filename;
	std::shared_ptr<QuestCore::Inventory> _playerInventory;
	std::map<std::string, std::shared_ptr<QuestCore::ItemInfo>> _items;
	std::map<std::string, std::shared_ptr<QuestCore::IParagraph>> _paragraphs;
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
