#pragma once
#include "Game/Commands/VoidCommand.hpp"

namespace Game
{
	class Model;

	/// @serializable
	class ResetCommand : public VoidCommand
	{
		using ModelPtr = std::shared_ptr<Model>;
	public:
		ResetCommand(const ModelPtr& model);
		virtual void Run() override;
	private:
		ModelPtr _model;
	};
}
