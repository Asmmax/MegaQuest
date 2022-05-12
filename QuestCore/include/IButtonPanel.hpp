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

        virtual ~IButtonGroup() = default;
        virtual void AddButton(const TextString& text, const std::function<void()>& callback) = 0;
    };

    class IButtonPanel
    {
    public:
        virtual ~IButtonPanel() = default;
        virtual void RemoveAllButtons() = 0;
        virtual IButtonGroup& GetButtonGroup(const std::string& actionKey) = 0;
    };

    class IButtonPanelFactory
    {
    public:
        virtual ~IButtonPanelFactory() = default;
        virtual IButtonPanel& GetButtonPanel(const std::string& rootKey) = 0;
    };
}
