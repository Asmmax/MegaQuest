#pragma once

#include "FormatedString.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Factory.hpp"

//FormatedString

using FormatedStringImpl = FactoryImpl<QuestCore::FormatedString,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::FormBase>>, FactoryReader>
>;

//Factories

using FormatedStringFactory = Factory<QuestCore::FormatedString, FormatedStringImpl>;
