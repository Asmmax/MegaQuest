#pragma once
#include "TextString.hpp"
#include "Game/IDialog.hpp"
#include <vector>

namespace Game
{
	class IOutput;

	class DialogBase : public IDialog
	{
		using OutputPtr = std::shared_ptr<IOutput>;
		using ButtonListPtr = std::shared_ptr<IButtonList>;

	public:
		using Ptr = std::shared_ptr<DialogBase>;

		DialogBase(const OutputPtr& output,
			const QuestCore::TextString& intro);

		virtual void Init() override;
		virtual void Update() override;
		virtual void Draw() override;
		void AddButtonList(const ButtonListPtr& buttonList);

	protected:
		OutputPtr GetOutput();

	private:
		OutputPtr _output;
		QuestCore::TextString _intro;
		std::vector<ButtonListPtr> _buttonGroups;
	};
}
