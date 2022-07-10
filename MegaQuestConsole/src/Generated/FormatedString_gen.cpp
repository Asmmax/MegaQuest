#include "Generated/FormatedString_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

FormatedStringImpl_Binder FormatedStringImpl_Binder::instance;

FormatedStringImpl_Binder::FormatedStringImpl_Binder()
{
    auto impl = std::make_shared<FormatedStringImpl>(
        CreateProperty<std::vector<std::shared_ptr<QuestCore::FormBase>>>("forms", std::vector<std::shared_ptr<QuestCore::FormBase>>())
        );

    FactoryBinder<QuestCore::FormatedString>().BindImpl("FormatedString", impl);
}

template<>
template<>
void FactoryBinder<QuestCore::FormatedString>::BindImpl(const std::string& implName, const std::shared_ptr<FormatedStringImpl>& impl)
{
    BindImplWithCast<FormatedStringFactory, FormatedStringImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<QuestCore::FormatedString>>& GlobalContext::GetFactory<QuestCore::FormatedString>()
{
    static std::shared_ptr<IFactory<QuestCore::FormatedString>>
        instancePtr = std::make_shared<FormatedStringFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<QuestCore::FormatedString>> GetReader()
{
    auto factory = GlobalContext::GetFactory<QuestCore::FormatedString>();
    return std::make_shared<FactoryReader<QuestCore::FormatedString>>(factory);
}
