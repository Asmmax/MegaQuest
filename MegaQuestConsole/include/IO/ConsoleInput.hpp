#pragma once
#include "IInput.hpp"

namespace IO
{
	class ConsoleInput : public IInput
	{
	public:
		virtual QuestCore::TextString GetString() const override;
	};
}
