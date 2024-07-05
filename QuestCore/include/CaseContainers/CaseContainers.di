bind "CaseContainers/CaseContainerGroup.hpp";
bind "CaseContainers/CaseContainerStateMachine.hpp";
bind "CaseContainers/ConditionalCaseContainer.hpp";
bind "CaseContainers/SimpleCaseContainer.hpp";

shared QuestCore::CaseContainerGroup : QuestCore::ICaseContainer
{
	CaseContainerGroup(vector<QuestCore::ICaseContainer> children);
};

shared QuestCore::CaseContainerStateMachine : QuestCore::ICaseContainer
{
	CaseContainerStateMachine(QuestCore::Quest quest);
	InitState(QuestCore::ICaseContainer state);
};

shared QuestCore::ConditionalCaseContainer : QuestCore::ICaseContainer
{
	ConditionalCaseContainer(QuestCore::ICaseContainer thenContainer, QuestCore::ICaseContainer elseContainer, vector<QuestCore::ICondition> conditions);
};

shared QuestCore::SimpleCaseContainer : QuestCore::ICaseContainer
{
	SimpleCaseContainer(vector<QuestCore::Case> cases);
};
