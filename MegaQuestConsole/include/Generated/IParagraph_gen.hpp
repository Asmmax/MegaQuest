#pragma once
#include "IParagraph.hpp"

#include "Generated/Paragraphs/ConditionalParagraph_gen.hpp"
#include "Generated/Paragraphs/InventoryParagraph_gen.hpp"
#include "Generated/Paragraphs/ParagraphGroup_gen.hpp"
#include "Generated/Paragraphs/ParagraphStateMachine_gen.hpp"
#include "Generated/Paragraphs/TextParagraph_gen.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using IParagraphContainer = Container<QuestCore::IParagraph, ConditionalParagraphImpl, InventoryParagraphImpl, ParagraphGroupImpl, ParagraphStateMachineImpl, TextParagraphImpl>;

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<ConditionalParagraphImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryParagraphImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphGroupImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphStateMachineImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::IParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<TextParagraphImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::IParagraph>>& GlobalContext::GetContainer<QuestCore::IParagraph>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::IParagraph>>> GetReader();
