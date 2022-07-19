#pragma once
#include "json.hpp"
#include <memory>

namespace Game
{
	class CommandManager;
}

class CommandsFactory
{
	using CommandManagerPtr = std::shared_ptr<Game::CommandManager>;

public:
	CommandsFactory(const std::string& filename);
	CommandManagerPtr GetCommandManager();

	bool Read();

private:
	bool _isRed;
	std::string _filename;
};
