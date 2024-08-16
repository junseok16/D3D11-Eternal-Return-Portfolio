#include "pch.h"
#include "ItemBoxPanel.h"

#include "ItemBoxBackground.h"
#include "ItemSlotImage.h"
#include "ItemButton.h"

#include "World.h"
#include "Level.h"

HRESULT Editor::CItemBoxPanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CItemBoxPanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CItemBoxPanel::PostInitialize()
{
	if (FAILED(CPanel::PostInitialize())) { return E_FAIL; }

	shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();

	// 패널 1개
	shared_ptr<CItemBoxBackground> spItemBoxBackground = spLevel->CreateUI<CItemBoxBackground>(L"ItemBoxBackground");
	spItemBoxBackground->SetPriority(20);
	AddUI(L"ItemBoxBackground", spItemBoxBackground);

	// 빈 슬롯 8개
	shared_ptr<CItemSlotImage> spFirstItemBoxSlotImage = spLevel->CreateUI<CItemSlotImage>(L"FirstItemBoxSlot");
	shared_ptr<CItemSlotImage> spSecondItemBoxSlotImage = spLevel->CreateUI<CItemSlotImage>(L"SecondItemBoxSlot");
	shared_ptr<CItemSlotImage> spThirdItemBoxSlotImage = spLevel->CreateUI<CItemSlotImage>(L"ThirdItemBoxSlot");
	shared_ptr<CItemSlotImage> spFourthItemBoxSlotImage = spLevel->CreateUI<CItemSlotImage>(L"FourthItemBoxSlot");
	shared_ptr<CItemSlotImage> spFifthItemBoxSlotImage = spLevel->CreateUI<CItemSlotImage>(L"FifthItemBoxSlot");
	shared_ptr<CItemSlotImage> spSixthItemBoxSlotImage = spLevel->CreateUI<CItemSlotImage>(L"SixthItemBoxSlot");
	shared_ptr<CItemSlotImage> spSeventhItemBoxSlotImage = spLevel->CreateUI<CItemSlotImage>(L"SeventhItemBoxSlot");
	shared_ptr<CItemSlotImage> spEightItemBoxSlotImage = spLevel->CreateUI<CItemSlotImage>(L"EighthItemBoxSlot");

	spFirstItemBoxSlotImage->SetPriority(10);
	spSecondItemBoxSlotImage->SetPriority(10);
	spThirdItemBoxSlotImage->SetPriority(10);
	spFourthItemBoxSlotImage->SetPriority(10);
	spFifthItemBoxSlotImage->SetPriority(10);
	spSixthItemBoxSlotImage->SetPriority(10);
	spSeventhItemBoxSlotImage->SetPriority(10);
	spEightItemBoxSlotImage->SetPriority(10);

	spFirstItemBoxSlotImage->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spSecondItemBoxSlotImage->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spThirdItemBoxSlotImage->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spFourthItemBoxSlotImage->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spFifthItemBoxSlotImage->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spSixthItemBoxSlotImage->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spSeventhItemBoxSlotImage->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spEightItemBoxSlotImage->SetItemBelongType(EItemBelongType::ITEM_BOX);

	spFirstItemBoxSlotImage->SetItemSlotType(EItemSlotType::FIRST);
	spSecondItemBoxSlotImage->SetItemSlotType(EItemSlotType::SECOND);
	spThirdItemBoxSlotImage->SetItemSlotType(EItemSlotType::THIRD);
	spFourthItemBoxSlotImage->SetItemSlotType(EItemSlotType::FOURTH);
	spFifthItemBoxSlotImage->SetItemSlotType(EItemSlotType::FIFTH);
	spSixthItemBoxSlotImage->SetItemSlotType(EItemSlotType::SIXTH);
	spSeventhItemBoxSlotImage->SetItemSlotType(EItemSlotType::SEVENTH);
	spEightItemBoxSlotImage->SetItemSlotType(EItemSlotType::EIGHTH);

	m_arrItemSlots[(int32)EItemSlotType::FIRST] = spFirstItemBoxSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::SECOND] = spSecondItemBoxSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::THIRD] = spThirdItemBoxSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::FOURTH] = spFourthItemBoxSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::FIFTH] = spFifthItemBoxSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::SIXTH] = spSixthItemBoxSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::SEVENTH] = spSeventhItemBoxSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::EIGHTH] = spEightItemBoxSlotImage;

	AddUI(L"FirstItemBoxSlot", spFirstItemBoxSlotImage);
	AddUI(L"SecondItemBoxSlot", spSecondItemBoxSlotImage);
	AddUI(L"ThirdItemBoxSlot", spThirdItemBoxSlotImage);
	AddUI(L"FourthItemBoxSlot", spFourthItemBoxSlotImage);
	AddUI(L"FifthItemBoxSlot", spFifthItemBoxSlotImage);
	AddUI(L"SixthItemBoxSlot", spSixthItemBoxSlotImage);
	AddUI(L"SeventhItemBoxSlot", spSeventhItemBoxSlotImage);
	AddUI(L"EighthItemBoxSlot", spEightItemBoxSlotImage);

	// 아이템 버튼 8개
	shared_ptr<CItemButton> spFirstItemBoxButton	= spLevel->CreateUI<CItemButton>(L"FirstItemBoxButton");
	shared_ptr<CItemButton> spSecondItemBoxButton	= spLevel->CreateUI<CItemButton>(L"SecondItemBoxButton");
	shared_ptr<CItemButton> spThirdItemBoxButton	= spLevel->CreateUI<CItemButton>(L"ThirdItemBoxButton");
	shared_ptr<CItemButton> spFourthItemBoxButton	= spLevel->CreateUI<CItemButton>(L"FourthItemBoxButton");
	shared_ptr<CItemButton> spFifthItemBoxButton	= spLevel->CreateUI<CItemButton>(L"FifthItemBoxButton");
	shared_ptr<CItemButton> spSixthItemBoxButton	= spLevel->CreateUI<CItemButton>(L"SixthItemBoxButton");
	shared_ptr<CItemButton> spSeventhItemBoxButton	= spLevel->CreateUI<CItemButton>(L"SeventhItemBoxButton");
	shared_ptr<CItemButton> spEightItemBoxButton	= spLevel->CreateUI<CItemButton>(L"EighthItemBoxButton");

	spFirstItemBoxButton	->SetPriority(5);
	spSecondItemBoxButton	->SetPriority(5);
	spThirdItemBoxButton	->SetPriority(5);
	spFourthItemBoxButton	->SetPriority(5);
	spFifthItemBoxButton	->SetPriority(5);
	spSixthItemBoxButton	->SetPriority(5);
	spSeventhItemBoxButton	->SetPriority(5);
	spEightItemBoxButton	->SetPriority(5);

	spFirstItemBoxButton	->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spSecondItemBoxButton	->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spThirdItemBoxButton	->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spFourthItemBoxButton	->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spFifthItemBoxButton	->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spSixthItemBoxButton	->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spSeventhItemBoxButton	->SetItemBelongType(EItemBelongType::ITEM_BOX);
	spEightItemBoxButton	->SetItemBelongType(EItemBelongType::ITEM_BOX);

	spFirstItemBoxButton	->SetItemSlotType(EItemSlotType::FIRST);
	spSecondItemBoxButton	->SetItemSlotType(EItemSlotType::SECOND);
	spThirdItemBoxButton	->SetItemSlotType(EItemSlotType::THIRD);
	spFourthItemBoxButton	->SetItemSlotType(EItemSlotType::FOURTH);
	spFifthItemBoxButton	->SetItemSlotType(EItemSlotType::FIFTH);
	spSixthItemBoxButton	->SetItemSlotType(EItemSlotType::SIXTH);
	spSeventhItemBoxButton	->SetItemSlotType(EItemSlotType::SEVENTH);
	spEightItemBoxButton	->SetItemSlotType(EItemSlotType::EIGHTH);

	m_arrItemButtons[(int32)EItemSlotType::FIRST] = spFirstItemBoxButton;
	m_arrItemButtons[(int32)EItemSlotType::SECOND] = spSecondItemBoxButton;
	m_arrItemButtons[(int32)EItemSlotType::THIRD] = spThirdItemBoxButton;
	m_arrItemButtons[(int32)EItemSlotType::FOURTH] = spFourthItemBoxButton;
	m_arrItemButtons[(int32)EItemSlotType::FIFTH] = spFifthItemBoxButton;
	m_arrItemButtons[(int32)EItemSlotType::SIXTH] = spSixthItemBoxButton;
	m_arrItemButtons[(int32)EItemSlotType::SEVENTH]= spSeventhItemBoxButton;
	m_arrItemButtons[(int32)EItemSlotType::EIGHTH] = spEightItemBoxButton;

	AddUI(L"FirstItemBoxButton", spFirstItemBoxButton);
	AddUI(L"SecondItemBoxButton", spSecondItemBoxButton);
	AddUI(L"ThirdItemBoxButton", spThirdItemBoxButton);
	AddUI(L"FourthItemBoxButton", spFourthItemBoxButton);
	AddUI(L"FifthItemBoxButton", spFifthItemBoxButton);
	AddUI(L"SixthItemBoxButton", spSixthItemBoxButton);
	AddUI(L"SeventhItemBoxButton", spSeventhItemBoxButton);
	AddUI(L"EighthItemBoxButton", spEightItemBoxButton);

	return S_OK;
}

HRESULT Editor::CItemBoxPanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	// 아이템 박스 패널을 비활성화합니다.
	SetActive(false);

	return S_OK;
}

int32 Editor::CItemBoxPanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CItemBoxPanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	
	return 0;
}

int32 Editor::CItemBoxPanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CItemBoxPanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CItemBoxPanel::Render()
{
	CPanel::Render();
}

void Editor::CItemBoxPanel::Release()
{
	CPanel::Release();
}

void Editor::CItemBoxPanel::SetItem(const std::shared_ptr<CItem>& _spItem, int32 _iSlot)
{
	if (_iSlot < 0 || _iSlot >= m_arrItemSlots.size()) { return; }

	m_arrItemSlots[_iSlot].lock()->SetItem(_spItem);
	m_arrItemButtons[_iSlot].lock()->SetItem(_spItem);
}
