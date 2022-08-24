#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Context.hpp"

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> Context::GetReader()
{
    auto factory = GetFactory<std::shared_ptr<${full_type_name}>>();
    return std::make_shared<FactoryReader<std::shared_ptr<${full_type_name}>>>(factory);
}

