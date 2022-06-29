#pragma once
#include "GlobalContext.hpp"
#include "ContainerBase.hpp"
#include <functional>
#include <vector>

class GlobalRootReader
{
	using AddRootCallback = std::function<void(const nlohmann::json&)>;
	using VoidCallback = std::function<void()>;

public:
	static GlobalRootReader& Instance();

	void AddRoot(const nlohmann::json& root);

	template <typename Type>
	void AddContainer()
	{
		_addRootCallbacks.push_back([](const nlohmann::json& root) {
			GlobalContext::GetContainer<Type>()->AddRoot(root);
			});

		_createAllCallbacks.push_back([]() {
			GlobalContext::GetContainer<Type>()->CreateAll();
			});

		_initAllCallbacks.push_back([]() {
			GlobalContext::GetContainer<Type>()->InitAll();
			});
	}

private:
	std::vector<AddRootCallback> _addRootCallbacks;
	std::vector<VoidCallback> _createAllCallbacks;
	std::vector<VoidCallback> _initAllCallbacks;
};
