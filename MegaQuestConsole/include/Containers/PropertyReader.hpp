#pragma once
#include "json.hpp"
#include <vector>

template<typename ResultType, template<typename> typename ReaderStrategy>
class PropertyReader
{
public:
	PropertyReader(const std::string& property, const ReaderStrategy<ResultType>& reader, const ResultType& defValue) :
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

		return _reader.Create(*childIt);
	}
	void Init(const nlohmann::json& node)
	{
		auto childIt = node.find(_propertyName);
		if (childIt == node.end()) {
			return;
		}

		_reader.Init(*childIt);
	}
private:
	std::string _propertyName;
	ReaderStrategy<ResultType> _reader;
	ResultType _defValue;
};

// vector specialization
template<typename Type, template<typename> typename ReaderStrategy>
class PropertyReader<std::vector<Type>, ReaderStrategy>
{
public:
	PropertyReader(const std::string& property, const ReaderStrategy<Type>& reader, const std::vector<Type>& defValue) :
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
			results.emplace_back(_reader.Create(child));
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
			_reader.Init(child);
		}
	}
private:
	std::string _propertyName;
	ReaderStrategy<Type> _reader;
	std::vector<Type> _defValue;
};
