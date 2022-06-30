#pragma once
#include "Paragraphs/ParagraphStateMachine.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/GlobalContext.hpp"

using ParagraphStateMachineInitializer = ContainerInitializer<QuestCore::ParagraphStateMachine,
    MethodInitializer<QuestCore::ParagraphStateMachine, std::shared_ptr<QuestCore::IParagraph>, ContainerReader>
>;

using ParagraphStateMachineImpl = ContainerImpl<QuestCore::ParagraphStateMachine,
    ParagraphStateMachineInitializer
>;

class ParagraphStateMachineImpl_Binder
{
public:
    ParagraphStateMachineImpl_Binder();

private:
    static ParagraphStateMachineImpl_Binder instance;
};

using ParagraphStateMachineContainer = Container<QuestCore::ParagraphStateMachine, ParagraphStateMachineImpl>;

template<>
const std::shared_ptr<ContainerBase<QuestCore::ParagraphStateMachine>>& GlobalContext::GetContainer<QuestCore::ParagraphStateMachine>();
