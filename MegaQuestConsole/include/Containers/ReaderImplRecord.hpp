#pragma once
#include <string>
#include <memory>

template<typename Impl>
struct ReaderImplRecord
{
	std::string type;
	std::shared_ptr<Impl> impl;
};
