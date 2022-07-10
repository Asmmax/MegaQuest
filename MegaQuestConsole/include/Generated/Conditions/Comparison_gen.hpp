#pragma once
#include "Conditions/Comparison.hpp"

#include "Containers/FactoryImpl.hpp"

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

template <>
std::shared_ptr<IReaderStrategy<QuestCore::Operation>> GetReader();

using ComparisonImpl = FactoryImpl<std::shared_ptr<QuestCore::Comparison>,
    std::shared_ptr<QuestCore::Value>,
    std::shared_ptr<QuestCore::Value>,
    QuestCore::Operation
>;

class ComparisonImpl_Binder
{
public:
    ComparisonImpl_Binder();

private:
    static ComparisonImpl_Binder instance;
};

using ComparisonFactory = Factory<std::shared_ptr<QuestCore::Comparison>, ComparisonImpl>;

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::Comparison>>::BindImpl(const std::string& implName, const std::shared_ptr<ComparisonImpl>& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Comparison>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::Comparison>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Comparison>>> GetReader();
