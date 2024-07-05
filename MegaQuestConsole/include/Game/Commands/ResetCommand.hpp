#pragma once
#include "Game/Commands/VoidCommand.hpp"

namespace Game
{
	class Model;

	class ResetCommand : public VoidCommand
	{
	public:
		ResetCommand(Model* model);
		virtual void Run() override;
	private:
		Model* _model;
	};
}
