#pragma once
#include "json.hpp"
#include <string>
#include <map>
#include <memory>

#include "Containers/Context.hpp"

class ContextManager
{
public:
	static ContextManager& Instance()
	{
		static ContextManager instance;
		return instance;
	}

	Context& GetContext(const std::string& id = std::string())
	{
		if (_contexts.find(id) == _contexts.end()) {
			auto newContext = std::make_unique<Context>(id);
			_contexts.emplace(id, std::move(newContext));
		}
		return *_contexts[id];
	}

	void AddRoot(const nlohmann::json& root, const std::string& id = std::string())
	{
		GetContext(id).AddRoot(root);
	}

	void Read()
	{
		for (auto& context : _contexts) {
			context.second->Read();
		}
	}

private:
	std::map<std::string, std::unique_ptr<Context>> _contexts;
};
