#include "IO/Logger.hpp"
#include "Game/IOutput.hpp"
#include "Containers/Context.hpp"
#include "Containers/ContextManager.hpp"

using namespace IO;

Logger& Logger::Instance()
{
	static std::shared_ptr<Logger> instance = ContextManager::Instance().GetContext().GetContainer<Logger>()->Get();
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
