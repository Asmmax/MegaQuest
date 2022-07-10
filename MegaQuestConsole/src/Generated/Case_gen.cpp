#include "Generated/Case_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

CaseImpl_Binder CaseImpl_Binder::instance;

CaseImpl_Binder::CaseImpl_Binder()
{
    auto impl = std::make_shared<CaseImpl>(
        CreateProperty<QuestCore::TextString>("name", QuestCore::TextString())
        , CreateProperty<std::vector<std::shared_ptr<QuestCore::IAction>>>("actions", std::vector<std::shared_ptr<QuestCore::IAction>>())
        );

    FactoryBinder<QuestCore::Case>().BindImpl("Case", impl);
}

template<>
template<>
void FactoryBinder<QuestCore::Case>::BindImpl(const std::string& implName, const std::shared_ptr<CaseImpl>& impl)
{
    BindImplWithCast<CaseFactory, CaseImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<QuestCore::Case>>& GlobalContext::GetFactory<QuestCore::Case>()
{
    static std::shared_ptr<IFactory<QuestCore::Case>>
        instancePtr = std::make_shared<CaseFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<QuestCore::Case>> GetReader()
{
    auto factory = GlobalContext::GetFactory<QuestCore::Case>();
    return std::make_shared<FactoryReader<QuestCore::Case>>(factory);
}
