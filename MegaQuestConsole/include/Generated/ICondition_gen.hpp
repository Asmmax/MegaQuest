#pragma once

#include "Conditions/Comparison.hpp"
#include "ICondition.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/ReaderStrategy/EnumReader.hpp"
#include "Containers/Factory.hpp"

//Comparison

using ComparisonImpl = FactoryImpl<std::shared_ptr<QuestCore::Comparison>,
    PropertyReader<std::shared_ptr<QuestCore::Value>, FactoryReader<std::shared_ptr<QuestCore::Value>>>,
    PropertyReader<std::shared_ptr<QuestCore::Value>, FactoryReader<std::shared_ptr<QuestCore::Value>>>,
    PropertyReader<QuestCore::Operation, EnumReader<QuestCore::Operation>>
>;

//Factories

using IConditionFactory = Factory<std::shared_ptr<QuestCore::ICondition>, ComparisonImpl>;
