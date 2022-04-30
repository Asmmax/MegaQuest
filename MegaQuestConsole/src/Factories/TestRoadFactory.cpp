#include "Factories/TestRoadFactory.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"
#include "SimpleRoom.hpp"
#include "Paragraphs/TextParagraph.hpp"
#include "Actions/ParagraphChanging.hpp"
#include "Actions/ActionGroup.hpp"
#include "Actions/GiftReceiving.hpp"
#include "Item.hpp"
#include "Forms.hpp"

using namespace QuestCore;

std::shared_ptr<IRoom> TestRoadFactory::GetRoom()
{
    std::vector<std::string> hotKeys;
    std::map<std::string, std::shared_ptr<IParagraph>> inputs;
    std::map<std::string, std::shared_ptr<Item>> items;
    std::map<std::string, std::shared_ptr<Inventory>> inventories;
    auto paragraphSatateMachine = std::make_shared<ParagraphStateMachine>();
    inputs.emplace("root", paragraphSatateMachine);
    return std::make_shared<SimpleRoom>(inputs, hotKeys, items, inventories);

    /*
    auto paragraphSatateMachine = std::make_shared<ParagraphStateMachine>();
    auto road = std::make_shared<SimpleRoom>(TextString::FromUtf8(u8"Дорога"), paragraphSatateMachine);

    auto roadParagraph = std::make_shared<TextParagraph>(TextString::FromUtf8(u8"Перед вами дорога."));
    paragraphSatateMachine->SetState(roadParagraph);

    auto exploreParagraph = std::make_shared<TextParagraph>(TextString::FromUtf8(u8"Вы видите перед собой дорогу, а на дороге путника."));
    auto explore = std::make_shared<ParagraphChanging>(TextString::FromUtf8(u8"Осмотреться"), paragraphSatateMachine, exploreParagraph);

    auto backToRoad = std::make_shared<ParagraphChanging>(TextString::FromUtf8(u8"Вернуться назад"), paragraphSatateMachine, roadParagraph);
    exploreParagraph->GetActionContainer().AddAction(backToRoad);

    roadParagraph->GetActionContainer().AddAction(explore);

    auto switcher = std::make_shared<AutoActionSwitcher>();

    auto talkingTrump = std::make_shared<TextParagraph>(TextString::FromUtf8(u8"Здравствуй незнакомец, на вот те за просто так 50 монет и медальон."));
    auto emptyTrump = std::make_shared<TextParagraph>(TextString::FromUtf8(u8"Здравствуй еще раз незнакомец, я тебе уже все отдал."));

    auto talk = std::make_shared<ParagraphChanging>(TextString::FromUtf8(u8"Поговорить с бродягой"), paragraphSatateMachine, talkingTrump);
    auto emptyTalk = std::make_shared<ParagraphChanging>(TextString::FromUtf8(u8"Поговорить с бродягой"), paragraphSatateMachine, emptyTrump);

    switcher->AddAction(talk);
    switcher->Switch(talk);
    switcher->AddAction(emptyTalk);
    switcher->SetFinalAction(emptyTalk);

    roadParagraph->GetActionContainer().AddAction(switcher);

    emptyTrump->GetActionContainer().AddAction(backToRoad);

    auto group = std::make_shared<ActionGroup>(TextString::FromUtf8(u8" и "));
    talkingTrump->GetActionContainer().AddAction(group);
    group->AddAction(backToRoad);

    auto gift = std::make_shared<GiftReceiving>(TextString::FromUtf8(u8"Забрать подарок"), _playerInventory);
    auto coin = std::make_shared<ItemInfo>(true);
    auto medalion = std::make_shared<ItemInfo>();
    gift->AddThings(coin, 50);
    gift->AddThings(medalion, 1);

    auto coinForm1 = std::make_shared<SpecificForm>(std::vector<int>{ 11,12,13,14 }, TextString::FromUtf8(u8"монет"));
    auto coinForm2 = std::make_shared<TailForm>(10, std::vector<int>{ 1 }, TextString::FromUtf8(u8"монета"));
    auto coinForm3 = std::make_shared<TailForm>(10, std::vector<int>{ 2,3,4 }, TextString::FromUtf8(u8"монеты"));
    auto coinForm4 = std::make_shared<TailForm>(10, std::vector<int>{ 0,5,6,7,8,9 }, TextString::FromUtf8(u8"монет"));

    coin->AddForm(coinForm1);
    coin->AddForm(coinForm2);
    coin->AddForm(coinForm3);
    coin->AddForm(coinForm4);

    auto medalionForm1 = std::make_shared<SpecificForm>(std::vector<int>{ 11, 12, 13, 14 }, TextString::FromUtf8(u8"медальонов"));
    auto medalionForm2 = std::make_shared<TailForm>(10, std::vector<int>{ 1 }, TextString::FromUtf8(u8"медальон"));
    auto medalionForm3 = std::make_shared<TailForm>(10, std::vector<int>{ 2, 3, 4 }, TextString::FromUtf8(u8"медальона"));
    auto medalionForm4 = std::make_shared<TailForm>(10, std::vector<int>{ 0, 5, 6, 7, 8, 9 }, TextString::FromUtf8(u8"медальонов"));

    medalion->AddForm(medalionForm1);
    medalion->AddForm(medalionForm2);
    medalion->AddForm(medalionForm3);
    medalion->AddForm(medalionForm4);

    group->AddAction(gift);

    return road;
    */
}
