#pragma once
#include "Paragraphs/ParagraphStateMachine.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using ParagraphStateMachineInitializer = ContainerInitializer<QuestCore::ParagraphStateMachine,
    std::shared_ptr<QuestCore::IParagraph>
>;

using ParagraphStateMachineImpl = ContainerImpl<QuestCore::ParagraphStateMachine,
    ParagraphStateMachineInitializer
>;

class ParagraphStateMachineImpl_Binder
{
public:
    ParagraphStateMachineImpl_Binder();

private:
    static ParagraphStateMachineImpl_Binder instance;
};

using ParagraphStateMachineContainer = Container<QuestCore::ParagraphStateMachine, ParagraphStateMachineImpl>;

template<>
template<>
void ContainerBinder<QuestCore::ParagraphStateMachine>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphStateMachineImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::ParagraphStateMachine>>& GlobalContext::GetContainer<QuestCore::ParagraphStateMachine>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ParagraphStateMachine>>> GetReader();
