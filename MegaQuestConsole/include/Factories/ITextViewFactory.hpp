#pragma once
#include <memory>
#include <string>

namespace QuestCore
{
	class ITextView;
}

class ITextViewFactory
{
protected:
	using TextViewPtr = std::shared_ptr<QuestCore::ITextView>;

public:
	virtual ~ITextViewFactory() = default;
	virtual TextViewPtr GetTextView(const std::string& root) = 0;
};
