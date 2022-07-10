#include "Generated/IParagraph_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<ConditionalParagraphImpl>& impl)
{
	BindImplWithCast<IParagraphContainer, ConditionalParagraphImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryParagraphImpl>& impl)
{
	BindImplWithCast<IParagraphContainer, InventoryParagraphImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphGroupImpl>& impl)
{
	BindImplWithCast<IParagraphContainer, ParagraphGroupImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphStateMachineImpl>& impl)
{
	BindImplWithCast<IParagraphContainer, ParagraphStateMachineImpl>(implName, impl);
}

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<TextParagraphImpl>& impl)
{
	BindImplWithCast<IParagraphContainer, TextParagraphImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::IParagraph>>& GlobalContext::GetContainer<QuestCore::IParagraph>()
{
	static std::shared_ptr<ContainerBase<QuestCore::IParagraph>>
		instancePtr = std::make_shared<IParagraphContainer>("paragraphs");
	return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::IParagraph>>> GetReader()
{
	auto container = GlobalContext::GetContainer<QuestCore::IParagraph>();
	return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>(container);
}

