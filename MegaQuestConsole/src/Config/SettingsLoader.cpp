#include "Config/SettingsLoader.hpp"

#include "Containers/GlobalRootReader.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>

using namespace Config;

void SettingsLoader::Load(const std::string& configFile)
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

nlohmann::json SettingsLoader::LoadJson(const std::string& filename)
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

void SettingsLoader::LoadSettings(const std::string& settingsPath)
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
        GlobalRootReader::Instance().AddRoot(jsonAsset);
    }
    GlobalRootReader::Instance().Read();
}