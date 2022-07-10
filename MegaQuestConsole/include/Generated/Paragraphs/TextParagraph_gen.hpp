#pragma once
#include "Paragraphs/TextParagraph.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using TextParagraphInitializer = ContainerInitializer<QuestCore::TextParagraph>;

using TextParagraphImpl = ContainerImpl<QuestCore::TextParagraph,
    TextParagraphInitializer,
    QuestCore::TextString
>;

class TextParagraphImpl_Binder
{
public:
    TextParagraphImpl_Binder();

private:
    static TextParagraphImpl_Binder instance;
};

using TextParagraphContainer = Container<QuestCore::TextParagraph, TextParagraphImpl>;

template<>
template<>
void ContainerBinder<QuestCore::TextParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<TextParagraphImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::TextParagraph>>& GlobalContext::GetContainer<QuestCore::TextParagraph>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::TextParagraph>>> GetReader();
