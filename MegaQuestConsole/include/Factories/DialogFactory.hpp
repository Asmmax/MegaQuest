#pragma once
#include "json.hpp"
#include "TextString.hpp"
#include <vector>
#include <memory>

class IRootFactory;

namespace Game 
{
	class IOutput;
	class IDialog;
	class IButtonList;
}

class DialogFactory
{
	using OutputPtr = std::shared_ptr<Game::IOutput>;
	using DialogPtr = std::shared_ptr<Game::IDialog>;
	using ButtonListPtr = std::shared_ptr<Game::IButtonList>;
	using RootFactoryPtr = std::shared_ptr<IRootFactory>;

public:
	DialogFactory(const std::string& filename, const OutputPtr& output, const RootFactoryPtr& rootFactory);
	DialogPtr GetRootDialog();
	DialogPtr GetDialog(const std::string& id);

private:
	void Read();
	void CreateDialogs(const nlohmann::json& dialogsNode);
	DialogPtr CreateDialog(const nlohmann::json& dialogNode);
	void ReadDialogs(const nlohmann::json& dialogsNode);
	void InitDialog(const DialogPtr& dialog, const nlohmann::json& dialogNode);
	void ReadRootDialog(const nlohmann::json& rootNode);
	void ReadButtonLists(const nlohmann::json& buttonListsNode);
	ButtonListPtr ReadButtonList(const nlohmann::json& buttonListNode);

	std::vector<std::pair<std::string, ButtonListPtr>> ReadButtonGroups(const nlohmann::json& buttonGroupsNode);

private:
	bool _isRed;
	std::string _filename;
	OutputPtr _output;
	RootFactoryPtr _rootFactory;
	std::map<std::string, DialogPtr> _dialogs;
	std::map<std::string, ButtonListPtr> _buttonLists;
	DialogPtr _rootDialog;
};
