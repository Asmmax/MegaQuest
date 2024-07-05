bind "IO/InputHandler.hpp";

shared IO::InputHandler
{
	InputHandler(Game::IInput input, Game::IOutput output, Game::CommandManager commandManager, Game::Model model);
} inputHandler;
