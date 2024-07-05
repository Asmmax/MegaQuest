bind "Game/ButtonLists/ButtonListBase.hpp";
bind "Game/ButtonLists/InventoryButtonList.hpp";
bind "Game/ButtonLists/SimpleButtonList.hpp";
bind "Game/ButtonLists/SwitchButtonList.hpp";


abstract shared Game::ButtonListBase : Game::IButtonList
{
	ButtonListBase(QuestCore::TextString error, bool show = true);
};

shared Game::InventoryButtonList : Game::ButtonListBase
{
	InventoryButtonList(QuestCore::TextString error, QuestCore::IInventoryFactory inventoryFactory, vector<int> counts, QuestCore::TextString putMessage, QuestCore::TextString throwMessage);
};

shared Game::SimpleButtonList : Game::ButtonListBase
{
	SimpleButtonList(QuestCore::TextString error, bool show = false, QuestCore::ICaseContainerFactory containerFactory);
};

shared Game::SwitchButtonList : Game::IButtonList
{
	SwitchButtonList(vector<Game::IButtonList> targets);
};
