#pragma once
#include "Player/ITextView.hpp"

namespace IO
{
	class ConsoleView : public Player::ITextView
	{
	public:
		ConsoleView(const QuestCore::TextString& intro);
		virtual void Write(const QuestCore::TextString& text) override;
	};
}
