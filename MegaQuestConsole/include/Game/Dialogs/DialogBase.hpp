#pragma once
#include "TextString.hpp"
#include "Game/IDialog.hpp"
#include <vector>

namespace Game
{
	class Model;

	/// @serializable @abstract
	class DialogBase : public IDialog
	{
	protected:
		using ButtonListPtr = std::shared_ptr<IButtonList>;
		using ModelPtr = std::shared_ptr<Model>;
	public:
		using Ptr = std::shared_ptr<DialogBase>;

		DialogBase(const QuestCore::TextString& intro, const std::vector<ButtonListPtr> buttonGroups);

		/// @inject
		void SetModel(const ModelPtr& model);

		virtual void Init(IOutput& output) override;
		virtual void Update() override;
		virtual void Draw(IOutput& output) override;
		void AddButtonList(const ButtonListPtr& buttonList);

	protected:
		const ModelPtr& GetModel();

	private:
		ModelPtr _model;
		QuestCore::TextString _intro;
		std::vector<ButtonListPtr> _buttonGroups;
	};
}
