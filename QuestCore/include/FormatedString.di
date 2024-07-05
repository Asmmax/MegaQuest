bind "FormBase.hpp";
bind "FormatedString.hpp";

single QuestCore::FormBase
{
	FormBase(QuestCore::TextString text);
};

value QuestCore::FormatedString
{
	FormatedString(vector<QuestCore::FormBase> forms);
};
