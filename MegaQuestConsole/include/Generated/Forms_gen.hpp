#pragma once

#include "Forms.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"

//SpecificForm

using SpecificFormImpl = FactoryImpl<std::shared_ptr<QuestCore::SpecificForm>,
    PropertyReader<std::vector<int>, PrimitiveReader<int>>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
>;

class SpecificFormImpl_Binder
{
public:
    SpecificFormImpl_Binder();

private:
    static SpecificFormImpl_Binder instance;
};

//TailForm

using TailFormImpl = FactoryImpl<std::shared_ptr<QuestCore::TailForm>,
    PropertyReader<int, PrimitiveReader<int>>,
    PropertyReader<std::vector<int>, PrimitiveReader<int>>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>
>;

class TailFormImpl_Binder
{
public:
    TailFormImpl_Binder();

private:
    static TailFormImpl_Binder instance;
};
