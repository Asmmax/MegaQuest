#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"
#include "Containers/Utils.hpp"

using ${type_name}Factory = Factory<std::shared_ptr<${full_type_name}>>;

template<>
void FactoryBinder<std::shared_ptr<${full_type_name}>>::BindImpl(const FactoryBinder::FactoryImplPtr& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<${full_type_name}>>>& GlobalContext::GetFactory<std::shared_ptr<${full_type_name}>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<${full_type_name}>>> GetReader();
