#pragma once
#include "Containers/IReaderStrategy.hpp"
#include "json.hpp"
#include <vector>

template<typename ResultType>
class PropertyReader
{
	using ReaderPtr = std::shared_ptr<IReaderStrategy<ResultType>>;
public:
	PropertyReader(const std::string& property, const ReaderPtr& reader, const ResultType& defValue) :
		_propertyName(property),
		_reader(reader),
		_defValue(defValue)
	{
	}

	ResultType Create(const nlohmann::json& node)
	{
		auto childIt = node.find(_propertyName);
		if (childIt == node.end()) {
			return _defValue;
		}

		return _reader->Create(*childIt);
	}
	void Init(const nlohmann::json& node)
	{
		auto childIt = node.find(_propertyName);
		if (childIt == node.end()) {
			return;
		}

		_reader->Init(*childIt);
	}
private:
	std::string _propertyName;
	ReaderPtr _reader;
	ResultType _defValue;
};

// vector specialization
template<typename Type>
class PropertyReader<std::vector<Type>>
{
	using ReaderPtr = std::shared_ptr<IReaderStrategy<Type>>;
public:
	PropertyReader(const std::string& property, const ReaderPtr& reader, const std::vector<Type>& defValue) :
		_propertyName(property),
		_reader(reader),
		_defValue(defValue)
	{
	}

	std::vector<Type> Create(const nlohmann::json& node)
	{
		std::vector<Type> results;

		auto childIt = node.find(_propertyName);
		if (childIt == node.end()) {
			return results;
		}

		for (auto child : *childIt) {
			results.emplace_back(_reader->Create(child));
		}

		return results;
	}
	void Init(const nlohmann::json& node)
	{
		auto childIt = node.find(_propertyName);
		if (childIt == node.end()) {
			return;
		}

		for (auto child : *childIt) {
			_reader->Init(child);
		}
	}
private:
	std::string _propertyName;
	ReaderPtr _reader;
	std::vector<Type> _defValue;
};
