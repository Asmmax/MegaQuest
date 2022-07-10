#pragma once

#include "Case.hpp"

#include "Containers/FactoryImpl.hpp"

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

using CaseImpl = FactoryImpl<QuestCore::Case,
    QuestCore::TextString,
    std::vector<std::shared_ptr<QuestCore::IAction>>
>;

class CaseImpl_Binder
{
public:
    CaseImpl_Binder();

private:
    static CaseImpl_Binder instance;
};

using CaseFactory = Factory<QuestCore::Case, CaseImpl>;

template<>
template<>
void FactoryBinder<QuestCore::Case>::BindImpl(const std::string& implName, const std::shared_ptr<CaseImpl>& impl);

template<>
const std::shared_ptr<IFactory<QuestCore::Case>>& GlobalContext::GetFactory<QuestCore::Case>();

template <>
std::shared_ptr<IReaderStrategy<QuestCore::Case>> GetReader();
