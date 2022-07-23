#include "Containers/ReaderStrategy/EnumReader.hpp"

template <>
std::shared_ptr<IReaderStrategy<${enum_full_type}>> GetReader()
{
    return std::make_shared<EnumReader<${enum_full_type}>>(std::map<std::string, ${enum_full_type}>{
${enum_values}
    });
}
