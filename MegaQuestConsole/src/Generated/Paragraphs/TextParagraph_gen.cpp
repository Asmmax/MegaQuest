#include "Generated/Paragraphs/TextParagraph_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

TextParagraphImpl_Binder TextParagraphImpl_Binder::instance;

TextParagraphImpl_Binder::TextParagraphImpl_Binder()
{
    auto impl = std::make_shared<TextParagraphImpl>(
        TextParagraphInitializer(
        )
        , CreateProperty<QuestCore::TextString>("text", QuestCore::TextString())
        );

    ContainerBinder<QuestCore::TextParagraph>().BindImpl("TextParagraph", impl);
    ContainerBinder<QuestCore::IParagraph>().BindImpl("TextParagraph", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::TextParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<TextParagraphImpl>& impl)
{
    BindImplWithCast<TextParagraphContainer, TextParagraphImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::TextParagraph>>& GlobalContext::GetContainer<QuestCore::TextParagraph>()
{
    static std::shared_ptr<ContainerBase<QuestCore::TextParagraph>>
        instancePtr = std::make_shared<TextParagraphContainer>("paragraphs");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::TextParagraph>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::TextParagraph>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::TextParagraph>>>(container);
}
