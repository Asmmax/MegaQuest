#include "Generated/FormBase_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

FormBaseImpl_Binder FormBaseImpl_Binder::instance;

FormBaseImpl_Binder::FormBaseImpl_Binder()
{
    auto impl = std::make_shared<FormBaseImpl>(
        CreateProperty<QuestCore::TextString>("text", QuestCore::TextString())
        );

    FactoryBinder<std::shared_ptr<QuestCore::FormBase>>().BindImpl("FormBase", impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::FormBase>>::BindImpl(const std::string& implName, const std::shared_ptr<FormBaseImpl>& impl)
{
    BindImplWithCast<FormBaseFactory, FormBaseImpl>(implName, impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::FormBase>>::BindImpl(const std::string& implName, const std::shared_ptr<SpecificFormImpl>& impl)
{
    BindImplWithCast<FormBaseFactory, SpecificFormImpl>(implName, impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::FormBase>>::BindImpl(const std::string& implName, const std::shared_ptr<TailFormImpl>& impl)
{
    BindImplWithCast<FormBaseFactory, TailFormImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::FormBase>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::FormBase>>>
        instancePtr = std::make_shared<FormBaseFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::FormBase>>> GetReader()
{
    auto factory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::FormBase>>();
    return std::make_shared<FactoryReader<std::shared_ptr<QuestCore::FormBase>>>(factory);
}
