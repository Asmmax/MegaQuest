bind "Paragraphs/ConditionalParagraph.hpp";
bind "Paragraphs/InventoryParagraph.hpp";
bind "Paragraphs/ParagraphGroup.hpp";
bind "Paragraphs/ParagraphStateMachine.hpp";
bind "Paragraphs/TextParagraph.hpp";

shared QuestCore::ConditionalParagraph : QuestCore::IParagraph
{
	ConditionalParagraph(QuestCore::IParagraph thenParagraph, QuestCore::IParagraph elseParagraph, vector<QuestCore::ICondition> conditions);
};

value QuestCore::ItemOrder
{
	QuestCore::Item item;
	int order;
};

shared QuestCore::InventoryParagraph : QuestCore::IParagraph
{
	InventoryParagraph(QuestCore::FormatedString prefix, QuestCore::TextString gap, QuestCore::FormatedString postfix, QuestCore::Inventory inventory, vector<QuestCore::ItemOrder> itemOrders);
};

shared QuestCore::ParagraphGroup : QuestCore::IParagraph
{
	ParagraphGroup(vector<QuestCore::IParagraph> children, QuestCore::TextString gap);
};

shared QuestCore::ParagraphStateMachine : QuestCore::IParagraph
{
	ParagraphStateMachine(QuestCore::Quest quest);
	InitState(QuestCore::IParagraph state);
};

shared QuestCore::TextParagraph : QuestCore::IParagraph
{
	TextParagraph(QuestCore::TextString text);
};
