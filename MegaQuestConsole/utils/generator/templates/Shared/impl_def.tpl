${dependencies}
#include "Containers/Context.hpp"
#include "Containers/RegisterBinder.hpp"

void RegisterBinder<${full_type_name}>::Init(Context& context)
{
    auto impl = std::make_shared<${type_name}Impl>(
		"${shared_name}"
		,"${type_name}"
        ,${type_name}Initializer(
${methods}
        )
${properties}
        );
		
	context.RegisterContainerReader(impl);

	context.GetContainer<${full_type_name}>()->AddInheritor(impl);
	${container_binder_impls}
}

RegisterBinder<${full_type_name}> ${type_name}Impl_Binder;

