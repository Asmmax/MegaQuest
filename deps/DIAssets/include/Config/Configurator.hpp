#pragma once
#include "json.hpp"
#include "Containers/ContextManager.hpp"
#include "Utils/Reader.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>

class Configurator : public ContextManager
{
public:
	void Load(const std::string& configFile)
	{
		auto configJson = LoadJson(configFile);
		if (configJson.empty()) {
			return;
		}

		std::string settingsPath;
		auto foundIt = configJson.find("assets");
		if (foundIt != configJson.end()) {
			settingsPath = *foundIt;
		}

		LoadSettings(settingsPath);
	}

private:
	void LoadSettings(const std::string& settingsPath)
	{
		for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(settingsPath))
		{
			if (dir_entry.is_directory()) {
				continue;
			}

			if (dir_entry.path().extension().u8string() != ".json") {
				continue;
			}

			auto jsonAsset = LoadJson(dir_entry.path().u8string());
			auto relativePath = std::filesystem::relative(dir_entry.path(), settingsPath);
			auto rawContextId = relativePath.replace_extension().u8string();
			std::replace(rawContextId.begin(), rawContextId.end(), '\\', '/');
			auto contextId = ReadContextId(jsonAsset, rawContextId);
			AddRoot(jsonAsset, contextId);
		}
		Read();
	}

	static nlohmann::json LoadJson(const std::string& filename)
	{
		nlohmann::json root;

		std::fstream file;
		file.open(filename, std::ios::in);
		if (!file.is_open()) {
			return root;
		}

		std::string input;
		std::string line;
		while (std::getline(file, line)) {
			input += line + "\n";
		}

		file.close();

		try
		{
			root = nlohmann::json::parse(input);
		}
		catch (nlohmann::json::parse_error& ex)
		{
			std::cerr << ex.what() << std::endl;
		}

		return root;
	}

	static std::string ReadContextId(const nlohmann::json& asset, const std::string& defaultId)
	{
		if (asset.find("contextId") != asset.end()) {
			return Utils::Read(asset, "contextId", std::string());
		}
		return defaultId;
	}
};
