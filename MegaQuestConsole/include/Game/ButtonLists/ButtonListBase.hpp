#pragma once
#include "Game/IButtonList.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	class IOutput;

	class ButtonListBase : public IButtonList
	{
		using OutputPtr = std::shared_ptr<IOutput>;

	public:
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

		using Ptr = std::shared_ptr<ButtonListBase>;

		ButtonListBase(const OutputPtr& output,
			const QuestCore::TextString& error,
			bool show = true);

		virtual void Draw() override;

		void AddButton(const Button& button);
		void Clear();

		virtual bool IsUpdateAfterDone() const override { return true; }

	protected:
		virtual void DoImpl(int answer) override;

	private:
		std::vector<QuestCore::TextString> GetNames() const;

	private:
		std::vector<Button> _buttons;
		OutputPtr _output;
		QuestCore::TextString _error;
		bool _show;
	};
}
