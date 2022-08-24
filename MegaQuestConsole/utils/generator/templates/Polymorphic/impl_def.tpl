${dependencies}
#include "Containers/Context.hpp"
#include "Containers/RegisterBinder.hpp"

void RegisterBinder<${full_type_name}>::Init(Context& context)
{
    auto impl = std::make_shared<${type_name}Impl>("${type_name}"
${properties}
        );

    context.GetFactory<std::shared_ptr<${full_type_name}>>()->AddInheritor(impl);
	${factory_binder_impls}
}

RegisterBinder<${full_type_name}> ${type_name}Impl_Binder;
