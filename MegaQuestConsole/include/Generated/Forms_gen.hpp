#pragma once

#include "Forms.hpp"

#include "Containers/FactoryImpl.hpp"

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

//SpecificForm

using SpecificFormImpl = FactoryImpl<std::shared_ptr<QuestCore::SpecificForm>,
    std::vector<int>,
    QuestCore::TextString
>;

class SpecificFormImpl_Binder
{
public:
    SpecificFormImpl_Binder();

private:
    static SpecificFormImpl_Binder instance;
};

using SpecificFormFactory = Factory<std::shared_ptr<QuestCore::SpecificForm>, SpecificFormImpl>;

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::SpecificForm>>::BindImpl(const std::string& implName, const std::shared_ptr<SpecificFormImpl>& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::SpecificForm>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::SpecificForm>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::SpecificForm>>> GetReader();

//TailForm

using TailFormImpl = FactoryImpl<std::shared_ptr<QuestCore::TailForm>,
    int,
    std::vector<int>,
    QuestCore::TextString
>;

class TailFormImpl_Binder
{
public:
    TailFormImpl_Binder();

private:
    static TailFormImpl_Binder instance;
};

using TailFormFactory = Factory<std::shared_ptr<QuestCore::TailForm>, TailFormImpl>;

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::TailForm>>::BindImpl(const std::string& implName, const std::shared_ptr<TailFormImpl>& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::TailForm>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::TailForm>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::TailForm>>> GetReader();
