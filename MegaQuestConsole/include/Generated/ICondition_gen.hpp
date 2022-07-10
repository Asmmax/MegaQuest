#pragma once
#include "ICondition.hpp"

#include "Generated/Conditions/Comparison_gen.hpp"

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

using IConditionFactory = Factory<std::shared_ptr<QuestCore::ICondition>, ComparisonImpl>;

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::ICondition>>::BindImpl(const std::string& implName, const std::shared_ptr<ComparisonImpl>& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::ICondition>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::ICondition>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ICondition>>> GetReader();
