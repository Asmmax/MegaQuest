#pragma once

#include "FormatedString.hpp"

#include "Containers/FactoryImpl.hpp"

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

using FormatedStringImpl = FactoryImpl<QuestCore::FormatedString,
    std::vector<std::shared_ptr<QuestCore::FormBase>>
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
template<>
void FactoryBinder<QuestCore::FormatedString>::BindImpl(const std::string& implName, const std::shared_ptr<FormatedStringImpl>& impl);

template<>
const std::shared_ptr<IFactory<QuestCore::FormatedString>>& GlobalContext::GetFactory<QuestCore::FormatedString>();

template <>
std::shared_ptr<IReaderStrategy<QuestCore::FormatedString>> GetReader();
