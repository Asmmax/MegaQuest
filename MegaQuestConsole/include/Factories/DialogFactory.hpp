#pragma once
#include <vector>
#include <memory>

class IRootFactory;

namespace Game 
{
	class IDialog;
	class IOutput;
}

class DialogFactory
{
	using OutputPtr = std::shared_ptr<Game::IOutput>;
	using DialogPtr = std::shared_ptr<Game::IDialog>;
	using RootFactoryPtr = std::shared_ptr<IRootFactory>;

public:
	DialogFactory(const OutputPtr& output, const RootFactoryPtr& rootFactory);
	DialogPtr GetDialog();

private:
	void Read();

private:
	bool _isRed;
	OutputPtr _output;
	RootFactoryPtr _rootFactory;
	DialogPtr _dialog;
};
