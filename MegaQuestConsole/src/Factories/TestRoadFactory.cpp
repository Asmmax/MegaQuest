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
    auto road = std::make_shared<SimpleRoom>("Дорога", paragraphSatateMachine);

    auto roadParagraph = std::make_shared<TextParagraph>("Перед вами дорога.");
    paragraphSatateMachine->SetState(roadParagraph);

    auto exploreParagraph = std::make_shared<TextParagraph>("Вы видите перед собой дорогу, а на дороге путника.");
    auto explore = std::make_shared<ParagraphChanging>("Осмотреться", paragraphSatateMachine, exploreParagraph);

    auto backToRoad = std::make_shared<ParagraphChanging>("Вернуться назад", paragraphSatateMachine, roadParagraph);
    exploreParagraph->AddAction(backToRoad);

    roadParagraph->AddAction(explore);

    auto switcher = std::make_shared<AutoActionSwitcher>();

    auto talkingTrump = std::make_shared<TextParagraph>("Здравствуй незнакомец, на вот те за просто так 50 монет и медальон.");
    auto emptyTrump = std::make_shared<TextParagraph>("Здравствуй еще раз незнакомец, я тебе уже все отдал.");

    auto talk = std::make_shared<ParagraphChanging>("Поговорить с бродягой", paragraphSatateMachine, talkingTrump);
    auto emptyTalk = std::make_shared<ParagraphChanging>("Поговорить с бродягой", paragraphSatateMachine, emptyTrump);

    switcher->AddAction(talk);
    switcher->Switch(switcher->GetLastActionId());
    switcher->AddAction(emptyTalk);
    switcher->SetFinalAction(switcher->GetLastActionId());

    roadParagraph->AddAction(switcher);

    emptyTrump->AddAction(backToRoad);

    auto group = std::make_shared<ActionGroup>();
    talkingTrump->AddAction(group);
    group->AddAction(backToRoad);

    auto gift = std::make_shared<GiftReceiving>("Забрать подарок");
    gift->SetMoney(50);
    gift->SetThings({ "медальон" });

    group->AddAction(gift);
    gift->SetTargetInventory(_playerInventory);

    return road;
}
