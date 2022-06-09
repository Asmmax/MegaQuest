#pragma once
#include "Game/ICommand.hpp"
#include "TextString.hpp"

namespace Game
{
	class IntCommand :public ICommand
	{
	public:
		IntCommand(const QuestCore::TextString& error);
		virtual void Run(const std::vector<std::string>& args) override final;
		virtual void Run(int arg) = 0;

	protected:
		void Error();

	private:
		QuestCore::TextString _error;
	};
}