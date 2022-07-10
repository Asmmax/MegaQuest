#include "Generated/Paragraphs/ConditionalParagraph_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

ConditionalParagraphImpl_Binder ConditionalParagraphImpl_Binder::instance;

ConditionalParagraphImpl_Binder::ConditionalParagraphImpl_Binder()
{
    auto impl = std::make_shared<ConditionalParagraphImpl>(
        ConditionalParagraphInitializer(
        )
        , CreateProperty<std::shared_ptr<QuestCore::IParagraph>>("thenParagraph", nullptr)
        , CreateProperty<std::shared_ptr<QuestCore::IParagraph>>("elseParagraph", nullptr)
        , CreateProperty<std::vector<std::shared_ptr<QuestCore::ICondition>>>("conditions", std::vector<std::shared_ptr<QuestCore::ICondition>>())
        );

    ContainerBinder< QuestCore::ConditionalParagraph>().BindImpl("ConditionalParagraph", impl);
    ContainerBinder< QuestCore::IParagraph>().BindImpl("ConditionalParagraph", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::ConditionalParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<ConditionalParagraphImpl>& impl)
{
    BindImplWithCast<ConditionalParagraphContainer, ConditionalParagraphImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::ConditionalParagraph>>& GlobalContext::GetContainer<QuestCore::ConditionalParagraph>()
{
    static std::shared_ptr<ContainerBase<QuestCore::ConditionalParagraph>>
        instancePtr = std::make_shared<ConditionalParagraphContainer>("paragraphs");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ConditionalParagraph>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::ConditionalParagraph>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::ConditionalParagraph>>>(container);
}
