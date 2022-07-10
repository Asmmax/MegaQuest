#pragma once
#include "Paragraphs/ConditionalParagraph.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using ConditionalParagraphInitializer = ContainerInitializer<QuestCore::ConditionalParagraph>;

using ConditionalParagraphImpl = ContainerImpl<QuestCore::ConditionalParagraph,
    ConditionalParagraphInitializer,
    std::shared_ptr<QuestCore::IParagraph>,
    std::shared_ptr<QuestCore::IParagraph>,
    std::vector<std::shared_ptr<QuestCore::ICondition>>
>;

class ConditionalParagraphImpl_Binder
{
public:
    ConditionalParagraphImpl_Binder();

private:
    static ConditionalParagraphImpl_Binder instance;
};

using ConditionalParagraphContainer = Container<QuestCore::ConditionalParagraph, ConditionalParagraphImpl>;

template<>
template<>
void ContainerBinder<QuestCore::ConditionalParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<ConditionalParagraphImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::ConditionalParagraph>>& GlobalContext::GetContainer<QuestCore::ConditionalParagraph>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ConditionalParagraph>>> GetReader();
