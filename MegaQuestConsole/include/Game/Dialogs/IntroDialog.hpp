#pragma once
#include "TextString.hpp"
#include "Game/IDialog.hpp"

namespace Game
{
	class IOutput;

	class IntroDialog : public IDialog
	{
		using OutputPtr = std::shared_ptr<IOutput>;

	public:
		using Ptr = std::shared_ptr<IntroDialog>;

		IntroDialog(const OutputPtr& output,
			const QuestCore::TextString& intro);

		virtual void Init() override;

	protected:
		OutputPtr GetOutput();

	private:
		OutputPtr _output;
		QuestCore::TextString _intro;
	};
}
