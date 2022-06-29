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
        ContainerReader<std::shared_ptr<QuestCore::IParagraph>>
    >
        stateInitializer("state", paragraphReader, nullptr,
            [](const std::shared_ptr<QuestCore::ParagraphStateMachine>& element, const std::shared_ptr<QuestCore::IParagraph>& arg) {
                element->SetState(arg);
            });

    ParagraphStateMachineInitializer paragraphStateMachineInitializer(stateInitializer);
    auto paragraphStateMachineImpl = std::make_shared<ParagraphStateMachineImpl>(
        paragraphStateMachineInitializer);

    if (auto paragraphContainer = std::dynamic_pointer_cast<IParagraphContainer>(GlobalContext::GetContainer<QuestCore::IParagraph>())) {
        paragraphContainer->SetInheritor<ParagraphStateMachineImpl>(
            ReaderImplRecord<ParagraphStateMachineImpl>{ "ParagraphStateMachine", paragraphStateMachineImpl });
    }
}
