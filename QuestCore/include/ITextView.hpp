#pragma once
#include <string>

namespace QuestCore
{
    class TextString;

    class ITextView
    {
    public:
        virtual ~ITextView() = default;
        virtual void AppendText(const TextString& text) = 0;
    };
}
