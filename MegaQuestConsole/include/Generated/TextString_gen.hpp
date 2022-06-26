#pragma once

#include "TextString.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/Factory.hpp"

//TextString

using TextStringImpl = FactoryImpl<QuestCore::TextString,
    PropertyReader<std::string, PrimitiveReader>
>;

//Factories

using TextStringFactory = Factory<QuestCore::TextString, TextStringImpl>;
