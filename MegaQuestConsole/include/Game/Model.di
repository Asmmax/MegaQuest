bind "Game/Model.hpp";

shared Game::Model
{
	Model(Game::IDialog rootDialog, QuestCore::IQuest quest);
	SetOutput(Game::IOutput output);
} models;
