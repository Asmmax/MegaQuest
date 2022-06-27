#pragma once

#include "Case.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Factory.hpp"

//Case

using CaseImpl = FactoryImpl<QuestCore::Case,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::IAction>>, ContainerReader<std::shared_ptr<QuestCore::IAction>>>
>;

//Factories

using CaseFactory = Factory<QuestCore::Case, CaseImpl>;
