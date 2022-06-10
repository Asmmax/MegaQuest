#include "Config/Settings.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>

using namespace Config;

Settings& Settings::Instance()
{
	static Settings settings("config.json");
	return settings;
}

std::string Settings::GetResourcePath() const
{
    return _resourcePath;
}

std::string Settings::GetQuestPath() const
{
    return GetResourcePath() + "/" + _questFileName;
}

std::string Settings::GetDialogsPath() const
{
    return GetResourcePath() + "/" + _dialogsFileName;
}

std::string Settings::GetCommandsPath() const
{
    return GetResourcePath() + "/" + _commandsFileName;
}

Settings::Settings(const std::string& filename)
{
    Load(filename);
}

void Settings::Load(const std::string& filename)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        return;
    }

    std::string input;
    std::string line;
    while (std::getline(file, line)) {
        input += line + "\n";
    }

    file.close();

    nlohmann::json root;
    try
    {
        root = nlohmann::json::parse(input);
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << ex.what() << std::endl;
        return;
    }

    std::string settingsFileName;
    auto foundIt = root.find("settings");
    if (foundIt != root.end()) {
        settingsFileName = *foundIt;
    }

    LoadSettings(settingsFileName);
}

void Settings::LoadSettings(const std::string& filename)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        return;
    }

    std::string input;
    std::string line;
    while (std::getline(file, line)) {
        input += line + "\n";
    }

    file.close();

    nlohmann::json root;
    try
    {
        root = nlohmann::json::parse(input);
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << ex.what() << std::endl;
        return;
    }

    std::string path = filename;
    auto pos = path.find_last_of("/");
    auto length = path.size() - pos;
    path.erase(pos, length);
    _resourcePath = path;

    auto foundIt = root.find("resourcePath");
    if (foundIt != root.end()) {
        std::string relativePath = *foundIt;
        if (!relativePath.empty()) {
            _resourcePath += "/" + relativePath;
        }
    }

    foundIt = root.find("questFileName");
    if (foundIt != root.end()) {
        _questFileName = *foundIt;
    }

    foundIt = root.find("dialogsFileName");
    if (foundIt != root.end()) {
        _dialogsFileName = *foundIt;
    }

    foundIt = root.find("commandsFileName");
    if (foundIt != root.end()) {
        _commandsFileName = *foundIt;
    }
}
