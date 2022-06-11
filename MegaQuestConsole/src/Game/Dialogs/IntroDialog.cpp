#include "Game/Dialogs/IntroDialog.hpp"
#include "Game/IOutput.hpp"

using namespace Game;


IntroDialog::IntroDialog(const OutputPtr& output,
	const QuestCore::TextString& intro) :

	_output(output),
	_intro(intro)
{
}

void IntroDialog::Init()
{
	_output->WriteLn(_intro);
}

IOutput::Ptr IntroDialog::GetOutput()
{
	return _output;
}
