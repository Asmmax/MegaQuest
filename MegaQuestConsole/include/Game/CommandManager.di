bind "Game/CommandManager.hpp";

value Game::CommandRecord
{
	std::string name;
	Game::ICommand command;
};

shared Game::CommandManager
{
	CommandManager(QuestCore::TextString error);
	RegisterCommands(vector<Game::CommandRecord> commands);
} commandManagers;
