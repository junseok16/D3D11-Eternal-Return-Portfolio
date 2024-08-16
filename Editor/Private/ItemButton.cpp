#include "pch.h"
#include "ItemButton.h"

#include "Inventory.h"
#include "ItemBox.h"
#include "Item.h"

#include "GameManager.h"
#include "Survivor.h"

#include "Controller.h"
#include "Survivor.h"
#include "WildAnimal.h"

HRESULT Editor::CItemButton::PreInitialize()
{
	// 델리게이트를 추가합니다.
	AddOnButtonUpInDelegate(static_pointer_cast<CItemButton>(shared_from_this()), &CItemButton::OnButtonUpIn);
	AddOnButtonUpOutDelegate(static_pointer_cast<CItemButton>(shared_from_this()), &CItemButton::OnButtonUpOut);

	SetActorRenderType(ERenderType::TRANSLUCENT_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetButtonState(EButtonState::ENABLE);

	SetButtonNames
	(
		{
			// 돌, 나뭇가지, 가죽
			L"ItemIcon_108101",
			L"ItemIcon_112101",
			L"ItemIcon_401103",

			// 일반 재료
			L"ItemIcon_101101",
			L"ItemIcon_101102",
			L"ItemIcon_105102",

			L"ItemIcon_112103",
			L"ItemIcon_112104",
			L"ItemIcon_113102",
			L"ItemIcon_113104",
			L"ItemIcon_205101",
			L"ItemIcon_205102",
			L"ItemIcon_205103",
			L"ItemIcon_205106",
			L"ItemIcon_205108",
			L"ItemIcon_205109",
			L"ItemIcon_205110",
			L"ItemIcon_401101",
			L"ItemIcon_401104",
			L"ItemIcon_401105",
			L"ItemIcon_401106",
			L"ItemIcon_401107",
			L"ItemIcon_401108",
			L"ItemIcon_401109",
			L"ItemIcon_401110",
			L"ItemIcon_401112",
			L"ItemIcon_401113",
			L"ItemIcon_401114",
			L"ItemIcon_401116",
			L"ItemIcon_401117",
			L"ItemIcon_401121",
			L"ItemIcon_502104",

			// 일반 무기
			L"ItemIcon_110102",
			L"ItemIcon_102101",
			L"ItemIcon_116101",
			L"ItemIcon_104101",

			// 일반 옷
			L"ItemIcon_202101",
			L"ItemIcon_202103",
			L"ItemIcon_202105",
			L"ItemIcon_202106",

			// 일반 머리
			L"ItemIcon_201101",
			L"ItemIcon_201102",
			L"ItemIcon_201104",

			// 일반 팔
			L"ItemIcon_203101",
			L"ItemIcon_203102",
			L"ItemIcon_203104",
			
			// 일반 다리
			L"ItemIcon_204101",
			L"ItemIcon_204102",
			L"ItemIcon_204103",

			// 고급 재료
			L"ItemIcon_205203",
			L"ItemIcon_205204",
			L"ItemIcon_205206",
			L"ItemIcon_205207",
			L"ItemIcon_205208",
			L"ItemIcon_205209",
			L"ItemIcon_205211",
			L"ItemIcon_205213",
			L"ItemIcon_401202",
			L"ItemIcon_401206",
			L"ItemIcon_401210",
			L"ItemIcon_401211",
			L"ItemIcon_401211",
			L"ItemIcon_401213",
			L"ItemIcon_401214",
			L"ItemIcon_401215",
			L"ItemIcon_401216",
			L"ItemIcon_401217",
			L"ItemIcon_401218",
			L"ItemIcon_401306",

			// 희귀 재료
			L"ItemIcon_205312",
			L"ItemIcon_401303",
			L"ItemIcon_401305",

			// 영웅 재료
			L"ItemIcon_205402",
			L"ItemIcon_205403",
			L"ItemIcon_401208",
			L"ItemIcon_401209",
			L"ItemIcon_401301",
			L"ItemIcon_401304",
			L"ItemIcon_401401",
			L"ItemIcon_401402",
			L"ItemIcon_401403",

			// 일반 음식
			L"ItemIcon_301111",
			L"ItemIcon_301110",
			L"ItemIcon_301113",
			L"ItemIcon_301119",

			// 일반 음료
			L"ItemIcon_302101",
			L"ItemIcon_302102",
			L"ItemIcon_302104",
			L"ItemIcon_302107",

			// 고급 글러브
			L"ItemIcon_110201",
			L"ItemIcon_110202",

			// 희귀 글러브
			L"ItemIcon_110301",
			L"ItemIcon_110302",
			L"ItemIcon_110401",
			L"ItemIcon_110402",
			L"ItemIcon_110404",

			// 영웅 글러브
			L"ItemIcon_110405",
			L"ItemIcon_110406",
			L"ItemIcon_110407",
			L"ItemIcon_110408",
			L"ItemIcon_110409",
			L"ItemIcon_110410",
			L"ItemIcon_110411",

			// 고급 양손검
			L"ItemIcon_102401",

			// 희귀 양손검
			L"ItemIcon_102301",
			L"ItemIcon_102402",
			L"ItemIcon_102403",
			L"ItemIcon_102404",

			// 영웅 양손검
			L"ItemIcon_102405",
			L"ItemIcon_102406",
			L"ItemIcon_102407",
			L"ItemIcon_102410",
			L"ItemIcon_102411",
			L"ItemIcon_102413",

			// 고급 피스톨
			L"ItemIcon_116201",
			L"ItemIcon_116202",

			// 희귀 피스톨
			L"ItemIcon_116301",
			L"ItemIcon_116402",
			L"ItemIcon_116408",

			// 영웅 피스톨
			L"ItemIcon_116404",
			L"ItemIcon_116405",
			L"ItemIcon_116406",
			L"ItemIcon_116407",
			L"ItemIcon_116409",

			// 고급 옷
			L"ItemIcon_202201",
			L"ItemIcon_202202",
			L"ItemIcon_202205",
			L"ItemIcon_202206",
			L"ItemIcon_202207",
			L"ItemIcon_202209",
			L"ItemIcon_202210",
			L"ItemIcon_202211",


			// 희귀 옷
			L"ItemIcon_202301",
			L"ItemIcon_202302",
			L"ItemIcon_202303",
			L"ItemIcon_202304",
			L"ItemIcon_202305",
			L"ItemIcon_202306",
			L"ItemIcon_202401",


			// 영웅 옷
			L"ItemIcon_202307",
			L"ItemIcon_202402",
			L"ItemIcon_202404",
			L"ItemIcon_202405",
			L"ItemIcon_202406",
			L"ItemIcon_202408",
			L"ItemIcon_202410",
			L"ItemIcon_202411",
			L"ItemIcon_202412",
			L"ItemIcon_202413",
			L"ItemIcon_202415",
			L"ItemIcon_202417",
			L"ItemIcon_202418",
			L"ItemIcon_202419",
			L"ItemIcon_202414",

			// 고급 머리
			L"ItemIcon_201201",
			L"ItemIcon_201202",
			L"ItemIcon_201203",
			L"ItemIcon_201204",
			L"ItemIcon_201205",

			// 희귀 머리
			L"ItemIcon_201301",
			L"ItemIcon_201302",
			L"ItemIcon_201303",
			L"ItemIcon_201401",
			L"ItemIcon_201402",

			// 영웅 머리
			L"ItemIcon_201304",
			L"ItemIcon_201404",
			L"ItemIcon_201405",
			L"ItemIcon_201406",
			L"ItemIcon_201407",
			L"ItemIcon_201409",
			L"ItemIcon_201410",
			L"ItemIcon_201412",
			L"ItemIcon_201413",
			L"ItemIcon_201414",
			L"ItemIcon_201415",

			// 고급 팔
			L"ItemIcon_203201",
			L"ItemIcon_203202",
			L"ItemIcon_203203",
			L"ItemIcon_203204",

			// 희귀 팔
			L"ItemIcon_203301",
			L"ItemIcon_203302",
			L"ItemIcon_203303",
			L"ItemIcon_203304",
			L"ItemIcon_203305",
			L"ItemIcon_203401",

			// 영웅 팔
			L"ItemIcon_203306",
			L"ItemIcon_203402",
			L"ItemIcon_203403",
			L"ItemIcon_203405",
			L"ItemIcon_203406",
			L"ItemIcon_203407",
			L"ItemIcon_203409",
			L"ItemIcon_203410",
			L"ItemIcon_203411",
			L"ItemIcon_203412",
			L"ItemIcon_203414",
			L"ItemIcon_203506",

			// 고급 다리
			L"ItemIcon_204201",
			L"ItemIcon_204202",
			L"ItemIcon_204203",
			L"ItemIcon_204204",
			L"ItemIcon_204205",
			L"ItemIcon_204301",
			L"ItemIcon_204302",

			// 희귀 다리
			L"ItemIcon_204401",
			L"ItemIcon_204404",

			// 영웅 다리
			L"ItemIcon_204303",
			L"ItemIcon_204304",
			L"ItemIcon_204402",
			L"ItemIcon_204403",
			L"ItemIcon_204406",
			L"ItemIcon_204408",
			L"ItemIcon_204409",
			L"ItemIcon_204411",
			L"ItemIcon_204412",
			L"ItemIcon_204415",

			// 고급 음료
			L"ItemIcon_302201",
			L"ItemIcon_302209",
			L"ItemIcon_302213",
			L"ItemIcon_302215",
		}
	);

	return CButton::PreInitialize();
}

HRESULT Editor::CItemButton::Initialize()
{
	SetWidth(27.0f);
	SetHeight(24.0f);

	switch (m_eItemBelongType)
	{
	case Editor::EItemBelongType::CRAFT:
	{
		switch (m_eItemSlotType)
		{
		case Editor::EItemSlotType::FIRST:	SetPivot({ 832.0f, 609.0f });	break;
		case Editor::EItemSlotType::SECOND:	SetPivot({ 879.0f, 609.0f });	break;
		case Editor::EItemSlotType::THIRD:	SetPivot({ 926.0f, 609.0f });	break;
		case Editor::EItemSlotType::FOURTH:	SetPivot({ 973.0f, 609.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Editor::EItemBelongType::EQUIPMENT:
	{
		SetWidth(24.0f);
		SetHeight(22.0f);

		switch (m_eItemSlotType)
		{
		case Editor::EItemSlotType::FIRST:	SetPivot({ 333.0f, 663.0f });	break;
		case Editor::EItemSlotType::SECOND:	SetPivot({ 373.0f, 663.0f });	break;
		case Editor::EItemSlotType::THIRD:	SetPivot({ 413.0f, 663.0f });	break;
		case Editor::EItemSlotType::FOURTH:	SetPivot({ 333.0f, 692.0f });	break;
		case Editor::EItemSlotType::FIFTH:	SetPivot({ 373.0f, 692.0f });	break;
		case Editor::EItemSlotType::SIXTH:	SetPivot({ 413.0f, 692.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Editor::EItemBelongType::INVENTORY:
	{
		switch (m_eItemSlotType)
		{
		case Editor::EItemSlotType::FIRST:	SetPivot({ 785.0f, 652.0f });	break;
		case Editor::EItemSlotType::SECOND:	SetPivot({ 832.0f, 652.0f });	break;
		case Editor::EItemSlotType::THIRD:	SetPivot({ 879.0f, 652.0f });	break;
		case Editor::EItemSlotType::FOURTH:	SetPivot({ 926.0f, 652.0f });	break;
		case Editor::EItemSlotType::FIFTH:	SetPivot({ 973.0f, 652.0f });	break;
		case Editor::EItemSlotType::SIXTH:	SetPivot({ 785.0f, 685.0f });	break;
		case Editor::EItemSlotType::SEVENTH:SetPivot({ 832.0f, 685.0f });	break;
		case Editor::EItemSlotType::EIGHTH:	SetPivot({ 879.0f, 685.0f });	break;
		case Editor::EItemSlotType::NINETH:	SetPivot({ 926.0f, 685.0f });	break;
		case Editor::EItemSlotType::TENTH:	SetPivot({ 973.0f, 685.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Editor::EItemBelongType::ITEM_BOX:
	{
		switch (m_eItemSlotType)
		{
		case Editor::EItemSlotType::FIRST:	SetPivot({ 886.0f,  519.0f });	break;
		case Editor::EItemSlotType::SECOND:	SetPivot({ 938.0f,  519.0f });	break;
		case Editor::EItemSlotType::THIRD:	SetPivot({ 990.0f,  519.0f });	break;
		case Editor::EItemSlotType::FOURTH:	SetPivot({ 1042.0f, 519.0f });	break;
		case Editor::EItemSlotType::FIFTH:	SetPivot({ 886.0f,  555.0f });	break;
		case Editor::EItemSlotType::SIXTH:	SetPivot({ 938.0f,  555.0f });	break;
		case Editor::EItemSlotType::SEVENTH:SetPivot({ 990.0f,  555.0f });	break;
		case Editor::EItemSlotType::EIGHTH:	SetPivot({ 1042.0f, 555.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Editor::EItemBelongType::DEAD_BODY:
	{

	}
	break;

	default:
		CHECKF(false, L"Item belong type is not designated.")
		break;
	}

	return CButton::Initialize();
}

HRESULT Editor::CItemButton::PostInitialize()
{
	if (FAILED(CButton::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CItemButton::BeginPlay()
{
	if (FAILED(CButton::BeginPlay())) { return E_FAIL; }

	m_wpGameManager = CGameManager::GetInstance();
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();
	m_wpInventory = m_wpSurvivor.lock()->GetInventory();

	return S_OK;
}

int32 Editor::CItemButton::PreTick(float _fDeltaSeconds)
{
	switch (CButton::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CItemButton::Tick(float _fDeltaSeconds)
{
	switch (CButton::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// 아이템 슬롯에 아이템이 없는 경우
	if (m_wpItem.expired())
	{
		m_eButtonState = EButtonState::INACTIVE;
		return 0;
	}
	m_eButtonState = EButtonState::ENABLE;
	
	switch (m_wpItem.lock()->GetItemCategoryType())
	{
	case EItemCategoryType::WEAPON:
		SetTextureIndex((int32)m_wpItem.lock()->GetItemType());
		break;

	case EItemCategoryType::ARMOR:
		SetTextureIndex((int32)m_wpItem.lock()->GetItemType());
		break;

	case EItemCategoryType::HEAD:
		SetTextureIndex((int32)m_wpItem.lock()->GetItemType());
		break;

	case EItemCategoryType::ARM:
		SetTextureIndex((int32)m_wpItem.lock()->GetItemType());
		break;

	case EItemCategoryType::LEG:
		SetTextureIndex((int32)m_wpItem.lock()->GetItemType());
		break;

	case EItemCategoryType::DECO:
		break;

	case EItemCategoryType::FOOD:
		SetTextureIndex((int32)m_wpItem.lock()->GetItemType());
		break;

	case EItemCategoryType::DRINK:
		SetTextureIndex((int32)m_wpItem.lock()->GetItemType());
		break;

	case EItemCategoryType::MATERIAL:
		SetTextureIndex((int32)m_wpItem.lock()->GetItemType());
		break;

	default:
		break;
	}

	return 0;
}

int32 Editor::CItemButton::PostTick(float _fDeltaSeconds)
{
	switch (CButton::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CItemButton::EndPlay()
{
	if (FAILED(CButton::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CItemButton::Render()
{
	CButton::Render();
}

void Editor::CItemButton::Release()
{
	CButton::Release();
}

void Editor::CItemButton::OnButtonUpIn()
{
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();
	m_wpInventory = m_wpSurvivor.lock()->GetInventory();

	switch (m_wpItem.lock()->GetItemBelongType())
	{
	case Editor::EItemBelongType::EQUIPMENT:
	{
		// 인벤토리에 여유 공간이 있는 경우, 장비를 이동합니다.
	}
	break;

	case Editor::EItemBelongType::CRAFT:
	{
		// 생존자의 상태를 변경합니다.
		switch (m_wpItem.lock()->GetItemCategoryType())
		{
		case EItemCategoryType::FOOD:
		case EItemCategoryType::DRINK:
			m_wpSurvivor.lock()->SetSurvivorState(ESurvivorState::CRAFT_FOOD);
			break;

		case EItemCategoryType::ARM:
		case EItemCategoryType::ARMOR:
		case EItemCategoryType::DECO:
		case EItemCategoryType::HEAD:
		case EItemCategoryType::LEG:
		case EItemCategoryType::MATERIAL:
		case EItemCategoryType::WEAPON:
			m_wpSurvivor.lock()->SetSurvivorState(ESurvivorState::CRAFT_METAL);
			break;
		}

		// 제작할 아이템을 예약합니다.
		m_wpInventory.lock()->ReserveItem(m_wpItem.lock()->GetItemType(), m_eItemSlotType);
	}
	break;

	case Editor::EItemBelongType::INVENTORY:
	{
		switch (m_wpItem.lock()->GetItemCategoryType())
		{
		case EItemCategoryType::FOOD:
		case EItemCategoryType::DRINK:
			m_wpInventory.lock()->EatItem((int32)m_eItemSlotType);
			break;

		case EItemCategoryType::HEAD:
			m_wpInventory.lock()->SwapItem2Equipment(m_wpItem.lock(), EEquipSlotType::HEAD, m_eItemSlotType);
			break;

		case EItemCategoryType::WEAPON:
			m_wpInventory.lock()->SwapItem2Equipment(m_wpItem.lock(), EEquipSlotType::WEAPON, m_eItemSlotType);
			break;

		case EItemCategoryType::ARMOR:
			m_wpInventory.lock()->SwapItem2Equipment(m_wpItem.lock(), EEquipSlotType::ARMOR, m_eItemSlotType);
			break;

		case EItemCategoryType::ARM:
			m_wpInventory.lock()->SwapItem2Equipment(m_wpItem.lock(), EEquipSlotType::ARM, m_eItemSlotType);
			break;

		case EItemCategoryType::LEG:
			m_wpInventory.lock()->SwapItem2Equipment(m_wpItem.lock(), EEquipSlotType::LEG, m_eItemSlotType);
			break;

		case EItemCategoryType::DECO:
			m_wpInventory.lock()->SwapItem2Equipment(m_wpItem.lock(), EEquipSlotType::DECO, m_eItemSlotType);
			break;

		default:
			break;
		}
	}
	break;

	case Editor::EItemBelongType::ITEM_BOX:
	{
		shared_ptr<CItemBox> spItemBox = dynamic_pointer_cast<CItemBox>(m_wpItem.lock()->GetItemOwner());

		// std::array<std::shared_ptr<CItem>, 8>& arrItems = spItemBox->GetItems();
		// if (FAILED(m_wpInventory.lock()->AddItem(arrItems[(int32)m_eItemSlotType]))) { break; }

		m_wpItem.lock()->SetItemBelongType(EItemBelongType::INVENTORY);
		if (FAILED(m_wpInventory.lock()->AddItem(m_wpItem.lock()))) { break; }
		spItemBox->RemoveItem(m_eItemSlotType);

		m_wpInventory.lock()->CheckItemBuildOrder();
	}
	break;

	case Editor::EItemBelongType::DEAD_BODY:
	{

	}
	break;

	case Editor::EItemBelongType::WILD_ANIMAL:
	{
		shared_ptr<CWildAnimal> spWildAnimal = dynamic_pointer_cast<CWildAnimal>(m_wpItem.lock()->GetItemOwner());

		// std::array<std::shared_ptr<CItem>, 8>& arrItems = spItemBox->GetItems();
		// if (FAILED(m_wpInventory.lock()->AddItem(arrItems[(int32)m_eItemSlotType]))) { break; }

		m_wpItem.lock()->SetItemBelongType(EItemBelongType::INVENTORY);
		if (FAILED(m_wpInventory.lock()->AddItem(m_wpItem.lock()))) { break; }
		spWildAnimal->RemoveItem(m_eItemSlotType);

		m_wpInventory.lock()->CheckItemBuildOrder();
	}
	break;

	default:
		CHECKF(false, L"Item belong type is not designated.");
		break;
	}

}

void Editor::CItemButton::OnButtonUpOut()
{
	m_wpSurvivor = m_wpGameManager.lock()->GetSurvivor();
	m_wpInventory = m_wpSurvivor.lock()->GetInventory();

	switch (m_eItemBelongType)
	{
	case Editor::EItemBelongType::EQUIPMENT:
	{

	}
	break;

	case Editor::EItemBelongType::INVENTORY:
	{
		// m_wpSurvivor.lock()->GetSurvivorState();
		m_wpInventory.lock()->RemoveItem(m_eItemSlotType);
	}
	break;

	case Editor::EItemBelongType::ITEM_BOX:
	{
		
	}
	break;

	case Editor::EItemBelongType::DEAD_BODY:
	{

	}
	break;

	default:
	{
		CHECKF(false, L"Item belong type is not designated.");
	}
	break;
	}
}
