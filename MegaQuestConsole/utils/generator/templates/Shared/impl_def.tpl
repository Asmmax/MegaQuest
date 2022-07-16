${type_name}Impl_Binder ${type_name}Impl_Binder::instance;

${type_name}Impl_Binder::${type_name}Impl_Binder()
{
    auto impl = std::make_shared<${type_name}Impl>(
        ${type_name}Initializer(
${methods}
        )
${properties}
        );

    ContainerBinder<${full_type_name}>().BindImpl("${type_name}", impl);
	${container_binder_impls}
}

