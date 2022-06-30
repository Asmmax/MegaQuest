#include "Generated/Actions/ParagraphSwitching_gen.hpp"
#include "Generated/IAction_gen.hpp"

ParagraphSwitchingImpl_Binder ParagraphSwitchingImpl_Binder::instance;

ParagraphSwitchingImpl_Binder::ParagraphSwitchingImpl_Binder()
{
    auto iParagraphContainer = GlobalContext::GetContainer<QuestCore::IParagraph>();
    ContainerReader<std::shared_ptr<QuestCore::IParagraph>>
        paragraphReader(iParagraphContainer);

    auto paragraphStateMachineContainer = GlobalContext::GetContainer<QuestCore::ParagraphStateMachine>();
    ContainerReader<std::shared_ptr<QuestCore::ParagraphStateMachine>>
        paragraphStateMachineReader(paragraphStateMachineContainer);

    MethodInitializer<QuestCore::ParagraphSwitching, 
        std::shared_ptr<QuestCore::ParagraphStateMachine>, 
        ContainerReader
    >
        paragraphStateMachineInitializer("stateMachine", paragraphStateMachineReader, nullptr,
            [](const std::shared_ptr<QuestCore::ParagraphSwitching>& element, const std::shared_ptr<QuestCore::ParagraphStateMachine>& arg) {
                element->SetStateMachine(arg);
            });

    MethodInitializer<QuestCore::ParagraphSwitching, 
        std::shared_ptr<QuestCore::IParagraph>, 
        ContainerReader
    >
        paragraphInitializer("nextParagraph", paragraphReader, nullptr,
            [](const std::shared_ptr<QuestCore::ParagraphSwitching>& element, const std::shared_ptr<QuestCore::IParagraph>& arg) {
                element->SetNextParagraph(arg);
            });

    ParagraphSwitchingInitializer paragraphSwitchingInitializer(paragraphStateMachineInitializer, paragraphInitializer);
    auto paragraphSwitchingImpl = std::make_shared<ParagraphSwitchingImpl>(paragraphSwitchingInitializer);

    if (auto actionContainer = std::dynamic_pointer_cast<IActionContainer>(GlobalContext::GetContainer<QuestCore::IAction>())) {
        actionContainer->SetInheritor<ParagraphSwitchingImpl>(
            ReaderImplRecord<ParagraphSwitchingImpl>{ "ParagraphSwitching", paragraphSwitchingImpl });
    }
}
