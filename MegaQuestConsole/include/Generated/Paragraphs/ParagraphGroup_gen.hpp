#pragma once
#include "Paragraphs/ParagraphGroup.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using ParagraphGroupInitializer = ContainerInitializer<QuestCore::ParagraphGroup>;

using ParagraphGroupImpl = ContainerImpl<QuestCore::ParagraphGroup,
    ParagraphGroupInitializer,
    std::vector<std::shared_ptr<QuestCore::IParagraph>>,
    QuestCore::TextString
>;

class ParagraphGroupImpl_Binder
{
public:
    ParagraphGroupImpl_Binder();

private:
    static ParagraphGroupImpl_Binder instance;
};

using ParagraphGroupContainer = Container<QuestCore::ParagraphGroup, ParagraphGroupImpl>;

template<>
template<>
void ContainerBinder<QuestCore::ParagraphGroup>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphGroupImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::ParagraphGroup>>& GlobalContext::GetContainer<QuestCore::ParagraphGroup>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ParagraphGroup>>> GetReader();
