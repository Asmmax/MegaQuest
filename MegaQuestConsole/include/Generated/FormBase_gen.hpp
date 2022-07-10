#pragma once

#include "FormBase.hpp"

#include "Generated/Forms_gen.hpp"

#include "Containers/FactoryImpl.hpp"

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

using FormBaseImpl = FactoryImpl<std::shared_ptr<QuestCore::FormBase>,
    QuestCore::TextString
>;

class FormBaseImpl_Binder
{
public:
    FormBaseImpl_Binder();

private:
    static FormBaseImpl_Binder instance;
};

using FormBaseFactory = Factory<std::shared_ptr<QuestCore::FormBase>, FormBaseImpl, SpecificFormImpl, TailFormImpl>;

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::FormBase>>::BindImpl(const std::string& implName, const std::shared_ptr<FormBaseImpl>& impl);

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::FormBase>>::BindImpl(const std::string& implName, const std::shared_ptr<SpecificFormImpl>& impl);

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::FormBase>>::BindImpl(const std::string& implName, const std::shared_ptr<TailFormImpl>& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::FormBase>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::FormBase>>> GetReader();
