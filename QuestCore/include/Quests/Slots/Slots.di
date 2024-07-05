bind "Quests/Slots/CaseContainerSlot.hpp";
bind "Quests/Slots/InventorySlot.hpp";
bind "Quests/Slots/ParagraphSlot.hpp";

shared QuestCore::CaseContainerSlot : QuestCore::ICaseContainerFactory
{
	CaseContainerSlot(QuestCore::Quest quest);
} slots;

shared QuestCore::InventorySlot : QuestCore::IInventoryFactory
{
	InventorySlot(QuestCore::Quest quest);
} slots;

shared QuestCore::ParagraphSlot : QuestCore::IParagraphFactory
{
	ParagraphSlot(QuestCore::Quest quest);
} slots;
