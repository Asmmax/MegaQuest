#pragma once
#include "Paragraphs/ParagraphGroup.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/PropertyReader.hpp"

using ParagraphGroupImpl = ContainerImpl<QuestCore::ParagraphGroup,
    ContainerInitializer<QuestCore::ParagraphGroup>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::IParagraph>>, ContainerReader<std::shared_ptr<QuestCore::IParagraph>>>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
>;

class ParagraphGroupImpl_Binder
{
public:
    ParagraphGroupImpl_Binder();

private:
    static ParagraphGroupImpl_Binder instance;
};
