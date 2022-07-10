#pragma once

#include "TextString.hpp"

#include "Containers/FactoryImpl.hpp"

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

//TextString

using TextStringImpl = FactoryImpl<QuestCore::TextString,
    std::string
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
template<>
void FactoryBinder<QuestCore::TextString>::BindImpl(const std::string& implName, const std::shared_ptr<TextStringImpl>& impl);

template<>
const std::shared_ptr<IFactory<QuestCore::TextString>>& GlobalContext::GetFactory<QuestCore::TextString>();

template <>
std::shared_ptr<IReaderStrategy<QuestCore::TextString>> GetReader();
