#pragma once
#include "Game/Commands/VoidCommand.hpp"

namespace QuestCore
{
	class QuestList;
}

namespace Game
{
	class Model;

	class LevelUpCommand : public VoidCommand
	{
	public:
		LevelUpCommand(Model* model, QuestCore::QuestList* questList);
		virtual void Run() override;
	private:
		Model* _model;
		QuestCore::QuestList* _questList;
	};
}
