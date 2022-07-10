#include "Containers/Utils.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"

template<>
std::shared_ptr<IReaderStrategy<bool>> GetReader()
{
	return std::make_shared<PrimitiveReader<bool>>();
}

template<>
std::shared_ptr<IReaderStrategy<int>> GetReader()
{
	return std::make_shared<PrimitiveReader<int>>();
}

template<>
std::shared_ptr<IReaderStrategy<std::string>> GetReader()
{
	return std::make_shared<PrimitiveReader<std::string>>();
}
