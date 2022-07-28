#pragma once
#include "Game/Commands/VoidCommand.hpp"

namespace QuestCore
{
	class QuestList;
}

namespace Game
{
	class Model;

	/// @serializable
	class LevelUpCommand : public VoidCommand
	{
		using ModelPtr = std::shared_ptr<Model>;
		using QuestListPtr = std::shared_ptr<QuestCore::QuestList>;
	public:
		LevelUpCommand(const ModelPtr& model, const QuestListPtr& questList);
		virtual void Run() override;
	private:
		ModelPtr _model;
		QuestListPtr _questList;
	};
}
