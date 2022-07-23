#pragma once
#include "Utils/Reader.hpp"

template<typename Type>
class ContainerBase
{
	using TypePtr = std::shared_ptr<Type>;

public:
	ContainerBase(const std::string& groupName) :
		_groupName(groupName)
	{
	}

	virtual ~ContainerBase() = default;

	void AddRoot(const nlohmann::json& root) 
	{
		auto foundIt = root.find(_groupName);
		if (foundIt == root.end()) {
			return;
		}

		_roots.push_back(*foundIt);
	}

	void CreateAll()
	{
		for (auto& root : _roots) {
			for (auto& node : root) {
				Create(node);
			}
		}
	}

	void InitAll()
	{
		for (auto& root : _roots) {
			for (auto& node : root) {
				Init(node);
			}
		}
	}

	void CreateById(const std::string& id)
	{
		for (auto& root : _roots) {
			for (auto& child : root) {
				auto childId = Utils::Read(child, "id", std::string());
				if (!childId.empty() && childId == id) {
					Create(child);
				}
			}
		}
	}

	void InitById(const std::string& id)
	{
		for (auto& root : _roots) {
			for (auto& child : root) {
				auto childId = Utils::Read(child, "id", std::string());
				if (!childId.empty() && childId == id) {
					Init(child);
				}
			}
		}
	}

	virtual void Create(const nlohmann::json& node) = 0;
	virtual void Init(const nlohmann::json& node) = 0;
	virtual TypePtr Get(const std::string& id) = 0;
	virtual TypePtr Get() = 0;

private:
	std::string _groupName;
	std::vector<nlohmann::json> _roots;
};
