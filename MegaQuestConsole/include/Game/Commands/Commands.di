bind "Game/Commands/AliasCommand.hpp";
bind "Game/Commands/ChoiceCommand.hpp";
bind "Game/Commands/ForceChoiceCommand.hpp";
bind "Game/Commands/IntCommand.hpp";
bind "Game/Commands/LevelUpCommand.hpp";
bind "Game/Commands/QuitCommand.hpp";
bind "Game/Commands/ResetCommand.hpp";
bind "Game/Commands/SwitchCommand.hpp";
bind "Game/Commands/VoidCommand.hpp";

single Game::AliasCommand : Game::ICommand
{
	AliasCommand(std::string alias, Game::CommandManager commandManager);
};


abstract single Game::IntCommand : Game::ICommand
{
	IntCommand(QuestCore::TextString error);
};

single Game::ChoiceCommand : Game::IntCommand
{
	ChoiceCommand(Game::IButtonList buttonGroup, QuestCore::TextString error);
};


abstract single Game::VoidCommand : Game::ICommand
{
};

single Game::ForceChoiceCommand : Game::VoidCommand
{
	ForceChoiceCommand(Game::IButtonList buttonGroup, int choice = 0);
};

single Game::LevelUpCommand : Game::VoidCommand
{
	LevelUpCommand(Game::Model model, QuestCore::QuestList questList);
};

single Game::QuitCommand : Game::VoidCommand
{
};

single Game::ResetCommand : Game::VoidCommand
{
	ResetCommand(Game::Model model);
};

single Game::SwitchCommand : Game::VoidCommand
{
	SwitchCommand(Game::SwitchDialog switchDialog);
};
