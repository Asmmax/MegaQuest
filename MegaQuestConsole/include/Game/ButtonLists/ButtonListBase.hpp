#pragma once
#include "Game/IButtonList.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	/// @serializable @abstract
	class ButtonListBase : public IButtonList
	{
	public:
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

		using Ptr = std::shared_ptr<ButtonListBase>;

		ButtonListBase(const QuestCore::TextString& error,
			bool show = true);

		virtual void Draw(IOutput& output) override;

		void AddButton(const Button& button);
		void Clear();

		virtual bool IsUpdateAfterDone() const override { return true; }

	protected:
		virtual void DoImpl(int answer) override;

	private:
		std::vector<QuestCore::TextString> GetNames() const;

	private:
		std::vector<Button> _buttons;
		QuestCore::TextString _error;
		bool _show;
	};
}
