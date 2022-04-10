#pragma once
#include "Player/ITextView.hpp"

namespace IO
{
	class ConsoleView : public Player::ITextView
	{
	public:
		ConsoleView(const std::string& intro);
		virtual void Write(const std::string& text) override;
	};
}
