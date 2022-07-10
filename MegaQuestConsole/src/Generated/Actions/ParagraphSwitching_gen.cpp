#include "Generated/Actions/ParagraphSwitching_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

ParagraphSwitchingImpl_Binder ParagraphSwitchingImpl_Binder::instance;

ParagraphSwitchingImpl_Binder::ParagraphSwitchingImpl_Binder()
{
    auto impl = std::make_shared<ParagraphSwitchingImpl>(
        ParagraphSwitchingInitializer(
            CreateMethod<QuestCore::ParagraphSwitching,std::shared_ptr<QuestCore::ParagraphStateMachine>>("stateMachine", nullptr,
                [](const std::shared_ptr<QuestCore::ParagraphSwitching>& element, const std::shared_ptr<QuestCore::ParagraphStateMachine>& arg) {
                    element->SetStateMachine(arg);
                }),
            CreateMethod<QuestCore::ParagraphSwitching, std::shared_ptr<QuestCore::IParagraph>>("nextParagraph", nullptr,
                [](const std::shared_ptr<QuestCore::ParagraphSwitching>& element, const std::shared_ptr<QuestCore::IParagraph>& arg) {
                    element->SetNextParagraph(arg);
                })
        )
        );

    ContainerBinder<QuestCore::ParagraphSwitching>().BindImpl("ParagraphSwitching", impl);
    ContainerBinder<QuestCore::IAction>().BindImpl("ParagraphSwitching", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::ParagraphSwitching>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphSwitchingImpl>& impl)
{
    BindImplWithCast<ParagraphSwitchingContainer, ParagraphSwitchingImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::ParagraphSwitching>>& GlobalContext::GetContainer<QuestCore::ParagraphSwitching>()
{
    static std::shared_ptr<ContainerBase<QuestCore::ParagraphSwitching>>
        instancePtr = std::make_shared<ParagraphSwitchingContainer>("actions");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ParagraphSwitching>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::ParagraphSwitching>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::ParagraphSwitching>>>(container);
}
