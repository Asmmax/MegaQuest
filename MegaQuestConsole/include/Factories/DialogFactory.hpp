#pragma once
#include "json.hpp"
#include <memory>

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
	using ModelPtr = std::shared_ptr<Game::Model>;

public:
	DialogFactory(const std::string& filename);
	ModelPtr GetModel();
	DialogPtr GetDialog(const std::string& id);
	ButtonListPtr GetButtonList(const std::string& id);

private:
	bool Read();

private:
	bool _isRed;
	std::string _filename;
};
