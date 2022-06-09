#pragma once
#include "Game/ICommand.hpp"

namespace Game
{
	class AliasCommand :public ICommand
	{
	public:
		AliasCommand(const std::string& orig);
		virtual void Run(const std::vector<std::string>& args) override;
	private:
		std::string _orig;
	};
}