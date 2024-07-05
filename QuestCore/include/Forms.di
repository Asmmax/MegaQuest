bind "Forms.hpp";

single QuestCore::SpecificForm : QuestCore::FormBase
{
	SpecificForm(vector<int> counts, QuestCore::TextString text);
};

single QuestCore::TailForm : QuestCore::FormBase
{
	TailForm(int notation, vector<int> digits, QuestCore::TextString text);
};
