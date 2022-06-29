#pragma once
#include "IParagraph.hpp"

#include "Generated/Paragraphs/ConditionalParagraph_gen.hpp"
#include "Generated/Paragraphs/InventoryParagraph_gen.hpp"
#include "Generated/Paragraphs/ParagraphGroup_gen.hpp"
#include "Generated/Paragraphs/ParagraphStateMachine_gen.hpp"
#include "Generated/Paragraphs/TextParagraph_gen.hpp"

#include "Containers/Container.hpp"
#include "Containers/GlobalContext.hpp"

using IParagraphContainer = Container<QuestCore::IParagraph, ConditionalParagraphImpl, InventoryParagraphImpl, ParagraphGroupImpl, ParagraphStateMachineImpl, TextParagraphImpl>;

template<>
const std::shared_ptr<ContainerBase<QuestCore::IParagraph>>& GlobalContext::GetContainer<QuestCore::IParagraph>();
