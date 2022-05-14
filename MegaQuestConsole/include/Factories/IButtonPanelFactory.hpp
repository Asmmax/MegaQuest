#pragma once
#include <memory>
#include <string>

namespace QuestCore
{
	class IButtonPanel;
}

class IButtonPanelFactory
{
protected:
	using ButtonsPtr = std::shared_ptr<QuestCore::IButtonPanel>;

public:
	virtual ~IButtonPanelFactory() = default;
	virtual ButtonsPtr GetButtonPanel(const std::string& root) = 0;
};
