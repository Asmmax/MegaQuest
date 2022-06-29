#pragma once
#include "Actions/ParagraphSwitching.hpp"

#include "IParagraph.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"

using ParagraphSwitchingInitializer = ContainerInitializer<QuestCore::ParagraphSwitching,
    MethodInitializer<QuestCore::ParagraphSwitching, std::shared_ptr<QuestCore::ParagraphStateMachine>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>, std::shared_ptr<QuestCore::ParagraphStateMachine>>>,
    MethodInitializer<QuestCore::ParagraphSwitching, std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>
>;

using ParagraphSwitchingImpl = ContainerImpl<QuestCore::ParagraphSwitching,
    ParagraphSwitchingInitializer
>;

class ParagraphSwitchingImpl_Binder
{
public:
    ParagraphSwitchingImpl_Binder();

private:
    static ParagraphSwitchingImpl_Binder instance;
};
