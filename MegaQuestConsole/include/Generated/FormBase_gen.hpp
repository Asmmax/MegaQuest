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
    PropertyReader<QuestCore::TextString, FactoryReader>
>;

//SpecificForm

using SpecificFormImpl = FactoryImpl<std::shared_ptr<QuestCore::SpecificForm>,
    PropertyReader<std::vector<int>, PrimitiveReader>,
    PropertyReader<QuestCore::TextString, FactoryReader>
>;

//TailForm

using TailFormImpl = FactoryImpl<std::shared_ptr<QuestCore::TailForm>,
    PropertyReader<int, PrimitiveReader>,
    PropertyReader<std::vector<int>, PrimitiveReader>,
    PropertyReader<QuestCore::TextString, FactoryReader>
>;

//Factories

using FormBaseFactory = Factory<std::shared_ptr<QuestCore::FormBase>, FormBaseImpl, SpecificFormImpl, TailFormImpl>;
