#pragma once
#include "Paragraphs/ParagraphStateMachine.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"

using ParagraphStateMachineInitializer = ContainerInitializer<QuestCore::ParagraphStateMachine,
    MethodInitializer<QuestCore::ParagraphStateMachine, std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>
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
