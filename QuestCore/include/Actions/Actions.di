bind "Actions/CaseContainerSwitching.hpp";
bind "Actions/Clearing.hpp";
bind "Actions/Copying.hpp";
bind "Actions/ParagraphSwitching.hpp";
bind "Actions/Transfer.hpp";

shared QuestCore::CaseContainerSwitching : QuestCore::IAction
{
	SetStateMachine(QuestCore::CaseContainerStateMachine stateMachine);
	SetNextContainer(QuestCore::ICaseContainer nextContainer);
};

shared QuestCore::Clearing : QuestCore::IAction
{
	Clearing(QuestCore::Inventory inventory);
};

shared QuestCore::Copying : QuestCore::IAction
{
	Copying(QuestCore::Inventory source, QuestCore::Inventory target);
};

shared QuestCore::ParagraphSwitching : QuestCore::IAction
{
	SetStateMachine(QuestCore::ParagraphStateMachine stateMachine);
	SetNextParagraph(QuestCore::IParagraph nextParagraph);
};

shared QuestCore::Transfer : QuestCore::IAction
{
	Transfer(QuestCore::Inventory source, QuestCore::Inventory target, vector<QuestCore::ItemRecord> items);
};
