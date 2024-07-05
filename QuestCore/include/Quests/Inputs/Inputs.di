bind "Quests/Inputs/CaseContainerInput.hpp";
bind "Quests/Inputs/InventoryInput.hpp";
bind "Quests/Inputs/ParagraphInput.hpp";

shared QuestCore::CaseContainerInput
{
	CaseContainerInput(QuestCore::ICaseContainer container, QuestCore::CaseContainerSlot slot, QuestCore::Quest quest);
} inputs;

shared QuestCore::InventoryInput
{
	InventoryInput(QuestCore::Inventory inventory, QuestCore::InventorySlot slot, QuestCore::Quest quest);
} inputs;

shared QuestCore::ParagraphInput
{
	ParagraphInput(QuestCore::IParagraph paragraph, QuestCore::ParagraphSlot slot, QuestCore::Quest quest);
} inputs;
