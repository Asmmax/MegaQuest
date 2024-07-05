bind "Value.hpp";

abstract single QuestCore::Value
{
};

single QuestCore::SimpleValue : QuestCore::Value
{
	SimpleValue(int value = 0);
};

single QuestCore::InventoryValue : QuestCore::Value
{
	InventoryValue(QuestCore::Item item, QuestCore::Inventory inventory);
};
