#pragma once
#include "Paragraphs/ConditionalParagraph.hpp"
#include "Paragraphs/InventoryParagraph.hpp"
#include "Paragraphs/ParagraphGroup.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"
#include "Paragraphs/TextParagraph.hpp"
#include "IParagraph.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Container.hpp"

namespace QuestCore
{
    class ICondition;
    class FormatedString;
    class TextString;
    class Inventory;
    struct ItemRecord;
}

//ConditionalParagraph

using ConditionalParagraphImpl = ContainerImpl<QuestCore::ConditionalParagraph,
    ContainerInitializer<QuestCore::ConditionalParagraph>,
    PropertyReader<std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>,
    PropertyReader<std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICondition>>, FactoryReader<std::shared_ptr<QuestCore::ICondition>>>
>;

//InventoryParagraph

using InventoryParagraphImpl = ContainerImpl<QuestCore::InventoryParagraph,
    ContainerInitializer<QuestCore::InventoryParagraph>,
    PropertyReader<QuestCore::FormatedString, FactoryReader<QuestCore::FormatedString>>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>,
    PropertyReader<QuestCore::FormatedString, FactoryReader<QuestCore::FormatedString>>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>,
    PropertyReader<std::vector<QuestCore::ItemOrder>, FactoryReader<QuestCore::ItemOrder>>
>;

// ParagraphGroup

using ParagraphGroupImpl = ContainerImpl<QuestCore::ParagraphGroup,
    ContainerInitializer<QuestCore::ParagraphGroup>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::IParagraph>>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
>;

// ParagraphStateMachine

using ParagraphStateMachineInitializer = ContainerInitializer<QuestCore::ParagraphStateMachine,
    MethodInitializer<QuestCore::ParagraphStateMachine, std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>
>;

using ParagraphStateMachineImpl = ContainerImpl<QuestCore::ParagraphStateMachine,
    ParagraphStateMachineInitializer
>;

// TextParagraph

using TextParagraphImpl = ContainerImpl<QuestCore::TextParagraph,
    ContainerInitializer<QuestCore::TextParagraph>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
>;

//Containers

using IParagraphContainer = Container<QuestCore::IParagraph, ConditionalParagraphImpl, InventoryParagraphImpl, ParagraphGroupImpl, ParagraphStateMachineImpl, TextParagraphImpl>;
using ParagraphStateMachineContainer = Container<QuestCore::ParagraphStateMachine, ParagraphStateMachineImpl>;
