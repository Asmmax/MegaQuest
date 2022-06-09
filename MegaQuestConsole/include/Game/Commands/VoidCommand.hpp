#pragma once
#include "Game/ICommand.hpp"

namespace Game
{
	class VoidCommand :public ICommand
	{
	public:
		virtual void Run(const std::vector<std::string>& args) override final;
		virtual void Run() = 0;
	};
}