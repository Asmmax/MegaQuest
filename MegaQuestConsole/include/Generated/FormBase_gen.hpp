#pragma once

#include "FormBase.hpp"
#include "Forms.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/Factory.hpp"

//FormBase

using FormBaseImpl = FactoryImpl<std::shared_ptr<QuestCore::FormBase>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
>;

//SpecificForm

using SpecificFormImpl = FactoryImpl<std::shared_ptr<QuestCore::SpecificForm>,
    PropertyReader<std::vector<int>, PrimitiveReader<int>>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
>;

//TailForm

using TailFormImpl = FactoryImpl<std::shared_ptr<QuestCore::TailForm>,
    PropertyReader<int, PrimitiveReader<int>>,
    PropertyReader<std::vector<int>, PrimitiveReader<int>>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
>;

//Factories

using FormBaseFactory = Factory<std::shared_ptr<QuestCore::FormBase>, FormBaseImpl, SpecificFormImpl, TailFormImpl>;
