#pragma once
#include "Actions/CaseContainerSwitching.hpp"
#include "Actions/ParagraphSwitching.hpp"
#include "Actions/Clearing.hpp"
#include "Actions/Copying.hpp"
#include "Actions/Transfer.hpp"
#include "IAction.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Container.hpp"

#include <memory>

namespace QuestCore
{
    class CaseContainerStateMachine;
    class ICaseContainer;
    class ParagraphStateMachine;
    class IParagraph;
    class Inventory;
    struct ItemRecord;
}

//CaseContainerSwitching

using ContainerSwitchingInitializer = ContainerInitializer<QuestCore::CaseContainerSwitching,
    MethodInitializer<QuestCore::CaseContainerSwitching, std::shared_ptr<QuestCore::CaseContainerStateMachine>, ContainerReader>,
    MethodInitializer<QuestCore::CaseContainerSwitching, std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>
>;

using CaseContainerSwitchingImpl = ContainerImpl<QuestCore::CaseContainerSwitching,
    ContainerSwitchingInitializer
>;

//ParagraphSwitching

using ParagraphSwitchingInitializer = ContainerInitializer<QuestCore::ParagraphSwitching,
    MethodInitializer<QuestCore::ParagraphSwitching, std::shared_ptr<QuestCore::ParagraphStateMachine>, ContainerReader>,
    MethodInitializer<QuestCore::ParagraphSwitching, std::shared_ptr<QuestCore::IParagraph>, ContainerReader>
>;

using ParagraphSwitchingImpl = ContainerImpl<QuestCore::ParagraphSwitching,
    ParagraphSwitchingInitializer
>;

// Clearing

using ClearingImpl = ContainerImpl<QuestCore::Clearing,
    ContainerInitializer<QuestCore::Clearing>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>
>;

// Copying

using CopyingImpl = ContainerImpl<QuestCore::Copying,
    ContainerInitializer<QuestCore::Copying>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>
>;

// Transfer

using TransferImpl = ContainerImpl<QuestCore::Transfer,
    ContainerInitializer<QuestCore::Transfer>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>,
    PropertyReader<std::vector<QuestCore::ItemRecord>, FactoryReader>
>;

//Containers

using IActionContainer = Container<QuestCore::IAction, CaseContainerSwitchingImpl, ParagraphSwitchingImpl, ClearingImpl, CopyingImpl, TransferImpl>;
