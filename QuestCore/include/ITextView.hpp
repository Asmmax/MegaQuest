#pragma once
#include <string>

namespace QuestCore
{
    class TextString;

    class ITextView
    {
    public:
        virtual ~ITextView() = default;
        virtual void Clear() = 0;
        virtual void AppendText(const TextString& text) = 0;
    };

    class ITextViewFactory
    {
    public:
        virtual ~ITextViewFactory() = default;
        virtual ITextView& GetTextView(const std::string& rootKey) = 0;
    };
}
