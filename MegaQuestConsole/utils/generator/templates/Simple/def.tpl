${dependencies}

${type_name}Impl_Binder ${type_name}Impl_Binder::instance;

${type_name}Impl_Binder::${type_name}Impl_Binder()
{
    auto impl = std::make_shared<${type_name}Impl>("${type_name}"
${properties}
        );

    FactoryBinder<${full_type_name}>().BindImpl(impl);
}

#include "Containers/ReaderStrategy/FactoryReader.hpp"

template<>
void FactoryBinder<${full_type_name}>::BindImpl(const FactoryBinder::FactoryImplPtr& impl)
{
    BindImplWithCast<${type_name}Factory>(impl);
}

template<>
const std::shared_ptr<IFactory<${full_type_name}>>& GlobalContext::GetFactory<${full_type_name}>()
{
    static std::shared_ptr<IFactory<${full_type_name}>>
        instancePtr = std::make_shared<${type_name}Factory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<${full_type_name}>> GetReader()
{
    auto factory = GlobalContext::GetFactory<${full_type_name}>();
    return std::make_shared<FactoryReader<${full_type_name}>>(factory);
}
