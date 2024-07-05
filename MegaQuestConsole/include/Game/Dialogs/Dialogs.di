bind "Game/Dialogs/DialogBase.hpp";
bind "Game/Dialogs/InventoryDialog.hpp";
bind "Game/Dialogs/SimpleDialog.hpp";
bind "Game/Dialogs/SwitchDialog.hpp";

abstract shared Game::DialogBase : Game::IDialog
{
	DialogBase(QuestCore::TextString intro, vector<Game::IButtonList> buttonGroups);
	SetModel(Game::Model model);
};

shared Game::InventoryDialog : Game::DialogBase
{
	InventoryDialog(QuestCore::TextString intro, QuestCore::IInventoryFactory inventoryFactory, vector<Game::IButtonList> buttonGroups);
};

shared Game::SimpleDialog : Game::DialogBase
{
	SimpleDialog(QuestCore::TextString intro, QuestCore::IParagraphFactory paragraphFactory, vector<Game::IButtonList> buttonGroups);
};

shared Game::SwitchDialog : Game::DialogBase
{
	SwitchDialog(QuestCore::TextString intro, vector<Game::IButtonList> buttonGroups, vector<Game::IDialog> dialogs);
};
