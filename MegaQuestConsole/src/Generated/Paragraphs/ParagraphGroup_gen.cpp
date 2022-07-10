#include "Generated/Paragraphs/ParagraphGroup_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

ParagraphGroupImpl_Binder ParagraphGroupImpl_Binder::instance;

ParagraphGroupImpl_Binder::ParagraphGroupImpl_Binder()
{
    auto impl = std::make_shared<ParagraphGroupImpl>(
        ParagraphGroupInitializer(
        )
        , CreateProperty<std::vector<std::shared_ptr<QuestCore::IParagraph>>>("children", std::vector<std::shared_ptr<QuestCore::IParagraph>>())
        , CreateProperty<QuestCore::TextString>("gap", QuestCore::TextString())
        );

    ContainerBinder<QuestCore::ParagraphGroup>().BindImpl("ParagraphGroup", impl);
    ContainerBinder<QuestCore::IParagraph>().BindImpl("ParagraphGroup", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::ParagraphGroup>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphGroupImpl>& impl)
{
    BindImplWithCast<ParagraphGroupContainer, ParagraphGroupImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::ParagraphGroup>>& GlobalContext::GetContainer<QuestCore::ParagraphGroup>()
{
    static std::shared_ptr<ContainerBase<QuestCore::ParagraphGroup>>
        instancePtr = std::make_shared<ParagraphGroupContainer>("paragraphs");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ParagraphGroup>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::ParagraphGroup>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::ParagraphGroup>>>(container);
}
