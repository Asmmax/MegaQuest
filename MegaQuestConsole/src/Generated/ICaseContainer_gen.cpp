#include "Generated/ICaseContainer_gen.hpp"

template<>
const std::shared_ptr<ContainerBase<QuestCore::ICaseContainer>>& GlobalContext::GetContainer<QuestCore::ICaseContainer>()
{
	static std::shared_ptr<ContainerBase<QuestCore::ICaseContainer>> 
		instancePtr = std::make_shared<ICaseContainerContainer>("containers");
	return instancePtr;
}
