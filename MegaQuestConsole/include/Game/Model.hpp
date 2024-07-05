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

	class Model 
	{
	public:
		Model(IDialog* rootDialog, QuestCore::IQuest* quest);

		void SetOutput(IOutput* output);
		void Reset();
		void Init();
		void Update();
	
	private:
		IDialog* _rootDialog;
		QuestCore::IQuest* _quest;
		IOutput* _output;
	};
}
