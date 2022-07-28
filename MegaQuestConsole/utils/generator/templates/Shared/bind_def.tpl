template<>
template<>
void ContainerBinder<${full_type_name}>::BindImpl(const std::shared_ptr<${impl_type_name}Impl>& impl)
{
	BindImplWithCast<${type_name}Container, ${impl_type_name}Impl>(impl);
}
