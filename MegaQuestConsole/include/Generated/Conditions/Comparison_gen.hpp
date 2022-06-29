#pragma once
#include "Conditions/Comparison.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/ReaderStrategy/EnumReader.hpp"

using ComparisonImpl = FactoryImpl<std::shared_ptr<QuestCore::Comparison>,
    PropertyReader<std::shared_ptr<QuestCore::Value>, FactoryReader<std::shared_ptr<QuestCore::Value>>>,
    PropertyReader<std::shared_ptr<QuestCore::Value>, FactoryReader<std::shared_ptr<QuestCore::Value>>>,
    PropertyReader<QuestCore::Operation, EnumReader<QuestCore::Operation>>
>;

class ComparisonImpl_Binder
{
public:
    ComparisonImpl_Binder();

private:
    static ComparisonImpl_Binder instance;
};
