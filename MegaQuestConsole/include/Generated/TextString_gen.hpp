#pragma once

#include "TextString.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"

#include "Containers/Factory.hpp"
#include "Containers/GlobalContext.hpp"

//TextString

using TextStringImpl = FactoryImpl<QuestCore::TextString,
    PropertyReader<std::string, PrimitiveReader>
>;

class TextStringImpl_Binder
{
public:
    TextStringImpl_Binder();

private:
    static TextStringImpl_Binder instance;
};

using TextStringFactory = Factory<QuestCore::TextString, TextStringImpl>;

template<>
const std::shared_ptr<IFactory<QuestCore::TextString>>& GlobalContext::GetFactory<QuestCore::TextString>();
