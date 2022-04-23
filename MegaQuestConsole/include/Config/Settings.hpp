#pragma once
#include <string>

namespace Config 
{
	class Settings
	{
	public:
		static Settings& Instance();
		std::string GetResourcePath() const;

	private:
		Settings(const std::string& filename);
		void Load(const std::string& filename);

	private:
		std::string _resourcePath;
	};
}