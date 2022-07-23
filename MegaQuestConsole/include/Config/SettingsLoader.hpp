#pragma once
#include "json.hpp"

namespace Config
{
	class SettingsLoader
	{
	public:
		static void Load(const std::string& configFile);

	private:
		static nlohmann::json LoadJson(const std::string& filename);
		static void LoadSettings(const std::string& settingsPath);
	};
}