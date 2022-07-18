#pragma once
#include "json.hpp"
#include "TextString.hpp"
#include <vector>
#include <memory>

class IRootFactory;

namespace Game 
{
	class IDialog;
	class IButtonList;
	class Model;
}

class DialogFactory
{
	using DialogPtr = std::shared_ptr<Game::IDialog>;
	using ButtonListPtr = std::shared_ptr<Game::IButtonList>;
	using RootFactoryPtr = std::shared_ptr<IRootFactory>;
	using ModelPtr = std::shared_ptr<Game::Model>;

public:
	DialogFactory(const std::string& filename, const RootFactoryPtr& rootFactory);
	ModelPtr GetModel();
	DialogPtr GetDialog(const std::string& id);
	ButtonListPtr GetButtonList(const std::string& id);

private:
	void Read();
	void CreateDialogs(const nlohmann::json& dialogsNode);
	DialogPtr CreateDialog(const nlohmann::json& dialogNode);
	void ReadDialogs(const nlohmann::json& dialogsNode);
	void InitDialog(const DialogPtr& dialog, const nlohmann::json& dialogNode);
	void ReadRootDialog(const nlohmann::json& rootNode);
	void CreateButtonLists(const nlohmann::json& buttonListsNode);
	ButtonListPtr CreateButtonList(const nlohmann::json& buttonListNode);
	void ReadButtonLists(const nlohmann::json& buttonListsNode);
	void InitButtonList(const ButtonListPtr& buttonList, const nlohmann::json& buttonListNode);

	std::vector<ButtonListPtr> ReadButtonGroups(const nlohmann::json& buttonGroupsNode);

private:
	bool _isRed;
	std::string _filename;
	RootFactoryPtr _rootFactory;
	std::map<std::string, DialogPtr> _dialogs;
	std::map<std::string, ButtonListPtr> _buttonLists;
	ModelPtr _model;
};
