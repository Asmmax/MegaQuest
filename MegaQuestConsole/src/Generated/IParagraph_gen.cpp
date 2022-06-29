#include "Generated/IParagraph_gen.hpp"

template<>
const std::shared_ptr<ContainerBase<QuestCore::IParagraph>>& GlobalContext::GetContainer<QuestCore::IParagraph>()
{
	static std::shared_ptr<ContainerBase<QuestCore::IParagraph>>
		instancePtr = std::make_shared<IParagraphContainer>("paragraphs");
	return instancePtr;
}
