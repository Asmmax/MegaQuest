#include "IO/Logger.hpp"
#include "Game/IOutput.hpp"

using namespace IO;

Logger& Logger::Instance()
{
	static Logger logger;
	return logger;
}

void Logger::Init(const Game::IOutput::Ptr& output)
{
	_output = output;
}

void Logger::Log(const QuestCore::TextString& text)
{
	_output->WriteLn(text);
}
