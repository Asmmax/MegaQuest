#include "Factories/TestRoadFactory.hpp"
#include "ParagraphStateMachine.hpp"
#include "SimpleRoom.hpp"
#include "TextParagraph.hpp"
#include "ParagraphChanging.hpp"
#include "AutoActionSwitcher.hpp"
#include "ActionGroup.hpp"
#include "GiftReceiving.hpp"
#include "ItemInfo.hpp"
#include "Forms.hpp"

using namespace QuestCore;

TestRoadFactory::TestRoadFactory(const std::shared_ptr<Inventory>& playerInventory):
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

    auto gift = std::make_shared<GiftReceiving>("������� �������", _playerInventory);
    auto coin = std::make_shared<ItemInfo>(true);
    auto medalion = std::make_shared<ItemInfo>();
    gift->AddThings(coin, 50);
    gift->AddThings(medalion, 1);

    auto coinForm1 = std::make_shared<SpecificForm>(11, "�����");
    auto coinForm2 = std::make_shared<SpecificForm>(12, "�����");
    auto coinForm3 = std::make_shared<SpecificForm>(13, "�����");
    auto coinForm4 = std::make_shared<SpecificForm>(14, "�����");
    auto coinForm5 = std::make_shared<TailForm>(10, 0, "�����");
    auto coinForm6 = std::make_shared<TailForm>(10, 1, "������");
    auto coinForm7 = std::make_shared<TailForm>(10, 2, "������");
    auto coinForm8 = std::make_shared<TailForm>(10, 3, "������");
    auto coinForm9 = std::make_shared<TailForm>(10, 4, "������");
    auto coinForm10 = std::make_shared<TailForm>(10, 5, "�����");
    auto coinForm11 = std::make_shared<TailForm>(10, 6, "�����");
    auto coinForm12 = std::make_shared<TailForm>(10, 7, "�����");
    auto coinForm13 = std::make_shared<TailForm>(10, 8, "�����");
    auto coinForm14 = std::make_shared<TailForm>(10, 9, "�����");

    coin->AddForm(coinForm1);
    coin->AddForm(coinForm2);
    coin->AddForm(coinForm3);
    coin->AddForm(coinForm4);
    coin->AddForm(coinForm5);
    coin->AddForm(coinForm6);
    coin->AddForm(coinForm7);
    coin->AddForm(coinForm8);
    coin->AddForm(coinForm9);
    coin->AddForm(coinForm10);
    coin->AddForm(coinForm11);
    coin->AddForm(coinForm12);
    coin->AddForm(coinForm13);
    coin->AddForm(coinForm14);

    auto medalionForm1 = std::make_shared<SpecificForm>(11, "����������");
    auto medalionForm2 = std::make_shared<SpecificForm>(12, "����������");
    auto medalionForm3 = std::make_shared<SpecificForm>(13, "����������");
    auto medalionForm4 = std::make_shared<SpecificForm>(14, "����������");
    auto medalionForm5 = std::make_shared<TailForm>(10, 0, "����������");
    auto medalionForm6 = std::make_shared<TailForm>(10, 1, "��������");
    auto medalionForm7 = std::make_shared<TailForm>(10, 2, "���������");
    auto medalionForm8 = std::make_shared<TailForm>(10, 3, "���������");
    auto medalionForm9 = std::make_shared<TailForm>(10, 4, "���������");
    auto medalionForm10 = std::make_shared<TailForm>(10, 5, "����������");
    auto medalionForm11 = std::make_shared<TailForm>(10, 6, "����������");
    auto medalionForm12 = std::make_shared<TailForm>(10, 7, "����������");
    auto medalionForm13 = std::make_shared<TailForm>(10, 8, "����������");
    auto medalionForm14 = std::make_shared<TailForm>(10, 9, "����������");

    medalion->AddForm(medalionForm1);
    medalion->AddForm(medalionForm2);
    medalion->AddForm(medalionForm3);
    medalion->AddForm(medalionForm4);
    medalion->AddForm(medalionForm5);
    medalion->AddForm(medalionForm6);
    medalion->AddForm(medalionForm7);
    medalion->AddForm(medalionForm8);
    medalion->AddForm(medalionForm9);
    medalion->AddForm(medalionForm10);
    medalion->AddForm(medalionForm11);
    medalion->AddForm(medalionForm12);
    medalion->AddForm(medalionForm13);
    medalion->AddForm(medalionForm14);

    group->AddAction(gift);

    return road;
}
