#include "Generated/TextString_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

TextStringImpl_Binder TextStringImpl_Binder::instance;

TextStringImpl_Binder::TextStringImpl_Binder()
{
    auto impl = std::make_shared<TextStringImpl>(
        CreateProperty<std::string>("u8", std::string())
        );

    FactoryBinder<QuestCore::TextString>().BindImpl("TextString", impl);
}

template<>
template<>
void FactoryBinder<QuestCore::TextString>::BindImpl(const std::string& implName, const std::shared_ptr<TextStringImpl>& impl)
{
    BindImplWithCast<TextStringFactory, TextStringImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<QuestCore::TextString>>& GlobalContext::GetFactory<QuestCore::TextString>()
{
    static std::shared_ptr<IFactory<QuestCore::TextString>>
        instancePtr = std::make_shared<TextStringFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<QuestCore::TextString>> GetReader()
{
    auto factory = GlobalContext::GetFactory<QuestCore::TextString>();
    return std::make_shared<FactoryReader<QuestCore::TextString>>(factory);
}
