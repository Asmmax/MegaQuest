#include "Generated/IAction_gen.hpp"

template<>
const std::shared_ptr<ContainerBase<QuestCore::IAction>>& GlobalContext::GetContainer<QuestCore::IAction>()
{
	static std::shared_ptr<ContainerBase<QuestCore::IAction>>
		instancePtr = std::make_shared<IActionContainer>("actions");
	return instancePtr;
}
