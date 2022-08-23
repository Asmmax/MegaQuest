#include "Containers/ReaderStrategy/FactoryReader.hpp"

template<>
void FactoryBinder<std::shared_ptr<${full_type_name}>>::BindImpl(const FactoryBinder::FactoryImplPtr& impl)
{
    BindImplWithCast<${type_name}Factory>(impl);
}

template<>
template<>
std::shared_ptr<IFactory<std::shared_ptr<${full_type_name}>>> ContainerFactory<IFactory>::Create<std::shared_ptr<${full_type_name}>>()
{
    return std::make_shared<${type_name}Factory>();
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> GetReader()
{
    auto factory = Context::Global().GetFactory<std::shared_ptr<${full_type_name}>>();
    return std::make_shared<FactoryReader<std::shared_ptr<${full_type_name}>>>(factory);
}

