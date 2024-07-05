#include "IO/Logger.hpp"
#include "Game/IOutput.hpp"
#include "Containers/Context.hpp"
#include "Containers/ContextManager.hpp"

using namespace IO;

Logger& Logger::Instance()
{
	Logger* instance = ContextManager::Instance().GetContext().GetContainer<Logger>().GetRecursive();
	return *instance;
}

void Logger::Init(Game::IOutput* output)
{
	_output = output;
}

void Logger::Log(const QuestCore::TextString& text)
{
	_output->WriteLn(text);
}
