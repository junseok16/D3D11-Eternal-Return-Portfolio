#include "pch.h"
#include "ItemInfoPanel.h"

#include "ItemInfoBackground.h"
#include "ItemInfoImage.h"
#include "ItemInfoText.h"
#include "ItemInfoLevelImage.h"

#include "World.h"
#include "Level.h"

#include "Item.h"

HRESULT Client::CItemInfoPanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemInfoPanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemInfoPanel::PostInitialize()
{
	if (FAILED(CPanel::PostInitialize())) { return E_FAIL; }

	shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();

	// 패널 1개
	shared_ptr<CItemInfoBackground> spItemInfoBackground = spLevel->CreateUI<CItemInfoBackground>(L"ItemInfoBackground");
	spItemInfoBackground->SetPriority(10);
	AddUI(L"ItemInfoBackground", spItemInfoBackground);
	m_wpItemInfoBackground = spItemInfoBackground;

	// 아이템 이미지
	shared_ptr<CItemInfoImage> spItemInfoImage = spLevel->CreateUI<CItemInfoImage>(L"ItemInfoImage");
	spItemInfoImage->SetPriority(8);
	AddUI(L"ItemInfoImage", spItemInfoImage);
	m_wpItemInfoImage = spItemInfoImage;

	// 아이템 등급 이미지 배경
	shared_ptr<CItemInfoLevelImage> spItemInfoLevelBackgoundImage = spLevel->CreateUI<CItemInfoLevelImage>(L"ItemInfoLevelBackgoundImage");
	spItemInfoLevelBackgoundImage->SetPriority(9);
	spItemInfoLevelBackgoundImage->SetItemInfoLevelImageType(EItemInfoLevelImageType::BACKGROUND);
	AddUI(L"ItemInfoLevelBackgoundImage", spItemInfoLevelBackgoundImage);
	m_wpItemInfoLevelBackgoundImage = spItemInfoLevelBackgoundImage;

	// 아이템 등급 이미지 띠
	// shared_ptr<CItemInfoLevelImage> spItemInfoLevelLineImage = spLevel->CreateUI<CItemInfoLevelImage>(L"ItemInfoLevelLineImage");
	// spItemInfoLevelLineImage->SetPriority(9);
	// spItemInfoLevelLineImage->SetItemInfoLevelImageType(EItemInfoLevelImageType::LINE);
	// AddUI(L"ItemInfoLevelLineImage", spItemInfoLevelLineImage);
	// m_wpItemInfoLevelLineImage = spItemInfoLevelLineImage;

	// 아이템 이름
	shared_ptr<CItemInfoText> spItemNameText = spLevel->CreateUI<CItemInfoText>(L"ItemNameText");
	spItemNameText->SetItemInfoType(EItemInfoType::NAME);
	spItemNameText->SetFontName(L"KBIZM");
	spItemNameText->SetPriority(5);
	AddUI(L"ItemNameText", spItemNameText);
	m_wpItemInfoText[0] = spItemNameText;

	// 아이템 등급
	shared_ptr<CItemInfoText> spItemLevelText = spLevel->CreateUI<CItemInfoText>(L"ItemLevelText");
	spItemLevelText->SetItemInfoType(EItemInfoType::LEVEL);
	spItemLevelText->SetFontName(L"KBIZM");
	spItemLevelText->SetPriority(5);
	AddUI(L"ItemLevelText", spItemLevelText);
	m_wpItemInfoText[1] = spItemLevelText;

	// 아이템 카테고리
	shared_ptr<CItemInfoText> spItemCategoryText = spLevel->CreateUI<CItemInfoText>(L"ItemCategoryText");
	spItemCategoryText->SetItemInfoType(EItemInfoType::CATEGORY);
	spItemCategoryText->SetFontName(L"KBIZM");
	spItemCategoryText->SetPriority(5);
	AddUI(L"ItemCategoryText", spItemCategoryText);
	m_wpItemInfoText[2] = spItemCategoryText;

	// 아이템 효과
	shared_ptr<CItemInfoText> spItemEffectText = spLevel->CreateUI<CItemInfoText>(L"ItemEffectText");
	spItemEffectText->SetItemInfoType(EItemInfoType::EFFECT);
	spItemEffectText->SetFontName(L"KBIZM");
	spItemEffectText->SetPriority(5);
	AddUI(L"ItemEffectText", spItemEffectText);
	m_wpItemInfoText[3] = spItemEffectText;

	// 아이템 설명
	shared_ptr<CItemInfoText> spItemExplainText = spLevel->CreateUI<CItemInfoText>(L"ItemExplainText");
	spItemExplainText->SetItemInfoType(EItemInfoType::EXPLANATION);
	spItemExplainText->SetFontName(L"KBIZM");
	spItemExplainText->SetPriority(5);
	AddUI(L"ItemExplainText", spItemExplainText);
	m_wpItemInfoText[4] = spItemExplainText;

	return S_OK;
}

HRESULT Client::CItemInfoPanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CItemInfoPanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	if (m_wpItem.expired()) { SetActive(false); }
	else { SetActive(true); }

	return 0;
}

int32 Client::CItemInfoPanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoPanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemInfoPanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemInfoPanel::Render()
{
	CPanel::Render();
}

void Client::CItemInfoPanel::Release()
{
	CPanel::Release();
}

void Client::CItemInfoPanel::RegisterItem(const shared_ptr<CItem>& _spItem, EItemSlotType _eItemSlotType)
{
	m_wpItem = _spItem;
	m_eItemRegister = _eItemSlotType;

	CheckItemInfo(_spItem);
}

void Client::CItemInfoPanel::UnregisterItem(EItemSlotType _eItemSlotType)
{
	if (m_wpItem.expired()) { return; }

	if (m_eItemRegister != _eItemSlotType) { return; }

	m_wpItem.reset();
}

void Client::CItemInfoPanel::CheckItemInfo(const shared_ptr<CItem>& _spItem)
{
	{
		EItemType eItemType = _spItem->GetItemType();
		wstring wstrItemName = L"";
		wstring wstrItemEffect = L"";
		wstring wstrItemExplanation = L"";

		switch (eItemType)
		{
		case Client::EItemType::BRANCH:					wstrItemName = L"나뭇가지";			break;
		case Client::EItemType::STONE:					wstrItemName = L"돌멩이";			break;
		case Client::EItemType::LEATHER:				wstrItemName = L"가죽";				break;
		case Client::EItemType::SCISSORS:				wstrItemName = L"가위";				break;
		case Client::EItemType::FOUNTAIN_PEN:			wstrItemName = L"만년필";			break;
		case Client::EItemType::PICKAXE:				wstrItemName = L"곡괭이";			break;
		case Client::EItemType::IRON_BALL:				wstrItemName = L"쇠구슬";			break;
		case Client::EItemType::GLASS_BOTTLE:			wstrItemName = L"유리병";			break;
		case Client::EItemType::PLAYING_CARDS:			wstrItemName = L"트럼프 카드";		break;
		case Client::EItemType::CHALK:					wstrItemName = L"분필";				break;
		case Client::EItemType::FEATHER:				wstrItemName = L"깃털";				break;
		case Client::EItemType::FLOWER:					wstrItemName = L"꽃";				break;
		case Client::EItemType::RIBBON:					wstrItemName = L"리본";				break;
		case Client::EItemType::BUDDHIST_SCRIPTURE:		wstrItemName = L"불경";				break;
		case Client::EItemType::HOLY_GRAIL:				wstrItemName = L"성배";				break;
		case Client::EItemType::CROSS:					wstrItemName = L"십자가";			break;
		case Client::EItemType::BINOCULARS:				wstrItemName = L"쌍안경";			break;
		case Client::EItemType::NAIL:					wstrItemName = L"못";				break;
		case Client::EItemType::TURTLE_SHELL:			wstrItemName = L"거북이 등딱지";	break;
		case Client::EItemType::RUBBER:					wstrItemName = L"고무";				break;
		case Client::EItemType::SCRAP_METAL:			wstrItemName = L"고철";				break;
		case Client::EItemType::LIGHTER:				wstrItemName = L"라이터";			break;
		case Client::EItemType::LASER_POINTER:			wstrItemName = L"레이저포인터";		break;
		case Client::EItemType::STALLION_MEDAL:			wstrItemName = L"마패";				break;
		case Client::EItemType::BATTERY:				wstrItemName = L"배터리";			break;
		case Client::EItemType::OIL:					wstrItemName = L"기름";				break;
		case Client::EItemType::CLOTH:					wstrItemName = L"옷감";				break;
		case Client::EItemType::GEMSTONE:				wstrItemName = L"원석";				break;
		case Client::EItemType::GLUE:					wstrItemName = L"풀";				break;
		case Client::EItemType::PAPER:					wstrItemName = L"종이";				break;
		case Client::EItemType::GUNPOWDER:				wstrItemName = L"화약";				break;
		case Client::EItemType::PIANO_WIRE:				wstrItemName = L"피아노 선";		break;

		case Client::EItemType::COTTON_GLOVE:			wstrItemName = L"목장갑";			wstrItemEffect = L"공격력 +3";	break;
		case Client::EItemType::BAMBOO:					wstrItemName = L"대나무";			wstrItemEffect = L"공격력 +3";	break;
		case Client::EItemType::RUSTY_SWORD:			wstrItemName = L"녹슨 검";			wstrItemEffect = L"공격력 +3";	break;
		case Client::EItemType::WALTHER_PPK:			wstrItemName = L"발터 PPK";			wstrItemEffect = L"공격력 +3";	break;
		case Client::EItemType::HAMMER:					wstrItemName = L"망치";				wstrItemEffect = L"공격력 +3";	break;

		case Client::EItemType::WINDBREAKER:			wstrItemName = L"바람막이";			wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::MONKS_ROBE:				wstrItemName = L"승복";				wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::WETSUIT:				wstrItemName = L"전신 수영복";		wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::FABRIC_ARMOR:			wstrItemName = L"천 갑옷";			wstrItemEffect = L"방어력 +3";	break;

		case Client::EItemType::HAIR_BAND:				wstrItemName = L"머리띠";			wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::HAT:					wstrItemName = L"모자";				wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::BIKE_HELMET:			wstrItemName = L"자전거 헬맷";		wstrItemEffect = L"방어력 +3";	break;

		case Client::EItemType::WATCH:					wstrItemName = L"손목시계";			wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::BANDAGE:				wstrItemName = L"붕대";				wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::BRACELET:				wstrItemName = L"팔찌";				wstrItemEffect = L"방어력 +3";	break;

		case Client::EItemType::SLIPPER:				wstrItemName = L"슬리퍼";			wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::RUNNING_SHOES:			wstrItemName = L"운동화";			wstrItemEffect = L"방어력 +3";	break;
		case Client::EItemType::TIGHTS:					wstrItemName = L"타이즈";			wstrItemEffect = L"방어력 +3";	break;

		case Client::EItemType::FLOWER_OF_FATE:			wstrItemName = L"운명의 꽃";		break;
		case Client::EItemType::GLASS_PIECES:			wstrItemName = L"유리 조각";		break;
		case Client::EItemType::SNIPER_SCOPE:			wstrItemName = L"저격 스코프";		break;
		case Client::EItemType::BUDDHA_SARIRA:			wstrItemName = L"진신사리";			break;
		case Client::EItemType::QUIVER:					wstrItemName = L"화살통";			break;
		case Client::EItemType::FEATHER_DUSTER:			wstrItemName = L"먼지털이개";		break;
		case Client::EItemType::SHAMANS_BRONZE:			wstrItemName = L"비파단도";			break;
		case Client::EItemType::MARKSMAN_HANDBOOK:		wstrItemName = L"사격교본";			break;
		case Client::EItemType::OIL_CLOTH:				wstrItemName = L"기름먹인 천";		break;
		case Client::EItemType::CHALK_POWDER:			wstrItemName = L"분필 가루";		break;
		case Client::EItemType::ASH:					wstrItemName = L"재";				break;
		case Client::EItemType::ELECTRONIC_PARTS:		wstrItemName = L"전자 부품";		break;
		case Client::EItemType::BLUEPRINT:				wstrItemName = L"정교한 도면";		break;
		case Client::EItemType::IRON_SHEET:				wstrItemName = L"철판";				break;
		case Client::EItemType::GOLD:					wstrItemName = L"금";				break;
		case Client::EItemType::HEATED_STONE:			wstrItemName = L"달궈진 돌멩이";	break;
		case Client::EItemType::BARBED_WIRE:			wstrItemName = L"철사";				break;
		case Client::EItemType::RUBY:					wstrItemName = L"루비";				break;
		case Client::EItemType::HARDCOVER:				wstrItemName = L"하드커버";			break;
		case Client::EItemType::ION_BATTERY:			wstrItemName = L"이온 전지";		break;

		case Client::EItemType::AETHER_FRINGE:			wstrItemName = L"에테르 깃털";		break;
		case Client::EItemType::MOTOR:					wstrItemName = L"모터";				break;
		case Client::EItemType::GLASS_PANEL:			wstrItemName = L"유리판";			break;

		case Client::EItemType::GLACIAL_ICE:			wstrItemName = L"만년빙";			break;
		case Client::EItemType::TRUE_SAMADHI_FIRE:		wstrItemName = L"삼매진화";			break;
		case Client::EItemType::TREE_OF_LIFE:			wstrItemName = L"생명의 나무";		break;
		case Client::EItemType::METEORITE:				wstrItemName = L"운석";				break;
		case Client::EItemType::MOONSTONE:				wstrItemName = L"문스톤";			break;
		case Client::EItemType::MYTHRIL:				wstrItemName = L"미스릴";			break;
		case Client::EItemType::VF_BLOOD_SAMPLE:		wstrItemName = L"VF 혈액 샘플";		break;
		case Client::EItemType::GEM_OF_EVOLUTION:		wstrItemName = L"진화의 돌";		break;
		case Client::EItemType::FORCE_CORE:				wstrItemName = L"포스 코어";		break;

		case Client::EItemType::MEAT:					wstrItemName = L"고기";				wstrItemEffect = L"체력 +300";		break;
		case Client::EItemType::BREAD:					wstrItemName = L"빵";				wstrItemEffect = L"체력 +300";		break;
		case Client::EItemType::RAMEN:					wstrItemName = L"생라면";			wstrItemEffect = L"체력 +300";		break;
		case Client::EItemType::CHOCOLATE:				wstrItemName = L"초콜릿";			wstrItemEffect = L"체력 +300";		break;
																							
		case Client::EItemType::HONEY:					wstrItemName = L"꿀";				wstrItemEffect = L"스태미나 +200";	break;
		case Client::EItemType::WATER:					wstrItemName = L"물";				wstrItemEffect = L"스태미나 +200";	break;
		case Client::EItemType::WHISKEY:				wstrItemName = L"위스키";			wstrItemEffect = L"스태미나 +200";	break;
		case Client::EItemType::CARBONATED_WATER:		wstrItemName = L"탄산수";			wstrItemEffect = L"스태미나 +200";	break;
																							
		case Client::EItemType::LEATHER_GLOVES:			wstrItemName = L"글러브";			wstrItemEffect = L"공격력 +6";		break;
		case Client::EItemType::IRON_KNUCKLES:			wstrItemName = L"아이언 너클";		wstrItemEffect = L"공격력 +6";		break;
																							
		case Client::EItemType::GAUNTLET:				wstrItemName = L"건틀릿";			wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::WING_KNUCKLES:			wstrItemName = L"윙 너클";			wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::BONE_GAUNTLET:			wstrItemName = L"귀골 장갑";		wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::SHATTER_SHELL_GAUNTLET:	wstrItemName = L"벽력귀투";			wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::PHOENIX_GLOVES:			wstrItemName = L"회단 장갑";		wstrItemEffect = L"공격력 +9";		break;

		case Client::EItemType::ONE_INCH_PUNCH:			wstrItemName = L"단영촌천투";		wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::DIVINE_FIST:			wstrItemName = L"디바인 피스트";	wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::BLOODWING_KNUCKLES:		wstrItemName = L"블러드윙 너클";	wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::FROST_PETAL_HAND:		wstrItemName = L"빙화현옥수";		wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::BUDDHAS_PALM:			wstrItemName = L"여래수투";			wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::BRASIL_GAUNTLET:		wstrItemName = L"브레이질 건틀릿";	wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::WHITE_CLAW_PUNCH:		wstrItemName = L"소수";				wstrItemEffect = L"공격력 +12";		break;

		case Client::EItemType::LONG_SWORD:				wstrItemName = L"장검";				wstrItemEffect = L"공격력 +6";		break;

		case Client::EItemType::KATANA:					wstrItemName = L"일본도";			wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::MURAMASA:				wstrItemName = L"무라마사";			wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::BASTARD_SWORD:			wstrItemName = L"바스타드 소드";	wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::JEWEL_SWORD:			wstrItemName = L"보검";				wstrItemEffect = L"공격력 +9";		break;

		case Client::EItemType::THUAN_THIEN:			wstrItemName = L"뚜언 띠엔";		wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::ARONDIGHT:				wstrItemName = L"아론다이트";		wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::EXCALIBUR:				wstrItemName = L"엑스칼리버";		wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::MONOHOSHIZAO:			wstrItemName = L"모노호시자오";		wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::HOVUD:					wstrItemName = L"호푸어드";			wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::ARCANE_EDGE:			wstrItemName = L"아케인 엣지";		wstrItemEffect = L"공격력 +12";		break;

		case Client::EItemType::MAGNUM_PYTHON:			wstrItemName = L"매그넘-파이선";	wstrItemEffect = L"공격력 +6";		break;
		case Client::EItemType::BERETTA_M92F:			wstrItemName = L"베레타 M92F";		wstrItemEffect = L"공격력 +6";		break;

		case Client::EItemType::FN57:					wstrItemName = L"FN57";				wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::MAGNUM_ANACONDA:		wstrItemName = L"매그넘-아나콘다";	wstrItemEffect = L"공격력 +9";		break;
		case Client::EItemType::DERRINGER:				wstrItemName = L"데린저";			wstrItemEffect = L"공격력 +9";		break;

		case Client::EItemType::ELEGANCE:				wstrItemName = L"엘레강스";			wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::ELECTRON_BLASTER:		wstrItemName = L"일렉트론 블라스터";wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::MAGNUM_BOA:				wstrItemName = L"매그넘-보아";		wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::GLOCK48:				wstrItemName = L"글록 48";			wstrItemEffect = L"공격력 +12";		break;
		case Client::EItemType::STAMPEDE:				wstrItemName = L"스탬피드";			wstrItemEffect = L"공격력 +12";		break;

		case Client::EItemType::LEATHER_ARMOR:			wstrItemName = L"가죽 갑옷";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::LEATHER_JACKET:			wstrItemName = L"가죽 자켓";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::MILITARY_SUIT:			wstrItemName = L"군복";				wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::PATCHED_ROBE:			wstrItemName = L"덧댄 로브";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::DRESS:					wstrItemName = L"드레스";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::BIKINI:					wstrItemName = L"비키니";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::DIVING_SUIT:			wstrItemName = L"잠수복";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::DEACON_ROBES:			wstrItemName = L"사제복";			wstrItemEffect = L"방어력 +3";		break;

		case Client::EItemType::RIDER_JACKET:			wstrItemName = L"라이더 자켓";		wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::CHAIN_ARMOR:			wstrItemName = L"사슬 갑옷";		wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::SUIT:					wstrItemName = L"정장";				wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::QIPAO:					wstrItemName = L"치파오";			wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::SHEET_METAL_ARMOR:		wstrItemName = L"판금갑옷";			wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::HANBOK:					wstrItemName = L"한복";				wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::BULLETPROOF_VEST:		wstrItemName = L"방탄조끼";			wstrItemEffect = L"방어력 +6";		break;

		case Client::EItemType::CARDINAL_ROBES:			wstrItemName = L"고위 사제복";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::SUNSET_ARMOR:			wstrItemName = L"석양의 갑옷";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::COVERT_AGENT_UNIFORM:	wstrItemName = L"어사의";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::OPTICAL_CAMOUFLAGE_SUIT:wstrItemName = L"광학미채 슈트";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::ROCKERS_JACKET:			wstrItemName = L"락커의 자켓";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::CRUSADER_ARMOR:			wstrItemName = L"성기사의 갑옷";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::AMAZONESS_ARMOR:		wstrItemName = L"아마조네스 아머";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::DRAGON_DOBOK:			wstrItemName = L"용의 도복";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::COMMANDERS_ARMOR:		wstrItemName = L"지휘관의 갑옷";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::BUTLERS_SUIT:			wstrItemName = L"집사복";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::BATTLE_SUIT:			wstrItemName = L"배틀 슈트";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::EOD_SUIT:				wstrItemName = L"EOD 슈트";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::TUXEDO:					wstrItemName = L"턱시도";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::HIGH_PRIEST_ROBES:		wstrItemName = L"제사장의 예복";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::CHANGPAO:				wstrItemName = L"창파오";			wstrItemEffect = L"방어력 +9";		break;

		case Client::EItemType::MASK:					wstrItemName = L"가면";				wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::CIRCLET:				wstrItemName = L"머리테";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::BERET:					wstrItemName = L"베레모";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::CHAIN_COIF:				wstrItemName = L"사슬 코이프";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::SAFETY_HELMET:			wstrItemName = L"안전모";			wstrItemEffect = L"방어력 +3";		break;

		case Client::EItemType::BALLISTIC_HELMET:		wstrItemName = L"방탄모";			wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::FIRE_HELMET:			wstrItemName = L"소방 헬멧";		wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::TIARA:					wstrItemName = L"티아라";			wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::CROWN:					wstrItemName = L"왕관";				wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::CLOSE_HELM:				wstrItemName = L"투구";				wstrItemEffect = L"방어력 +6";		break;

		case Client::EItemType::VIRTUOUS_OUTLAW:		wstrItemName = L"로빈";				wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::CRYSTAL_TIARA:			wstrItemName = L"수정 티아라";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::MOTORCYCLE_HELMET:		wstrItemName = L"오토바이 헬멧";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::TACTICAL_OPS_HELMET:	wstrItemName = L"전술 OPS 헬멧";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::HELM_OF_BANNERET:		wstrItemName = L"기사단장의 투구";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::IMPERIAL_CROWN:			wstrItemName = L"제국 왕관";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::IMPERIAL_BURGONET:		wstrItemName = L"황실 부르고넷";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::MOHAWK_HEADGEAR:		wstrItemName = L"모호크 헬멧";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::VIGILANTE:				wstrItemName = L"비질란테";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::DIADEM:					wstrItemName = L"다이아뎀";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::CRUSADER_HELMET:		wstrItemName = L"성기사의 투구";	wstrItemEffect = L"방어력 +9";		break;

		case Client::EItemType::LEATHER_SHIELD:			wstrItemName = L"가죽 방패";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::SQUARD_LEADER_ARMBAND:	wstrItemName = L"분대장 완장";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::BRACER:					wstrItemName = L"브레이서";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::BROKEN_WATCH:			wstrItemName = L"고장난 시계";		wstrItemEffect = L"방어력 +3";		break;

		case Client::EItemType::SHEATH:					wstrItemName = L"검집";				wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::GOLDEN_BRACELET:		wstrItemName = L"금팔찌";			wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::BAZUBAND:				wstrItemName = L"바주반드";			wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::CRIMSON_BRACELET:		wstrItemName = L"진홍 팔찌";		wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::BARBED_BLOSSOM:			wstrItemName = L"바브드 블로섬";	wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::STEEL_SHIELD:			wstrItemName = L"강철 방패";		wstrItemEffect = L"방어력 +6";		break;

		case Client::EItemType::CORRUPTING_TOUCH:		wstrItemName = L"포이즌드";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::SWORD_STOPPER:			wstrItemName = L"소드 스토퍼";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::DRAUPNIR:				wstrItemName = L"드라우프니르";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::VITAL_SIGH_SENSOR:		wstrItemName = L"바이탈 센서";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::CREED_OF_THE_KNIGHT:	wstrItemName = L"기사의 신조";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::SHEATH_OF_SHAH_JUHAN:	wstrItemName = L"샤자한의 검집";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::BURNISHED_AEGIS:		wstrItemName = L"아이기스";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::TINDALOS_BAND:			wstrItemName = L"틴달로스의 팔찌";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::NIGHTINGALE:			wstrItemName = L"나이팅게일";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::PLASMA_ARC:				wstrItemName = L"플라즈마 아크";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::SMART_BAND:				wstrItemName = L"스마트 밴드";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::SPORTS_WATCH:			wstrItemName = L"스포츠 시계";		wstrItemEffect = L"방어력 +9";		break;

		case Client::EItemType::KNEE_PADS:				wstrItemName = L"무릎 보호대";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::CHAIN_LEGGINGS:			wstrItemName = L"체인 레깅스";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::HIGH_HEELS:				wstrItemName = L"하이힐";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::HEELYS:					wstrItemName = L"힐리스";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::CLOGS:					wstrItemName = L"나막신";			wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::REPAIRED_SLIPPERS:		wstrItemName = L"덧댄 슬리퍼";		wstrItemEffect = L"방어력 +3";		break;
		case Client::EItemType::BOOTS:					wstrItemName = L"부츠";				wstrItemEffect = L"방어력 +3";		break;

		case Client::EItemType::STEEL_KNEE_PADS:		wstrItemName = L"강철 무릎 보호대";	wstrItemEffect = L"방어력 +6";		break;
		case Client::EItemType::COMBAT_BOOTS:			wstrItemName = L"전투화";			wstrItemEffect = L"방어력 +6";		break;

		case Client::EItemType::HIKING_BOOTS:			wstrItemName = L"등산화";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::GLACIER_CRAMPONS:		wstrItemName = L"아이젠";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::FEATHER_BOOTS:			wstrItemName = L"경량화 부츠";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::MAVERICK_RUNNER:		wstrItemName = L"매버릭 러너";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::STRAITJACKET_SNEAKERS:	wstrItemName = L"풍화륜";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::BUCEPHALUS:				wstrItemName = L"부케팔로스";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::EOD_BOOTS:				wstrItemName = L"EOD 부츠";			wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::WHITE_RHINOS:			wstrItemName = L"클링온 부츠";		wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::TACHYON_BRACE:			wstrItemName = L"타키온 브레이스";	wstrItemEffect = L"방어력 +9";		break;
		case Client::EItemType::SCV:					wstrItemName = L"SCV";				wstrItemEffect = L"방어력 +9";		break;

		case Client::EItemType::BOILING_WATER:			wstrItemName = L"뜨거운 물";		wstrItemEffect = L"스테미나 +400";	break;
		case Client::EItemType::COLA:					wstrItemName = L"콜라";				wstrItemEffect = L"스테미나 +400";	break;
		case Client::EItemType::HIGHBALL:				wstrItemName = L"하이볼";			wstrItemEffect = L"스테미나 +630";	break;
		case Client::EItemType::HONEY_WATER:			wstrItemName = L"꿀물";				wstrItemEffect = L"스테미나 +400";	break;

		case Client::EItemType::ENUM_END:				break;
		default:										break;
		}
	
		m_wpItemInfoImage.lock()->SetTextureIndex((int32)eItemType);
		m_wpItemInfoText[0].lock()->SetText(wstrItemName);
		m_wpItemInfoText[3].lock()->SetText(wstrItemEffect);
		// m_wpItemInfoText[4].lock()->SetText(wstrItemExplanation);
	}

	{
		EItemLevel eItemLevel = _spItem->GetItemLevel();
		wstring wstrItemLevel = L"";
		Vector4 vColor = Vector4::One;

		switch (eItemLevel)
		{
		case Client::EItemLevel::NORMAL:	wstrItemLevel = L"일반";	vColor = { 1.0f, 1.0f, 1.0f, 1.0f };	break;
		case Client::EItemLevel::UNCOMMON:	wstrItemLevel = L"고급";	vColor = { 0.0f, 1.0f, 0.0f, 1.0f };	break;
		case Client::EItemLevel::RARE:		wstrItemLevel = L"희귀";	vColor = { 0.0f, 1.0f, 1.0f, 1.0f };	break;
		case Client::EItemLevel::EPIC:		wstrItemLevel = L"영웅";	vColor = { 1.0f, 0.0f, 1.0f, 1.0f };	break;
		default:	break;
		}
		m_wpItemInfoText[1].lock()->SetText(wstrItemLevel);
		m_wpItemInfoText[1].lock()->SetTextColor(vColor);

		m_wpItemInfoLevelBackgoundImage.lock()->SetUIColor(vColor);
		// m_wpItemInfoLevelLineImage.lock()->SetUIColor(vColor);
	}
	
	{
		EItemCategoryType eItemCategoryType = _spItem->GetItemCategoryType();
		wstring wstrItemCategoryType = L"";
		wstring wstrItemExplanation = L"";

		switch (eItemCategoryType)
		{
		case Client::EItemCategoryType::WEAPON:
			wstrItemCategoryType = L"무기";
			wstrItemExplanation = L"좌클릭으로 착용할 수 있습니다.";
			break;

		case Client::EItemCategoryType::ARMOR:
			wstrItemCategoryType = L"옷";
			wstrItemExplanation = L"좌클릭으로 착용할 수 있습니다.";
			break;

		case Client::EItemCategoryType::HEAD:
			wstrItemCategoryType = L"머리";
			wstrItemExplanation = L"좌클릭으로 착용할 수 있습니다.";
			break;

		case Client::EItemCategoryType::ARM:
			wstrItemCategoryType = L"팔";
			wstrItemExplanation = L"좌클릭으로 착용할 수 있습니다.";
			break;

		case Client::EItemCategoryType::LEG:
			wstrItemCategoryType = L"다리";
			wstrItemExplanation = L"좌클릭으로 착용할 수 있습니다.";
			break;

		case Client::EItemCategoryType::FOOD:
			wstrItemCategoryType = L"음식";
			wstrItemExplanation = L"15초에 걸쳐 체력을 회복합니다.";
			break;

		case Client::EItemCategoryType::DRINK:
			wstrItemCategoryType = L"음료";
			wstrItemExplanation = L"15초에 걸쳐 스태미나를 회복합니다.";
			break;

		case Client::EItemCategoryType::MATERIAL:
			wstrItemCategoryType = L"재료";
			wstrItemExplanation = L"최대 수량 1개";
			break;

		case Client::EItemCategoryType::DECO:
			break;

		default:
			break;
		}
		m_wpItemInfoText[2].lock()->SetText(wstrItemCategoryType);
		m_wpItemInfoText[4].lock()->SetText(wstrItemExplanation);
	}
}
