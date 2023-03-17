#include "IO/Logger.hpp"
#include "Game/IOutput.hpp"
#include "Containers/Context.hpp"
#include "Containers/ContextManager.hpp"

using namespace IO;

void Logger::Init(const std::shared_ptr<Logger>& logger)
{
	_instance = logger;
}

Logger& Logger::Instance()
{
	return *_instance;
}

void Logger::SetOutput(const Game::IOutput::Ptr& output)
{
	_output = output;
}

void Logger::Log(const QuestCore::TextString& text)
{
	_output->WriteLn(text);
}
