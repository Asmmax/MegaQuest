#pragma once
#include "TextString.hpp"
#include <memory>

namespace Game 
{
	class IInput;
	class IOutput;
}

namespace IO
{
	class InputHandler
	{
		using InputPtr = std::shared_ptr<Game::IInput>;
		using OutputPtr = std::shared_ptr<Game::IOutput>;

	public:
		using Ptr = std::shared_ptr<InputHandler>;

		InputHandler(const InputPtr& input, const OutputPtr& output);
		void Handle();

	private:
		std::vector<std::string> Parse(const QuestCore::TextString& command);

	private:
		InputPtr _input;
		OutputPtr _output;
	};
}
