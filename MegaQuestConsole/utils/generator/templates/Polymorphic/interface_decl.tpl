#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"
#include "Containers/Utils.hpp"

using ${type_name}Factory = Factory<std::shared_ptr<${full_type_name}>>;

DECLARE_FACTORY_BIND_IMPL(std::shared_ptr<${full_type_name}>)
DECLARE_FACTORY(std::shared_ptr<${full_type_name}>)
DECLARE_READER(std::shared_ptr<${full_type_name}>)
