#include "Generated/Paragraphs/ParagraphStateMachine_gen.hpp"
#include "Generated/IParagraph_gen.hpp"

ParagraphStateMachineImpl_Binder ParagraphStateMachineImpl_Binder::instance;

ParagraphStateMachineImpl_Binder::ParagraphStateMachineImpl_Binder()
{
    auto iParagraphContainer = GlobalContext::GetContainer<QuestCore::IParagraph>();
    ContainerReader<std::shared_ptr<QuestCore::IParagraph>>
        paragraphReader(iParagraphContainer);

    MethodInitializer<QuestCore::ParagraphStateMachine, 
        std::shared_ptr<QuestCore::IParagraph>, 
        ContainerReader
    >
        stateInitializer("state", paragraphReader, nullptr,
            [](const std::shared_ptr<QuestCore::ParagraphStateMachine>& element, const std::shared_ptr<QuestCore::IParagraph>& arg) {
                element->SetState(arg);
            });

    ParagraphStateMachineInitializer paragraphStateMachineInitializer(stateInitializer);
    auto paragraphStateMachineImpl = std::make_shared<ParagraphStateMachineImpl>(
        paragraphStateMachineInitializer);

    if (auto ownContainer = std::dynamic_pointer_cast<ParagraphStateMachineContainer>(GlobalContext::GetContainer<QuestCore::ParagraphStateMachine>())) {
        ownContainer->SetInheritor<ParagraphStateMachineImpl>(
            ReaderImplRecord<ParagraphStateMachineImpl>{ "ParagraphStateMachine", paragraphStateMachineImpl });
    }

    if (auto paragraphContainer = std::dynamic_pointer_cast<IParagraphContainer>(GlobalContext::GetContainer<QuestCore::IParagraph>())) {
        paragraphContainer->SetInheritor<ParagraphStateMachineImpl>(
            ReaderImplRecord<ParagraphStateMachineImpl>{ "ParagraphStateMachine", paragraphStateMachineImpl });
    }
}


template<>
const std::shared_ptr<ContainerBase<QuestCore::ParagraphStateMachine>>& GlobalContext::GetContainer<QuestCore::ParagraphStateMachine>()
{
    static std::shared_ptr<ContainerBase<QuestCore::ParagraphStateMachine>>
        instancePtr = std::make_shared<ParagraphStateMachineContainer>("containers");
    return instancePtr;
}
