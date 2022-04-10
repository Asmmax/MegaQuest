#pragma once
#include <string>

namespace Player {
	class ITextView
	{
	public:
		virtual ~ITextView() = default;

		virtual void Write(const std::string& text) = 0;
	};
}
