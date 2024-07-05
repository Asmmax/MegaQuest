#include "DIAssets.hpp"
#include "Game/GameLoop.hpp"
#include "IO/InputHandler.hpp"
#include <fstream>
#include <filesystem>
#include <array>
#include <cassert>

static std::vector<std::string> loadResourcePaths(const std::string& settings)
{
	std::vector<std::string> resourcePaths;
	std::ifstream file;
	file.open(settings);

	if (!file.is_open()) {
		std::string settingsPath = std::filesystem::current_path().string() + "/" + settings;
		std::string errorMessage = "Settings file: " + settingsPath + " could not be open!\n";
		fprintf(stderr, "%s", errorMessage.c_str());
		return resourcePaths;
	}

	resourcePaths.clear();
	for (std::array<char, 256> pathBuff; file.getline(&pathBuff[0], 256);)
		resourcePaths.emplace_back(pathBuff.data());

	file.close();
	return resourcePaths;
}

int main()
{
	auto resourcePaths = loadResourcePaths("settings.dat");
	assert(!resourcePaths.empty());

	ContextManager::Instance().Register();
	ContextManager::Instance().Init(resourcePaths);

    auto inputHandler = ContextManager::Instance().GetContext().GetContainer<IO::InputHandler>().GetRecursive();

    Game::GameLoop game(inputHandler);
    return game.Run();
}
