#pragma once
#include <string>
#include <vector>
#include <memory>

namespace Game
{
	class ICommand
	{
	public:
		virtual ~ICommand() = default;
		virtual void Run(const std::vector<std::string>& args) = 0;
	};
}
