${dependencies}
#include "Containers/Context.hpp"

${type_name}Impl_Binder ${type_name}Impl_Binder::instance;

${type_name}Impl_Binder::${type_name}Impl_Binder()
{
    auto impl = std::make_shared<${type_name}Impl>("${type_name}"
${properties}
        );

	Context::Global().GetFactory<${full_type_name}>()->AddInheritor(impl);
}

#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Context.hpp"

template <>
std::shared_ptr<IReaderStrategy<${full_type_name}>> GetReader()
{
    auto factory = Context::Global().GetFactory<${full_type_name}>();
    return std::make_shared<FactoryReader<${full_type_name}>>(factory);
}
