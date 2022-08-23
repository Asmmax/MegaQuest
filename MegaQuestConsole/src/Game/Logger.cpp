#include "IO/Logger.hpp"
#include "Game/IOutput.hpp"
#include "Containers/Context.hpp"

using namespace IO;

DECLARE_CONTAINER(Logger)

Logger& Logger::Instance()
{
	static std::shared_ptr<Logger> instance = Context::Global().GetContainer<Logger>()->Get();
	return *instance;
}

void Logger::Init(const Game::IOutput::Ptr& output)
{
	_output = output;
}

void Logger::Log(const QuestCore::TextString& text)
{
	_output->WriteLn(text);
}
