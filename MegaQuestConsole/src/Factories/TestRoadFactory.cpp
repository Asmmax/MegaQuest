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
    auto road = std::make_shared<SimpleRoom>("Дорога", paragraphSatateMachine);

    auto roadParagraph = std::make_shared<TextParagraph>("Перед вами дорога.");
    paragraphSatateMachine->SetState(roadParagraph);

    auto exploreParagraph = std::make_shared<TextParagraph>("Вы видите перед собой дорогу, а на дороге путника.");
    auto explore = std::make_shared<ParagraphChanging>("Осмотреться", paragraphSatateMachine, exploreParagraph);

    auto backToRoad = std::make_shared<ParagraphChanging>("Вернуться назад", paragraphSatateMachine, roadParagraph);
    exploreParagraph->GetActionContainer().AddAction(backToRoad);

    roadParagraph->GetActionContainer().AddAction(explore);

    auto switcher = std::make_shared<AutoActionSwitcher>();

    auto talkingTrump = std::make_shared<TextParagraph>("Здравствуй незнакомец, на вот те за просто так 50 монет и медальон.");
    auto emptyTrump = std::make_shared<TextParagraph>("Здравствуй еще раз незнакомец, я тебе уже все отдал.");

    auto talk = std::make_shared<ParagraphChanging>("Поговорить с бродягой", paragraphSatateMachine, talkingTrump);
    auto emptyTalk = std::make_shared<ParagraphChanging>("Поговорить с бродягой", paragraphSatateMachine, emptyTrump);

    switcher->AddAction(talk);
    switcher->Switch(talk);
    switcher->AddAction(emptyTalk);
    switcher->SetFinalAction(emptyTalk);

    roadParagraph->GetActionContainer().AddAction(switcher);

    emptyTrump->GetActionContainer().AddAction(backToRoad);

    auto group = std::make_shared<ActionGroup>();
    talkingTrump->GetActionContainer().AddAction(group);
    group->AddAction(backToRoad);

    auto gift = std::make_shared<GiftReceiving>("Забрать подарок", _playerInventory);
    auto coin = std::make_shared<ItemInfo>(true);
    auto medalion = std::make_shared<ItemInfo>();
    gift->AddThings(coin, 50);
    gift->AddThings(medalion, 1);

    auto coinForm1 = std::make_shared<SpecificForm>(11, "монет");
    auto coinForm2 = std::make_shared<SpecificForm>(12, "монет");
    auto coinForm3 = std::make_shared<SpecificForm>(13, "монет");
    auto coinForm4 = std::make_shared<SpecificForm>(14, "монет");
    auto coinForm5 = std::make_shared<TailForm>(10, 0, "монет");
    auto coinForm6 = std::make_shared<TailForm>(10, 1, "монета");
    auto coinForm7 = std::make_shared<TailForm>(10, 2, "монеты");
    auto coinForm8 = std::make_shared<TailForm>(10, 3, "монеты");
    auto coinForm9 = std::make_shared<TailForm>(10, 4, "монеты");
    auto coinForm10 = std::make_shared<TailForm>(10, 5, "монет");
    auto coinForm11 = std::make_shared<TailForm>(10, 6, "монет");
    auto coinForm12 = std::make_shared<TailForm>(10, 7, "монет");
    auto coinForm13 = std::make_shared<TailForm>(10, 8, "монет");
    auto coinForm14 = std::make_shared<TailForm>(10, 9, "монет");

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

    auto medalionForm1 = std::make_shared<SpecificForm>(11, "медальонов");
    auto medalionForm2 = std::make_shared<SpecificForm>(12, "медальонов");
    auto medalionForm3 = std::make_shared<SpecificForm>(13, "медальонов");
    auto medalionForm4 = std::make_shared<SpecificForm>(14, "медальонов");
    auto medalionForm5 = std::make_shared<TailForm>(10, 0, "медальонов");
    auto medalionForm6 = std::make_shared<TailForm>(10, 1, "медальон");
    auto medalionForm7 = std::make_shared<TailForm>(10, 2, "медальона");
    auto medalionForm8 = std::make_shared<TailForm>(10, 3, "медальона");
    auto medalionForm9 = std::make_shared<TailForm>(10, 4, "медальона");
    auto medalionForm10 = std::make_shared<TailForm>(10, 5, "медальонов");
    auto medalionForm11 = std::make_shared<TailForm>(10, 6, "медальонов");
    auto medalionForm12 = std::make_shared<TailForm>(10, 7, "медальонов");
    auto medalionForm13 = std::make_shared<TailForm>(10, 8, "медальонов");
    auto medalionForm14 = std::make_shared<TailForm>(10, 9, "медальонов");

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
