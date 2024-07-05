bind "Conditions/Comparison.hpp";

enum QuestCore::Operation
{
	None, 
	Less, 
	Greater, 
	Equal, 
	NotLess, 
	NotGreater, 
	NotEqual
};

single QuestCore::Comparison : QuestCore::ICondition
{
	Comparison(QuestCore::Value left, QuestCore::Value right, QuestCore::Operation op);
};
