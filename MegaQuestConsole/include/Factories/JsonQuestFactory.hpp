#pragma once
#include "IRootFactory.hpp"
#include "Containers/ContainerBase.hpp"
#include "Containers/IFactory.hpp"

namespace QuestCore
{
	class Item;
	class IAction;
	class FormBase;
	class ICondition;
	class Value;
	struct Case;
	class TextString;
	class FormatedString;
	struct ItemRecord;
	struct ItemOrder;

	class CaseContainerStateMachine;
	class ParagraphStateMachine;
}

class JsonQuestFactory : public IRootFactory
{
public:
	JsonQuestFactory(const std::string& filename);

	virtual ParagraphPtr GetParagraph(const std::string& rootKey) override;
	virtual CaseContainerPtr GetCaseContainer(const std::string& rootKey) override;
	virtual InventoryPtr GetInventory(const std::string& inventoryKey) override;

private:
	void InitContainers();
	bool Read();

	void InitItems();
	void InitParagraphs();
	void InitCaseContainers();
	void InitInventories();
	void InitActions();

	void InitForms();
	void InitConditions();
	void InitValues();

	void InitCases();
	void InitTextStrings();
	void InitFormatedStrings();
	void InitItemOrders();
	void InitItemRecords();

private:
	bool _isRed;
	std::string _filename;
	
	//shared
	std::shared_ptr<ContainerBase<QuestCore::Item>> _items;
	std::shared_ptr<ContainerBase<QuestCore::IParagraph>> _paragraphs;
	std::shared_ptr<ContainerBase<QuestCore::ICaseContainer>> _containers;
	std::shared_ptr<ContainerBase<QuestCore::Inventory>> _inventories;
	std::shared_ptr<ContainerBase<QuestCore::IAction>> _actions;

	//unique
	std::shared_ptr<IFactory<std::shared_ptr<QuestCore::FormBase>>> _formBaseFactory;
	std::shared_ptr<IFactory<std::shared_ptr<QuestCore::ICondition>>> _conditionFactory;
	std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Value>>> _valueFactory;

	//simple
	std::shared_ptr<IFactory<QuestCore::Case>> _caseFactory;
	std::shared_ptr<IFactory<QuestCore::TextString>> _textFactory;
	std::shared_ptr<IFactory<QuestCore::FormatedString>> _formatedTextFactory;
	std::shared_ptr<IFactory<QuestCore::ItemRecord>> _itemRecordFactory;
	std::shared_ptr<IFactory<QuestCore::ItemOrder>> _itemOrderFactory;
};
