#pragma once
#include <memory>

namespace QuestCore 
{
	class IQuest;
}

namespace Game
{
	class IDialog;
	class IOutput;

	/// @serializable @shared models
	class Model 
	{
		using DialogPtr = std::shared_ptr<IDialog>;
		using OutputPtr = std::shared_ptr<IOutput>;
		using QuestPtr = std::shared_ptr<QuestCore::IQuest>;
	public:
		using Ptr = std::shared_ptr<Model>;
		using WeakPtr = std::weak_ptr<Model>;

		Model(const DialogPtr& rootDialog, const QuestPtr& quest);

		/// @inject
		void SetOutput(const OutputPtr& output);
		void Init();
		void Update();
	
	private:
		DialogPtr _rootDialog;
		QuestPtr _quest;
		OutputPtr _output;
	};
}
