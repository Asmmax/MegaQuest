#include "Generated/ICondition_gen.hpp"

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::ICondition>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::ICondition>>()
{
	static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::ICondition>>>
		instancePtr = std::make_shared<IConditionFactory>();
	return instancePtr;
}
