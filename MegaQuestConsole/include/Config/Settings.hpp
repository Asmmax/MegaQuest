#pragma once
#include <string>

namespace Config 
{
	class Settings
	{
	public:
		static Settings& Instance();
		std::string GetResourcePath() const;
		std::string GetQuestPath() const;
		std::string GetUISettingsPath() const;

	private:
		Settings(const std::string& filename);
		void Load(const std::string& filename);
		void LoadSettings(const std::string& filename);

	private:
		std::string _resourcePath;
		std::string _questFileName;
		std::string _uiSettingsFileName;
	};
}
