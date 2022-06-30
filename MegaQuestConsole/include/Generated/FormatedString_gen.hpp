#pragma once

#include "FormatedString.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

#include "Containers/Factory.hpp"
#include "Containers/GlobalContext.hpp"

using FormatedStringImpl = FactoryImpl<QuestCore::FormatedString,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::FormBase>>, FactoryReader>
>;

class FormatedStringImpl_Binder
{
public:
    FormatedStringImpl_Binder();

private:
    static FormatedStringImpl_Binder instance;
};

using FormatedStringFactory = Factory<QuestCore::FormatedString, FormatedStringImpl>;

template<>
const std::shared_ptr<IFactory<QuestCore::FormatedString>>& GlobalContext::GetFactory<QuestCore::FormatedString>();
