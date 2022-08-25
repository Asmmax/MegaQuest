#include "Containers/ContextManager.hpp"
#include "Containers/Context.hpp"

ContextManager& ContextManager::Instance()
{
	static ContextManager instance;
	return instance;
}

Context& ContextManager::GetContext(const std::string& id)
{
	if (_contexts.find(id) == _contexts.end()) {
		auto newContext = std::make_unique<Context>(id);
		_contexts.emplace(id, std::move(newContext));
	}
	return *_contexts[id];
}

void ContextManager::AddRoot(const nlohmann::json& root, const std::string& id)
{
	GetContext(id).AddRoot(root);
}

void ContextManager::Read()
{
	for (auto& context : _contexts) {
		context.second->Read();
	}
}
