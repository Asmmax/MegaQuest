#pragma once
#include "Paragraphs/TextParagraph.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/PropertyReader.hpp"

using TextParagraphImpl = ContainerImpl<QuestCore::TextParagraph,
    ContainerInitializer<QuestCore::TextParagraph>,
    PropertyReader<QuestCore::TextString, FactoryReader>
>;

class TextParagraphImpl_Binder
{
public:
    TextParagraphImpl_Binder();

private:
    static TextParagraphImpl_Binder instance;
};
