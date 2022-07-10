#include "Generated/Forms_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

//SpecificForm

SpecificFormImpl_Binder SpecificFormImpl_Binder::instance;

SpecificFormImpl_Binder::SpecificFormImpl_Binder()
{
    auto impl = std::make_shared<SpecificFormImpl>(
        CreateProperty<std::vector<int>>("counts", std::vector<int>())
        , CreateProperty<QuestCore::TextString>("text", QuestCore::TextString())
        );

    FactoryBinder<std::shared_ptr<QuestCore::SpecificForm>>().BindImpl("SpecificForm", impl);
    FactoryBinder<std::shared_ptr<QuestCore::FormBase>>().BindImpl("SpecificForm", impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::SpecificForm>>::BindImpl(const std::string& implName, const std::shared_ptr<SpecificFormImpl>& impl)
{
    BindImplWithCast<SpecificFormFactory, SpecificFormImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::SpecificForm>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::SpecificForm>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::SpecificForm>>>
        instancePtr = std::make_shared<SpecificFormFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::SpecificForm>>> GetReader()
{
    auto factory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::SpecificForm>>();
    return std::make_shared<FactoryReader<std::shared_ptr<QuestCore::SpecificForm>>>(factory);
}

//TailForm

TailFormImpl_Binder TailFormImpl_Binder::instance;

TailFormImpl_Binder::TailFormImpl_Binder()
{
    auto impl = std::make_shared<TailFormImpl>(
        CreateProperty<int>("notation", 0)
        , CreateProperty<std::vector<int>>("digits", std::vector<int>())
        , CreateProperty<QuestCore::TextString>("text", QuestCore::TextString())
        );

    FactoryBinder<std::shared_ptr<QuestCore::TailForm>>().BindImpl("TailForm", impl);
    FactoryBinder<std::shared_ptr<QuestCore::FormBase>>().BindImpl("TailForm", impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::TailForm>>::BindImpl(const std::string& implName, const std::shared_ptr<TailFormImpl>& impl)
{
    BindImplWithCast<TailFormFactory, TailFormImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::TailForm>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::TailForm>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::TailForm>>>
        instancePtr = std::make_shared<TailFormFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::TailForm>>> GetReader()
{
    auto factory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::TailForm>>();
    return std::make_shared<FactoryReader<std::shared_ptr<QuestCore::TailForm>>>(factory);
}
