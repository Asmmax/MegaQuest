#pragma once

#include "FormBase.hpp"

#include "Generated/Forms_gen.hpp"

#include "Containers/Factory.hpp"
#include "Containers/GlobalContext.hpp"

using FormBaseImpl = FactoryImpl<std::shared_ptr<QuestCore::FormBase>,
    PropertyReader<QuestCore::TextString, FactoryReader>
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
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::FormBase>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>();
