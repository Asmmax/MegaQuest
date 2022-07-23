#pragma once
#include "Game/IInput.hpp"

namespace IO
{
	/// @serializable
	class ConsoleInput : public Game::IInput
	{
	public:
		virtual QuestCore::TextString GetString() const override;
	};
}
