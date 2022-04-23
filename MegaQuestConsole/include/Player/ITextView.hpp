#pragma once
#include "TextString.hpp"

namespace Player {
	class ITextView
	{
	public:
		virtual ~ITextView() = default;

		virtual void Write(const QuestCore::TextString& text) = 0;
	};
}
