#pragma once

#include "Case.hpp"

#include "IAction.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

#include "Containers/Factory.hpp"
#include "Containers/GlobalContext.hpp"

using CaseImpl = FactoryImpl<QuestCore::Case,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::IAction>>, ContainerReader<std::shared_ptr<QuestCore::IAction>>>
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
const std::shared_ptr<IFactory<QuestCore::Case>>& GlobalContext::GetFactory<QuestCore::Case>();
