#pragma once
#include "json.hpp"
#include <string>
#include <map>
#include <memory>

class Context;

class ContextManager
{
public:
	static ContextManager& Instance();

	Context& GetContext(const std::string& id = std::string());

	void AddRoot(const nlohmann::json& root, const std::string& id = std::string());
	void Read();

private:
	std::map<std::string, std::unique_ptr<Context>> _contexts;
};
