#include "Containers/ReaderStrategy/FactoryReader.hpp"

${bind_impls}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<${full_type_name}>>>& GlobalContext::GetFactory<std::shared_ptr<${full_type_name}>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<${full_type_name}>>>
        instancePtr = std::make_shared<${type_name}Factory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> GetReader()
{
    auto factory = GlobalContext::GetFactory<std::shared_ptr<${full_type_name}>>();
    return std::make_shared<FactoryReader<std::shared_ptr<${full_type_name}>>>(factory);
}

