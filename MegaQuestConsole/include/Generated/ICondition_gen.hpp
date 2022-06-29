#pragma once
#include "ICondition.hpp"

#include "Generated/Conditions/Comparison_gen.hpp"

#include "Containers/Factory.hpp"
#include "Containers/GlobalContext.hpp"

using IConditionFactory = Factory<std::shared_ptr<QuestCore::ICondition>, ComparisonImpl>;

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::ICondition>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::ICondition>>();
