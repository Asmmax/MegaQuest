#pragma once
#include "Paragraphs/ConditionalParagraph.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/PropertyReader.hpp"

using ConditionalParagraphImpl = ContainerImpl<QuestCore::ConditionalParagraph,
    ContainerInitializer<QuestCore::ConditionalParagraph>,
    PropertyReader<std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>,
    PropertyReader<std::shared_ptr<QuestCore::IParagraph>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICondition>>, FactoryReader<std::shared_ptr<QuestCore::ICondition>>>
>;

class ConditionalParagraphImpl_Binder
{
public:
    ConditionalParagraphImpl_Binder();

private:
    static ConditionalParagraphImpl_Binder instance;
};
