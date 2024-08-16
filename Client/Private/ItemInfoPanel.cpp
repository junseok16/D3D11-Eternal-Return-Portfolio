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

	// �г� 1��
	shared_ptr<CItemInfoBackground> spItemInfoBackground = spLevel->CreateUI<CItemInfoBackground>(L"ItemInfoBackground");
	spItemInfoBackground->SetPriority(10);
	AddUI(L"ItemInfoBackground", spItemInfoBackground);
	m_wpItemInfoBackground = spItemInfoBackground;

	// ������ �̹���
	shared_ptr<CItemInfoImage> spItemInfoImage = spLevel->CreateUI<CItemInfoImage>(L"ItemInfoImage");
	spItemInfoImage->SetPriority(8);
	AddUI(L"ItemInfoImage", spItemInfoImage);
	m_wpItemInfoImage = spItemInfoImage;

	// ������ ��� �̹��� ���
	shared_ptr<CItemInfoLevelImage> spItemInfoLevelBackgoundImage = spLevel->CreateUI<CItemInfoLevelImage>(L"ItemInfoLevelBackgoundImage");
	spItemInfoLevelBackgoundImage->SetPriority(9);
	spItemInfoLevelBackgoundImage->SetItemInfoLevelImageType(EItemInfoLevelImageType::BACKGROUND);
	AddUI(L"ItemInfoLevelBackgoundImage", spItemInfoLevelBackgoundImage);
	m_wpItemInfoLevelBackgoundImage = spItemInfoLevelBackgoundImage;

	// ������ ��� �̹��� ��
	// shared_ptr<CItemInfoLevelImage> spItemInfoLevelLineImage = spLevel->CreateUI<CItemInfoLevelImage>(L"ItemInfoLevelLineImage");
	// spItemInfoLevelLineImage->SetPriority(9);
	// spItemInfoLevelLineImage->SetItemInfoLevelImageType(EItemInfoLevelImageType::LINE);
	// AddUI(L"ItemInfoLevelLineImage", spItemInfoLevelLineImage);
	// m_wpItemInfoLevelLineImage = spItemInfoLevelLineImage;

	// ������ �̸�
	shared_ptr<CItemInfoText> spItemNameText = spLevel->CreateUI<CItemInfoText>(L"ItemNameText");
	spItemNameText->SetItemInfoType(EItemInfoType::NAME);
	spItemNameText->SetFontName(L"KBIZM");
	spItemNameText->SetPriority(5);
	AddUI(L"ItemNameText", spItemNameText);
	m_wpItemInfoText[0] = spItemNameText;

	// ������ ���
	shared_ptr<CItemInfoText> spItemLevelText = spLevel->CreateUI<CItemInfoText>(L"ItemLevelText");
	spItemLevelText->SetItemInfoType(EItemInfoType::LEVEL);
	spItemLevelText->SetFontName(L"KBIZM");
	spItemLevelText->SetPriority(5);
	AddUI(L"ItemLevelText", spItemLevelText);
	m_wpItemInfoText[1] = spItemLevelText;

	// ������ ī�װ�
	shared_ptr<CItemInfoText> spItemCategoryText = spLevel->CreateUI<CItemInfoText>(L"ItemCategoryText");
	spItemCategoryText->SetItemInfoType(EItemInfoType::CATEGORY);
	spItemCategoryText->SetFontName(L"KBIZM");
	spItemCategoryText->SetPriority(5);
	AddUI(L"ItemCategoryText", spItemCategoryText);
	m_wpItemInfoText[2] = spItemCategoryText;

	// ������ ȿ��
	shared_ptr<CItemInfoText> spItemEffectText = spLevel->CreateUI<CItemInfoText>(L"ItemEffectText");
	spItemEffectText->SetItemInfoType(EItemInfoType::EFFECT);
	spItemEffectText->SetFontName(L"KBIZM");
	spItemEffectText->SetPriority(5);
	AddUI(L"ItemEffectText", spItemEffectText);
	m_wpItemInfoText[3] = spItemEffectText;

	// ������ ����
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
		case Client::EItemType::BRANCH:					wstrItemName = L"��������";			break;
		case Client::EItemType::STONE:					wstrItemName = L"������";			break;
		case Client::EItemType::LEATHER:				wstrItemName = L"����";				break;
		case Client::EItemType::SCISSORS:				wstrItemName = L"����";				break;
		case Client::EItemType::FOUNTAIN_PEN:			wstrItemName = L"������";			break;
		case Client::EItemType::PICKAXE:				wstrItemName = L"���";			break;
		case Client::EItemType::IRON_BALL:				wstrItemName = L"�豸��";			break;
		case Client::EItemType::GLASS_BOTTLE:			wstrItemName = L"������";			break;
		case Client::EItemType::PLAYING_CARDS:			wstrItemName = L"Ʈ���� ī��";		break;
		case Client::EItemType::CHALK:					wstrItemName = L"����";				break;
		case Client::EItemType::FEATHER:				wstrItemName = L"����";				break;
		case Client::EItemType::FLOWER:					wstrItemName = L"��";				break;
		case Client::EItemType::RIBBON:					wstrItemName = L"����";				break;
		case Client::EItemType::BUDDHIST_SCRIPTURE:		wstrItemName = L"�Ұ�";				break;
		case Client::EItemType::HOLY_GRAIL:				wstrItemName = L"����";				break;
		case Client::EItemType::CROSS:					wstrItemName = L"���ڰ�";			break;
		case Client::EItemType::BINOCULARS:				wstrItemName = L"�־Ȱ�";			break;
		case Client::EItemType::NAIL:					wstrItemName = L"��";				break;
		case Client::EItemType::TURTLE_SHELL:			wstrItemName = L"�ź��� �����";	break;
		case Client::EItemType::RUBBER:					wstrItemName = L"��";				break;
		case Client::EItemType::SCRAP_METAL:			wstrItemName = L"��ö";				break;
		case Client::EItemType::LIGHTER:				wstrItemName = L"������";			break;
		case Client::EItemType::LASER_POINTER:			wstrItemName = L"������������";		break;
		case Client::EItemType::STALLION_MEDAL:			wstrItemName = L"����";				break;
		case Client::EItemType::BATTERY:				wstrItemName = L"���͸�";			break;
		case Client::EItemType::OIL:					wstrItemName = L"�⸧";				break;
		case Client::EItemType::CLOTH:					wstrItemName = L"�ʰ�";				break;
		case Client::EItemType::GEMSTONE:				wstrItemName = L"����";				break;
		case Client::EItemType::GLUE:					wstrItemName = L"Ǯ";				break;
		case Client::EItemType::PAPER:					wstrItemName = L"����";				break;
		case Client::EItemType::GUNPOWDER:				wstrItemName = L"ȭ��";				break;
		case Client::EItemType::PIANO_WIRE:				wstrItemName = L"�ǾƳ� ��";		break;

		case Client::EItemType::COTTON_GLOVE:			wstrItemName = L"���尩";			wstrItemEffect = L"���ݷ� +3";	break;
		case Client::EItemType::BAMBOO:					wstrItemName = L"�볪��";			wstrItemEffect = L"���ݷ� +3";	break;
		case Client::EItemType::RUSTY_SWORD:			wstrItemName = L"�콼 ��";			wstrItemEffect = L"���ݷ� +3";	break;
		case Client::EItemType::WALTHER_PPK:			wstrItemName = L"���� PPK";			wstrItemEffect = L"���ݷ� +3";	break;
		case Client::EItemType::HAMMER:					wstrItemName = L"��ġ";				wstrItemEffect = L"���ݷ� +3";	break;

		case Client::EItemType::WINDBREAKER:			wstrItemName = L"�ٶ�����";			wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::MONKS_ROBE:				wstrItemName = L"�º�";				wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::WETSUIT:				wstrItemName = L"���� ������";		wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::FABRIC_ARMOR:			wstrItemName = L"õ ����";			wstrItemEffect = L"���� +3";	break;

		case Client::EItemType::HAIR_BAND:				wstrItemName = L"�Ӹ���";			wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::HAT:					wstrItemName = L"����";				wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::BIKE_HELMET:			wstrItemName = L"������ ���";		wstrItemEffect = L"���� +3";	break;

		case Client::EItemType::WATCH:					wstrItemName = L"�ո�ð�";			wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::BANDAGE:				wstrItemName = L"�ش�";				wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::BRACELET:				wstrItemName = L"����";				wstrItemEffect = L"���� +3";	break;

		case Client::EItemType::SLIPPER:				wstrItemName = L"������";			wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::RUNNING_SHOES:			wstrItemName = L"�ȭ";			wstrItemEffect = L"���� +3";	break;
		case Client::EItemType::TIGHTS:					wstrItemName = L"Ÿ����";			wstrItemEffect = L"���� +3";	break;

		case Client::EItemType::FLOWER_OF_FATE:			wstrItemName = L"����� ��";		break;
		case Client::EItemType::GLASS_PIECES:			wstrItemName = L"���� ����";		break;
		case Client::EItemType::SNIPER_SCOPE:			wstrItemName = L"���� ������";		break;
		case Client::EItemType::BUDDHA_SARIRA:			wstrItemName = L"���Ż縮";			break;
		case Client::EItemType::QUIVER:					wstrItemName = L"ȭ����";			break;
		case Client::EItemType::FEATHER_DUSTER:			wstrItemName = L"�������̰�";		break;
		case Client::EItemType::SHAMANS_BRONZE:			wstrItemName = L"���Ĵܵ�";			break;
		case Client::EItemType::MARKSMAN_HANDBOOK:		wstrItemName = L"��ݱ���";			break;
		case Client::EItemType::OIL_CLOTH:				wstrItemName = L"�⸧���� õ";		break;
		case Client::EItemType::CHALK_POWDER:			wstrItemName = L"���� ����";		break;
		case Client::EItemType::ASH:					wstrItemName = L"��";				break;
		case Client::EItemType::ELECTRONIC_PARTS:		wstrItemName = L"���� ��ǰ";		break;
		case Client::EItemType::BLUEPRINT:				wstrItemName = L"������ ����";		break;
		case Client::EItemType::IRON_SHEET:				wstrItemName = L"ö��";				break;
		case Client::EItemType::GOLD:					wstrItemName = L"��";				break;
		case Client::EItemType::HEATED_STONE:			wstrItemName = L"�ޱ��� ������";	break;
		case Client::EItemType::BARBED_WIRE:			wstrItemName = L"ö��";				break;
		case Client::EItemType::RUBY:					wstrItemName = L"���";				break;
		case Client::EItemType::HARDCOVER:				wstrItemName = L"�ϵ�Ŀ��";			break;
		case Client::EItemType::ION_BATTERY:			wstrItemName = L"�̿� ����";		break;

		case Client::EItemType::AETHER_FRINGE:			wstrItemName = L"���׸� ����";		break;
		case Client::EItemType::MOTOR:					wstrItemName = L"����";				break;
		case Client::EItemType::GLASS_PANEL:			wstrItemName = L"������";			break;

		case Client::EItemType::GLACIAL_ICE:			wstrItemName = L"�����";			break;
		case Client::EItemType::TRUE_SAMADHI_FIRE:		wstrItemName = L"�����ȭ";			break;
		case Client::EItemType::TREE_OF_LIFE:			wstrItemName = L"������ ����";		break;
		case Client::EItemType::METEORITE:				wstrItemName = L"�";				break;
		case Client::EItemType::MOONSTONE:				wstrItemName = L"������";			break;
		case Client::EItemType::MYTHRIL:				wstrItemName = L"�̽���";			break;
		case Client::EItemType::VF_BLOOD_SAMPLE:		wstrItemName = L"VF ���� ����";		break;
		case Client::EItemType::GEM_OF_EVOLUTION:		wstrItemName = L"��ȭ�� ��";		break;
		case Client::EItemType::FORCE_CORE:				wstrItemName = L"���� �ھ�";		break;

		case Client::EItemType::MEAT:					wstrItemName = L"���";				wstrItemEffect = L"ü�� +300";		break;
		case Client::EItemType::BREAD:					wstrItemName = L"��";				wstrItemEffect = L"ü�� +300";		break;
		case Client::EItemType::RAMEN:					wstrItemName = L"�����";			wstrItemEffect = L"ü�� +300";		break;
		case Client::EItemType::CHOCOLATE:				wstrItemName = L"���ݸ�";			wstrItemEffect = L"ü�� +300";		break;
																							
		case Client::EItemType::HONEY:					wstrItemName = L"��";				wstrItemEffect = L"���¹̳� +200";	break;
		case Client::EItemType::WATER:					wstrItemName = L"��";				wstrItemEffect = L"���¹̳� +200";	break;
		case Client::EItemType::WHISKEY:				wstrItemName = L"����Ű";			wstrItemEffect = L"���¹̳� +200";	break;
		case Client::EItemType::CARBONATED_WATER:		wstrItemName = L"ź���";			wstrItemEffect = L"���¹̳� +200";	break;
																							
		case Client::EItemType::LEATHER_GLOVES:			wstrItemName = L"�۷���";			wstrItemEffect = L"���ݷ� +6";		break;
		case Client::EItemType::IRON_KNUCKLES:			wstrItemName = L"���̾� ��Ŭ";		wstrItemEffect = L"���ݷ� +6";		break;
																							
		case Client::EItemType::GAUNTLET:				wstrItemName = L"��Ʋ��";			wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::WING_KNUCKLES:			wstrItemName = L"�� ��Ŭ";			wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::BONE_GAUNTLET:			wstrItemName = L"�Ͱ� �尩";		wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::SHATTER_SHELL_GAUNTLET:	wstrItemName = L"���±���";			wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::PHOENIX_GLOVES:			wstrItemName = L"ȸ�� �尩";		wstrItemEffect = L"���ݷ� +9";		break;

		case Client::EItemType::ONE_INCH_PUNCH:			wstrItemName = L"�ܿ���õ��";		wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::DIVINE_FIST:			wstrItemName = L"����� �ǽ�Ʈ";	wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::BLOODWING_KNUCKLES:		wstrItemName = L"������ ��Ŭ";	wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::FROST_PETAL_HAND:		wstrItemName = L"��ȭ������";		wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::BUDDHAS_PALM:			wstrItemName = L"��������";			wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::BRASIL_GAUNTLET:		wstrItemName = L"�극���� ��Ʋ��";	wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::WHITE_CLAW_PUNCH:		wstrItemName = L"�Ҽ�";				wstrItemEffect = L"���ݷ� +12";		break;

		case Client::EItemType::LONG_SWORD:				wstrItemName = L"���";				wstrItemEffect = L"���ݷ� +6";		break;

		case Client::EItemType::KATANA:					wstrItemName = L"�Ϻ���";			wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::MURAMASA:				wstrItemName = L"���󸶻�";			wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::BASTARD_SWORD:			wstrItemName = L"�ٽ�Ÿ�� �ҵ�";	wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::JEWEL_SWORD:			wstrItemName = L"����";				wstrItemEffect = L"���ݷ� +9";		break;

		case Client::EItemType::THUAN_THIEN:			wstrItemName = L"�Ѿ� �쿣";		wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::ARONDIGHT:				wstrItemName = L"�Ʒд���Ʈ";		wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::EXCALIBUR:				wstrItemName = L"����Į����";		wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::MONOHOSHIZAO:			wstrItemName = L"���ȣ���ڿ�";		wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::HOVUD:					wstrItemName = L"ȣǪ���";			wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::ARCANE_EDGE:			wstrItemName = L"������ ����";		wstrItemEffect = L"���ݷ� +12";		break;

		case Client::EItemType::MAGNUM_PYTHON:			wstrItemName = L"�ű׳�-���̼�";	wstrItemEffect = L"���ݷ� +6";		break;
		case Client::EItemType::BERETTA_M92F:			wstrItemName = L"����Ÿ M92F";		wstrItemEffect = L"���ݷ� +6";		break;

		case Client::EItemType::FN57:					wstrItemName = L"FN57";				wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::MAGNUM_ANACONDA:		wstrItemName = L"�ű׳�-�Ƴ��ܴ�";	wstrItemEffect = L"���ݷ� +9";		break;
		case Client::EItemType::DERRINGER:				wstrItemName = L"������";			wstrItemEffect = L"���ݷ� +9";		break;

		case Client::EItemType::ELEGANCE:				wstrItemName = L"��������";			wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::ELECTRON_BLASTER:		wstrItemName = L"�Ϸ�Ʈ�� �����";wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::MAGNUM_BOA:				wstrItemName = L"�ű׳�-����";		wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::GLOCK48:				wstrItemName = L"�۷� 48";			wstrItemEffect = L"���ݷ� +12";		break;
		case Client::EItemType::STAMPEDE:				wstrItemName = L"�����ǵ�";			wstrItemEffect = L"���ݷ� +12";		break;

		case Client::EItemType::LEATHER_ARMOR:			wstrItemName = L"���� ����";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::LEATHER_JACKET:			wstrItemName = L"���� ����";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::MILITARY_SUIT:			wstrItemName = L"����";				wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::PATCHED_ROBE:			wstrItemName = L"���� �κ�";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::DRESS:					wstrItemName = L"�巹��";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::BIKINI:					wstrItemName = L"��Ű��";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::DIVING_SUIT:			wstrItemName = L"�����";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::DEACON_ROBES:			wstrItemName = L"������";			wstrItemEffect = L"���� +3";		break;

		case Client::EItemType::RIDER_JACKET:			wstrItemName = L"���̴� ����";		wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::CHAIN_ARMOR:			wstrItemName = L"�罽 ����";		wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::SUIT:					wstrItemName = L"����";				wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::QIPAO:					wstrItemName = L"ġ�Ŀ�";			wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::SHEET_METAL_ARMOR:		wstrItemName = L"�Ǳݰ���";			wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::HANBOK:					wstrItemName = L"�Ѻ�";				wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::BULLETPROOF_VEST:		wstrItemName = L"��ź����";			wstrItemEffect = L"���� +6";		break;

		case Client::EItemType::CARDINAL_ROBES:			wstrItemName = L"���� ������";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::SUNSET_ARMOR:			wstrItemName = L"������ ����";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::COVERT_AGENT_UNIFORM:	wstrItemName = L"�����";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::OPTICAL_CAMOUFLAGE_SUIT:wstrItemName = L"���й�ä ��Ʈ";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::ROCKERS_JACKET:			wstrItemName = L"��Ŀ�� ����";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::CRUSADER_ARMOR:			wstrItemName = L"������� ����";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::AMAZONESS_ARMOR:		wstrItemName = L"�Ƹ����׽� �Ƹ�";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::DRAGON_DOBOK:			wstrItemName = L"���� ����";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::COMMANDERS_ARMOR:		wstrItemName = L"���ְ��� ����";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::BUTLERS_SUIT:			wstrItemName = L"���纹";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::BATTLE_SUIT:			wstrItemName = L"��Ʋ ��Ʈ";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::EOD_SUIT:				wstrItemName = L"EOD ��Ʈ";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::TUXEDO:					wstrItemName = L"�νõ�";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::HIGH_PRIEST_ROBES:		wstrItemName = L"�������� ����";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::CHANGPAO:				wstrItemName = L"â�Ŀ�";			wstrItemEffect = L"���� +9";		break;

		case Client::EItemType::MASK:					wstrItemName = L"����";				wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::CIRCLET:				wstrItemName = L"�Ӹ���";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::BERET:					wstrItemName = L"������";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::CHAIN_COIF:				wstrItemName = L"�罽 ������";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::SAFETY_HELMET:			wstrItemName = L"������";			wstrItemEffect = L"���� +3";		break;

		case Client::EItemType::BALLISTIC_HELMET:		wstrItemName = L"��ź��";			wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::FIRE_HELMET:			wstrItemName = L"�ҹ� ���";		wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::TIARA:					wstrItemName = L"Ƽ�ƶ�";			wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::CROWN:					wstrItemName = L"�հ�";				wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::CLOSE_HELM:				wstrItemName = L"����";				wstrItemEffect = L"���� +6";		break;

		case Client::EItemType::VIRTUOUS_OUTLAW:		wstrItemName = L"�κ�";				wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::CRYSTAL_TIARA:			wstrItemName = L"���� Ƽ�ƶ�";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::MOTORCYCLE_HELMET:		wstrItemName = L"������� ���";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::TACTICAL_OPS_HELMET:	wstrItemName = L"���� OPS ���";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::HELM_OF_BANNERET:		wstrItemName = L"�������� ����";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::IMPERIAL_CROWN:			wstrItemName = L"���� �հ�";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::IMPERIAL_BURGONET:		wstrItemName = L"Ȳ�� �θ����";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::MOHAWK_HEADGEAR:		wstrItemName = L"��ȣũ ���";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::VIGILANTE:				wstrItemName = L"��������";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::DIADEM:					wstrItemName = L"���̾Ƶ�";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::CRUSADER_HELMET:		wstrItemName = L"������� ����";	wstrItemEffect = L"���� +9";		break;

		case Client::EItemType::LEATHER_SHIELD:			wstrItemName = L"���� ����";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::SQUARD_LEADER_ARMBAND:	wstrItemName = L"�д��� ����";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::BRACER:					wstrItemName = L"�극�̼�";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::BROKEN_WATCH:			wstrItemName = L"���峭 �ð�";		wstrItemEffect = L"���� +3";		break;

		case Client::EItemType::SHEATH:					wstrItemName = L"����";				wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::GOLDEN_BRACELET:		wstrItemName = L"������";			wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::BAZUBAND:				wstrItemName = L"���ֹݵ�";			wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::CRIMSON_BRACELET:		wstrItemName = L"��ȫ ����";		wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::BARBED_BLOSSOM:			wstrItemName = L"�ٺ�� ��μ�";	wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::STEEL_SHIELD:			wstrItemName = L"��ö ����";		wstrItemEffect = L"���� +6";		break;

		case Client::EItemType::CORRUPTING_TOUCH:		wstrItemName = L"�������";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::SWORD_STOPPER:			wstrItemName = L"�ҵ� ������";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::DRAUPNIR:				wstrItemName = L"�������ϸ�";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::VITAL_SIGH_SENSOR:		wstrItemName = L"����Ż ����";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::CREED_OF_THE_KNIGHT:	wstrItemName = L"����� ����";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::SHEATH_OF_SHAH_JUHAN:	wstrItemName = L"�������� ����";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::BURNISHED_AEGIS:		wstrItemName = L"���̱⽺";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::TINDALOS_BAND:			wstrItemName = L"ƾ�޷ν��� ����";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::NIGHTINGALE:			wstrItemName = L"�����ð���";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::PLASMA_ARC:				wstrItemName = L"�ö�� ��ũ";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::SMART_BAND:				wstrItemName = L"����Ʈ ���";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::SPORTS_WATCH:			wstrItemName = L"������ �ð�";		wstrItemEffect = L"���� +9";		break;

		case Client::EItemType::KNEE_PADS:				wstrItemName = L"���� ��ȣ��";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::CHAIN_LEGGINGS:			wstrItemName = L"ü�� ���뽺";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::HIGH_HEELS:				wstrItemName = L"������";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::HEELYS:					wstrItemName = L"������";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::CLOGS:					wstrItemName = L"������";			wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::REPAIRED_SLIPPERS:		wstrItemName = L"���� ������";		wstrItemEffect = L"���� +3";		break;
		case Client::EItemType::BOOTS:					wstrItemName = L"����";				wstrItemEffect = L"���� +3";		break;

		case Client::EItemType::STEEL_KNEE_PADS:		wstrItemName = L"��ö ���� ��ȣ��";	wstrItemEffect = L"���� +6";		break;
		case Client::EItemType::COMBAT_BOOTS:			wstrItemName = L"����ȭ";			wstrItemEffect = L"���� +6";		break;

		case Client::EItemType::HIKING_BOOTS:			wstrItemName = L"���ȭ";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::GLACIER_CRAMPONS:		wstrItemName = L"������";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::FEATHER_BOOTS:			wstrItemName = L"�淮ȭ ����";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::MAVERICK_RUNNER:		wstrItemName = L"�Ź��� ����";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::STRAITJACKET_SNEAKERS:	wstrItemName = L"ǳȭ��";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::BUCEPHALUS:				wstrItemName = L"�����ȷν�";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::EOD_BOOTS:				wstrItemName = L"EOD ����";			wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::WHITE_RHINOS:			wstrItemName = L"Ŭ���� ����";		wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::TACHYON_BRACE:			wstrItemName = L"ŸŰ�� �극�̽�";	wstrItemEffect = L"���� +9";		break;
		case Client::EItemType::SCV:					wstrItemName = L"SCV";				wstrItemEffect = L"���� +9";		break;

		case Client::EItemType::BOILING_WATER:			wstrItemName = L"�߰ſ� ��";		wstrItemEffect = L"���׹̳� +400";	break;
		case Client::EItemType::COLA:					wstrItemName = L"�ݶ�";				wstrItemEffect = L"���׹̳� +400";	break;
		case Client::EItemType::HIGHBALL:				wstrItemName = L"���̺�";			wstrItemEffect = L"���׹̳� +630";	break;
		case Client::EItemType::HONEY_WATER:			wstrItemName = L"�ܹ�";				wstrItemEffect = L"���׹̳� +400";	break;

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
		case Client::EItemLevel::NORMAL:	wstrItemLevel = L"�Ϲ�";	vColor = { 1.0f, 1.0f, 1.0f, 1.0f };	break;
		case Client::EItemLevel::UNCOMMON:	wstrItemLevel = L"���";	vColor = { 0.0f, 1.0f, 0.0f, 1.0f };	break;
		case Client::EItemLevel::RARE:		wstrItemLevel = L"���";	vColor = { 0.0f, 1.0f, 1.0f, 1.0f };	break;
		case Client::EItemLevel::EPIC:		wstrItemLevel = L"����";	vColor = { 1.0f, 0.0f, 1.0f, 1.0f };	break;
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
			wstrItemCategoryType = L"����";
			wstrItemExplanation = L"��Ŭ������ ������ �� �ֽ��ϴ�.";
			break;

		case Client::EItemCategoryType::ARMOR:
			wstrItemCategoryType = L"��";
			wstrItemExplanation = L"��Ŭ������ ������ �� �ֽ��ϴ�.";
			break;

		case Client::EItemCategoryType::HEAD:
			wstrItemCategoryType = L"�Ӹ�";
			wstrItemExplanation = L"��Ŭ������ ������ �� �ֽ��ϴ�.";
			break;

		case Client::EItemCategoryType::ARM:
			wstrItemCategoryType = L"��";
			wstrItemExplanation = L"��Ŭ������ ������ �� �ֽ��ϴ�.";
			break;

		case Client::EItemCategoryType::LEG:
			wstrItemCategoryType = L"�ٸ�";
			wstrItemExplanation = L"��Ŭ������ ������ �� �ֽ��ϴ�.";
			break;

		case Client::EItemCategoryType::FOOD:
			wstrItemCategoryType = L"����";
			wstrItemExplanation = L"15�ʿ� ���� ü���� ȸ���մϴ�.";
			break;

		case Client::EItemCategoryType::DRINK:
			wstrItemCategoryType = L"����";
			wstrItemExplanation = L"15�ʿ� ���� ���¹̳��� ȸ���մϴ�.";
			break;

		case Client::EItemCategoryType::MATERIAL:
			wstrItemCategoryType = L"���";
			wstrItemExplanation = L"�ִ� ���� 1��";
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
