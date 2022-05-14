#pragma once
#include <functional>
#include <string>
#include <memory>

namespace QuestCore
{
    class TextString;

    class IButtonGroup
    {
    public:
        using Ptr = std::shared_ptr<IButtonGroup>;
        using Callback = std::function<void()>;

        virtual ~IButtonGroup() = default;
        virtual void AddButton(const TextString& text, const Callback& callback) = 0;
    };

    class IButtonPanel
    {
    public:
        virtual ~IButtonPanel() = default;
        virtual void RemoveAllButtons() = 0;
        virtual IButtonGroup& GetButtonGroup(const std::string& actionKey) = 0;
    };
}
