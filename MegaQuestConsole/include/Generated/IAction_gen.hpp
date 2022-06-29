#pragma once
#include "IAction.hpp"

#include "Generated/Actions/CaseContainerSwitching_gen.hpp"
#include "Generated/Actions/Clearing_gen.hpp"
#include "Generated/Actions/Copying_gen.hpp"
#include "Generated/Actions/ParagraphSwitching_gen.hpp"
#include "Generated/Actions/Transfer_gen.hpp"

#include "Containers/Container.hpp"
#include "Containers/GlobalContext.hpp"

using IActionContainer = Container<QuestCore::IAction, CaseContainerSwitchingImpl, ParagraphSwitchingImpl, ClearingImpl, CopyingImpl, TransferImpl>;

template<>
const std::shared_ptr<ContainerBase<QuestCore::IAction>>& GlobalContext::GetContainer<QuestCore::IAction>();
