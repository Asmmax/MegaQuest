#pragma once
#include "IAction.hpp"

#include "Generated/Actions/CaseContainerSwitching_gen.hpp"
#include "Generated/Actions/Clearing_gen.hpp"
#include "Generated/Actions/Copying_gen.hpp"
#include "Generated/Actions/ParagraphSwitching_gen.hpp"
#include "Generated/Actions/Transfer_gen.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using IActionContainer = Container<QuestCore::IAction, CaseContainerSwitchingImpl, ParagraphSwitchingImpl, ClearingImpl, CopyingImpl, TransferImpl>;

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerSwitchingImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<ParagraphSwitchingImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<ClearingImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<CopyingImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::IAction>::BindImpl(const std::string& implName, const std::shared_ptr<TransferImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::IAction>>& GlobalContext::GetContainer<QuestCore::IAction>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::IAction>>> GetReader();
