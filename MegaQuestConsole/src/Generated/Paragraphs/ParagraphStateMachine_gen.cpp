#include "Generated/Paragraphs/ParagraphStateMachine_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

ParagraphStateMachineImpl_Binder ParagraphStateMachineImpl_Binder::instance;

ParagraphStateMachineImpl_Binder::ParagraphStateMachineImpl_Binder()
{
    auto impl = std::make_shared<ParagraphStateMachineImpl>(
        ParagraphStateMachineInitializer(
            CreateMethod<QuestCore::ParagraphStateMachine, std::shared_ptr<QuestCore::IParagraph>>("state", nullptr,
                [](const std::shared_ptr<QuestCore::ParagraphStateMachine>& element, const std::shared_ptr<QuestCore::IParagraph>& arg) {
                    element->SetState(arg);
                })
        )
        );

    ContainerBinder<QuestCore::ParagraphStateMachine>().BindImpl("ParagraphStateMachine", impl);
    ContainerBinder<QuestCore::IParagraph>().BindImpl("ParagraphStateMachine", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::ParagraphStateMachine>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphStateMachineImpl>& impl)
{
    BindImplWithCast<ParagraphStateMachineContainer, ParagraphStateMachineImpl>(implName, impl);
}


template<>
const std::shared_ptr<ContainerBase<QuestCore::ParagraphStateMachine>>& GlobalContext::GetContainer<QuestCore::ParagraphStateMachine>()
{
    static std::shared_ptr<ContainerBase<QuestCore::ParagraphStateMachine>>
        instancePtr = std::make_shared<ParagraphStateMachineContainer>("containers");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ParagraphStateMachine>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::ParagraphStateMachine>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::ParagraphStateMachine>>>(container);
}
