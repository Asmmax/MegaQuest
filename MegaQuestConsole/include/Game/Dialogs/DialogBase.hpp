#pragma once
#include "TextString.hpp"
#include "Game/IDialog.hpp"
#include <vector>

namespace Game
{
	class Model;

	class DialogBase : public IDialog
	{
	public:
		DialogBase(const QuestCore::TextString& intro, const std::vector<IButtonList*> buttonGroups);

		void SetModel(Model* model);

		virtual void Init(IOutput& output) override;
		virtual void Update() override;
		virtual void Draw(IOutput& output) override;
		void AddButtonList(IButtonList* buttonList);

	protected:
		Model* GetModel();

	private:
		Model* _model;
		QuestCore::TextString _intro;
		std::vector<IButtonList*> _buttonGroups;
	};
}
