#include "Factories/TestRoadFactory.hpp"
#include "ParagraphStateMachine.hpp"
#include "SimpleRoom.hpp"
#include "TextParagraph.hpp"
#include "ParagraphChanging.hpp"
#include "AutoActionSwitcher.hpp"
#include "ActionGroup.hpp"
#include "GiftReceiving.hpp"

using namespace QuestCore;

TestRoadFactory::TestRoadFactory(const std::shared_ptr<IInventory>& playerInventory):
	_playerInventory(playerInventory)
{
}

std::shared_ptr<IRoom> TestRoadFactory::GetRoom()
{
    auto paragraphSatateMachine = std::make_shared<ParagraphStateMachine>();
    auto road = std::make_shared<SimpleRoom>("������", paragraphSatateMachine);

    auto roadParagraph = std::make_shared<TextParagraph>("����� ���� ������.");
    paragraphSatateMachine->SetState(roadParagraph);

    auto exploreParagraph = std::make_shared<TextParagraph>("�� ������ ����� ����� ������, � �� ������ �������.");
    auto explore = std::make_shared<ParagraphChanging>("�����������", paragraphSatateMachine, exploreParagraph);

    auto backToRoad = std::make_shared<ParagraphChanging>("��������� �����", paragraphSatateMachine, roadParagraph);
    exploreParagraph->GetActionContainer().AddAction(backToRoad);

    roadParagraph->GetActionContainer().AddAction(explore);

    auto switcher = std::make_shared<AutoActionSwitcher>();

    auto talkingTrump = std::make_shared<TextParagraph>("���������� ����������, �� ��� �� �� ������ ��� 50 ����� � ��������.");
    auto emptyTrump = std::make_shared<TextParagraph>("���������� ��� ��� ����������, � ���� ��� ��� �����.");

    auto talk = std::make_shared<ParagraphChanging>("���������� � ��������", paragraphSatateMachine, talkingTrump);
    auto emptyTalk = std::make_shared<ParagraphChanging>("���������� � ��������", paragraphSatateMachine, emptyTrump);

    switcher->AddAction(talk);
    switcher->Switch(talk);
    switcher->AddAction(emptyTalk);
    switcher->SetFinalAction(emptyTalk);

    roadParagraph->GetActionContainer().AddAction(switcher);

    emptyTrump->GetActionContainer().AddAction(backToRoad);

    auto group = std::make_shared<ActionGroup>();
    talkingTrump->GetActionContainer().AddAction(group);
    group->AddAction(backToRoad);

    auto gift = std::make_shared<GiftReceiving>("������� �������");
    gift->SetMoney(50);
    gift->SetThings({ "��������" });

    group->AddAction(gift);
    gift->SetTargetInventory(_playerInventory);

    return road;
}
