#pragma once
#include <vector>
#include <memory>

class IRootFactory;

namespace Game 
{
	class Dialog;
	class IOutput;
}

class DialogFactory
{
	using OutputPtr = std::shared_ptr<Game::IOutput>;
	using DialogPtr = std::shared_ptr<Game::Dialog>;
	using RootFactoryPtr = std::shared_ptr<IRootFactory>;

public:
	DialogFactory(const OutputPtr& output, const RootFactoryPtr& rootFactory);
	std::vector<DialogPtr> GetDialogs();

private:
	void Read();

private:
	bool _isRed;
	OutputPtr _output;
	RootFactoryPtr _rootFactory;
	std::vector< DialogPtr> _dialogs;
};
