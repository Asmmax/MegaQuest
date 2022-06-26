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
    PropertyReader<std::shared_ptr<QuestCore::IParagraph>, ContainerReader>,
    PropertyReader<std::shared_ptr<QuestCore::IParagraph>, ContainerReader>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICondition>>, FactoryReader>
>;

//InventoryParagraph

using InventoryParagraphImpl = ContainerImpl<QuestCore::InventoryParagraph,
    ContainerInitializer<QuestCore::InventoryParagraph>,
    PropertyReader<QuestCore::FormatedString, FactoryReader>,
    PropertyReader<QuestCore::TextString, FactoryReader>,
    PropertyReader<QuestCore::FormatedString, FactoryReader>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>,
    PropertyReader<std::vector<QuestCore::ItemOrder>, FactoryReader>
>;

// ParagraphGroup

using ParagraphGroupImpl = ContainerImpl<QuestCore::ParagraphGroup,
    ContainerInitializer<QuestCore::ParagraphGroup>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::IParagraph>>, ContainerReader>,
    PropertyReader<QuestCore::TextString, FactoryReader>
>;

// ParagraphStateMachine

using ParagraphStateMachineInitializer = ContainerInitializer<QuestCore::ParagraphStateMachine,
    MethodInitializer<QuestCore::ParagraphStateMachine, std::shared_ptr<QuestCore::IParagraph>, ContainerReader>
>;

using ParagraphStateMachineImpl = ContainerImpl<QuestCore::ParagraphStateMachine,
    ParagraphStateMachineInitializer
>;

// TextParagraph

using TextParagraphImpl = ContainerImpl<QuestCore::TextParagraph,
    ContainerInitializer<QuestCore::TextParagraph>,
    PropertyReader<QuestCore::TextString, FactoryReader>
>;

//Containers

using IParagraphContainer = Container<QuestCore::IParagraph, ConditionalParagraphImpl, InventoryParagraphImpl, ParagraphGroupImpl, ParagraphStateMachineImpl, TextParagraphImpl>;
using ParagraphStateMachineContainer = Container<QuestCore::ParagraphStateMachine, ParagraphStateMachineImpl>;
