#pragma once
#include "Actions/ParagraphSwitching.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using ParagraphSwitchingInitializer = ContainerInitializer<QuestCore::ParagraphSwitching,
    std::shared_ptr<QuestCore::ParagraphStateMachine>,
    std::shared_ptr<QuestCore::IParagraph>
>;

using ParagraphSwitchingImpl = ContainerImpl<QuestCore::ParagraphSwitching,
    ParagraphSwitchingInitializer
>;

class ParagraphSwitchingImpl_Binder
{
public:
    ParagraphSwitchingImpl_Binder();

private:
    static ParagraphSwitchingImpl_Binder instance;
};

using ParagraphSwitchingContainer = Container<QuestCore::ParagraphSwitching, ParagraphSwitchingImpl>;

template<>
template<>
void ContainerBinder<QuestCore::ParagraphSwitching>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphSwitchingImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::ParagraphSwitching>>& GlobalContext::GetContainer<QuestCore::ParagraphSwitching>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ParagraphSwitching>>> GetReader();
