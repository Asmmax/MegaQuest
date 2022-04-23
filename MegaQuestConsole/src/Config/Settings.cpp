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
    return _resourcePath + "/"; 
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

    auto foundIt = root.find("resourcePath");
    if (foundIt != root.end()) {
        _resourcePath = *foundIt;
    }
}

