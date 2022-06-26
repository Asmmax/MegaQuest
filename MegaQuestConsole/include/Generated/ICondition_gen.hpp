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
    PropertyReader<std::shared_ptr<QuestCore::Value>, FactoryReader>,
    PropertyReader<std::shared_ptr<QuestCore::Value>, FactoryReader>,
    PropertyReader<QuestCore::Operation, EnumReader>
>;

//Factories

using IConditionFactory = Factory<std::shared_ptr<QuestCore::ICondition>, ComparisonImpl>;
