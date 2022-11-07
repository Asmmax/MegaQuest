${dependencies}
#include "Containers/Context.hpp"
#include "Containers/RegisterBinder.hpp"

void RegisterBinder<${full_type_name}>::Init(Context& context)
{
    auto impl = std::make_shared<${type_name}Impl>("${type_name}"
${properties}
        );

	context.GetFactory<${full_type_name}>()->AddInheritor(impl);
}

RegisterBinder<${full_type_name}> ${type_name}Impl_Binder;

#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Context.hpp"

template <>
std::shared_ptr<IReaderStrategy<${full_type_name}>> Context::GetReader()
{
    auto factory = GetFactory<${full_type_name}>();
    return std::make_shared<FactoryReader<${full_type_name}>>(factory);
}
