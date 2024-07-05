bind "Inventory.hpp";

value QuestCore::ItemRecord
{
		QuestCore::Item item;
		int count;
};

shared QuestCore::Inventory
{
	Inventory(QuestCore::Quest quest, vector<QuestCore::ItemRecord> items);
} inventories;
