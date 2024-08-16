#include "pch.h"
#include "ItemPanel.h"

#include "ItemBackground.h"
#include "ItemSlotImage.h"
#include "ItemButton.h"
#include "CraftImage.h"

#include "World.h"
#include "Level.h"

HRESULT Client::CItemPanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemPanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemPanel::PostInitialize()
{
	if (FAILED(CPanel::PostInitialize())) { return E_FAIL; }

	shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();

	// 제작 이미지 1개
	shared_ptr<CCraftImage> spCraftImage = spLevel->CreateUI<CCraftImage>(L"CraftImage");
	spCraftImage->SetPriority(20);
	AddUI(L"CraftImage", spCraftImage);
	
	// 제작 슬롯 4개
	shared_ptr<CItemSlotImage> spFirstCraftSlotImage = spLevel->CreateUI<CItemSlotImage>(L"FirstCraftSlot");
	shared_ptr<CItemSlotImage> spSecondCraftSlotImage = spLevel->CreateUI<CItemSlotImage>(L"SecondCraftSlot");
	shared_ptr<CItemSlotImage> spThirdCraftSlotImage = spLevel->CreateUI<CItemSlotImage>(L"ThirdCraftSlot");
	shared_ptr<CItemSlotImage> spFourthCraftSlotImage = spLevel->CreateUI<CItemSlotImage>(L"FourthCraftSlot");

	spFirstCraftSlotImage->SetPriority(10);
	spSecondCraftSlotImage->SetPriority(10);
	spThirdCraftSlotImage->SetPriority(10);
	spFourthCraftSlotImage->SetPriority(10);

	spFirstCraftSlotImage->SetItemSlotType(EItemSlotType::FIRST);
	spSecondCraftSlotImage->SetItemSlotType(EItemSlotType::SECOND);
	spThirdCraftSlotImage->SetItemSlotType(EItemSlotType::THIRD);
	spFourthCraftSlotImage->SetItemSlotType(EItemSlotType::FOURTH);

	spFirstCraftSlotImage->SetItemBelongType(EItemBelongType::CRAFT);
	spSecondCraftSlotImage->SetItemBelongType(EItemBelongType::CRAFT);
	spThirdCraftSlotImage->SetItemBelongType(EItemBelongType::CRAFT);
	spFourthCraftSlotImage->SetItemBelongType(EItemBelongType::CRAFT);

	m_arrCraftSlots[(int32)EItemSlotType::FIRST] = spFirstCraftSlotImage;
	m_arrCraftSlots[(int32)EItemSlotType::SECOND] = spSecondCraftSlotImage;
	m_arrCraftSlots[(int32)EItemSlotType::THIRD] = spThirdCraftSlotImage;
	m_arrCraftSlots[(int32)EItemSlotType::FOURTH] = spFourthCraftSlotImage;

	AddUI(L"FirstCraftSlot", spFirstCraftSlotImage);
	AddUI(L"SecondCraftSlot", spSecondCraftSlotImage);
	AddUI(L"ThirdCraftSlot", spThirdCraftSlotImage);
	AddUI(L"FourthCraftSlot", spFourthCraftSlotImage);

	// 제작 버튼 4개
	shared_ptr<CItemButton> spFirstCraftButton = spLevel->CreateUI<CItemButton>(L"FirstCraftButton");
	shared_ptr<CItemButton> spSecondCraftButton = spLevel->CreateUI<CItemButton>(L"SecondCraftButton");
	shared_ptr<CItemButton> spThirdCraftButton = spLevel->CreateUI<CItemButton>(L"ThirdCraftButton");
	shared_ptr<CItemButton> spFourthCraftButton = spLevel->CreateUI<CItemButton>(L"FourthCraftButton");

	spFirstCraftButton->SetPriority(5);
	spSecondCraftButton->SetPriority(5);
	spThirdCraftButton->SetPriority(5);
	spFourthCraftButton->SetPriority(5);

	spFirstCraftButton->SetItemBelongType(EItemBelongType::CRAFT);
	spSecondCraftButton->SetItemBelongType(EItemBelongType::CRAFT);
	spThirdCraftButton->SetItemBelongType(EItemBelongType::CRAFT);
	spFourthCraftButton->SetItemBelongType(EItemBelongType::CRAFT);

	spFirstCraftButton->SetItemSlotType(EItemSlotType::FIRST);
	spSecondCraftButton->SetItemSlotType(EItemSlotType::SECOND);
	spThirdCraftButton->SetItemSlotType(EItemSlotType::THIRD);
	spFourthCraftButton->SetItemSlotType(EItemSlotType::FOURTH);

	m_arrCraftButtons[(int32)EItemSlotType::FIRST] = spFirstCraftButton;
	m_arrCraftButtons[(int32)EItemSlotType::SECOND] = spSecondCraftButton;
	m_arrCraftButtons[(int32)EItemSlotType::THIRD] = spThirdCraftButton;
	m_arrCraftButtons[(int32)EItemSlotType::FOURTH] = spFourthCraftButton;

	AddUI(L"FirstCraftButton", spFirstCraftButton);
	AddUI(L"SecondCraftButton", spSecondCraftButton);
	AddUI(L"ThirdCraftButton", spThirdCraftButton);
	AddUI(L"FourthCraftButton", spFourthCraftButton);




	// 패널 1개
	shared_ptr<CItemBackground> spItemBackground = spLevel->CreateUI<CItemBackground>(L"ItemBackground");
	spItemBackground->SetPriority(20);
	AddUI(L"ItemBackground", spItemBackground);

	// 빈 슬롯 10개
	shared_ptr<CItemSlotImage> spFirstItemSlotImage		= spLevel->CreateUI<CItemSlotImage>(L"FirstItemSlot");
	shared_ptr<CItemSlotImage> spSecondItemSlotImage	= spLevel->CreateUI<CItemSlotImage>(L"SecondItemSlot");
	shared_ptr<CItemSlotImage> spThirdItemSlotImage		= spLevel->CreateUI<CItemSlotImage>(L"ThirdItemSlot");
	shared_ptr<CItemSlotImage> spFourthItemSlotImage	= spLevel->CreateUI<CItemSlotImage>(L"FourthItemSlot");
	shared_ptr<CItemSlotImage> spFifthItemSlotImage		= spLevel->CreateUI<CItemSlotImage>(L"FifthItemSlot");
	shared_ptr<CItemSlotImage> spSixthItemSlotImage		= spLevel->CreateUI<CItemSlotImage>(L"SixthItemSlot");
	shared_ptr<CItemSlotImage> spSeventhItemSlotImage	= spLevel->CreateUI<CItemSlotImage>(L"SeventhItemSlot");
	shared_ptr<CItemSlotImage> spEighthItemSlotImage	= spLevel->CreateUI<CItemSlotImage>(L"EighthItemSlot");
	shared_ptr<CItemSlotImage> spNinethItemSlotImage	= spLevel->CreateUI<CItemSlotImage>(L"NinethItemSlot");
	shared_ptr<CItemSlotImage> spTenthItemSlotImage		= spLevel->CreateUI<CItemSlotImage>(L"TenthItemSlot");

	spFirstItemSlotImage->SetPriority(10);
	spSecondItemSlotImage->SetPriority(10);
	spThirdItemSlotImage->SetPriority(10);
	spFourthItemSlotImage->SetPriority(10);
	spFifthItemSlotImage->SetPriority(10);
	spSixthItemSlotImage->SetPriority(10);
	spSeventhItemSlotImage->SetPriority(10);
	spEighthItemSlotImage->SetPriority(10);
	spNinethItemSlotImage->SetPriority(10);
	spTenthItemSlotImage->SetPriority(10);

	spFirstItemSlotImage->SetItemSlotType(EItemSlotType::FIRST);
	spSecondItemSlotImage->SetItemSlotType(EItemSlotType::SECOND);
	spThirdItemSlotImage->SetItemSlotType(EItemSlotType::THIRD);
	spFourthItemSlotImage->SetItemSlotType(EItemSlotType::FOURTH);
	spFifthItemSlotImage->SetItemSlotType(EItemSlotType::FIFTH);
	spSixthItemSlotImage->SetItemSlotType(EItemSlotType::SIXTH);
	spSeventhItemSlotImage->SetItemSlotType(EItemSlotType::SEVENTH);
	spEighthItemSlotImage->SetItemSlotType(EItemSlotType::EIGHTH);
	spNinethItemSlotImage->SetItemSlotType(EItemSlotType::NINETH);
	spTenthItemSlotImage->SetItemSlotType(EItemSlotType::TENTH);

	spFirstItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spSecondItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spThirdItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spFourthItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spFifthItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spSixthItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spSeventhItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spEighthItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spNinethItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);
	spTenthItemSlotImage->SetItemBelongType(EItemBelongType::INVENTORY);

	m_arrItemSlots[(int32)EItemSlotType::FIRST]		= spFirstItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::SECOND]	= spSecondItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::THIRD]		= spThirdItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::FOURTH]	= spFourthItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::FIFTH]		= spFifthItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::SIXTH]		= spSixthItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::SEVENTH]	= spSeventhItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::EIGHTH]	= spEighthItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::NINETH]	= spNinethItemSlotImage;
	m_arrItemSlots[(int32)EItemSlotType::TENTH]		= spTenthItemSlotImage;

	AddUI(L"FirstItemSlot",		spFirstItemSlotImage);
	AddUI(L"SecondItemSlot",	spSecondItemSlotImage);
	AddUI(L"ThirdItemSlot",		spThirdItemSlotImage);
	AddUI(L"FourthItemSlot",	spFourthItemSlotImage);
	AddUI(L"FifthItemSlot",		spFifthItemSlotImage);
	AddUI(L"SixthItemSlot",		spSixthItemSlotImage);
	AddUI(L"SeventhItemSlot",	spSeventhItemSlotImage);
	AddUI(L"EighthItemSlot",	spEighthItemSlotImage);
	AddUI(L"NinethItemSlot",	spNinethItemSlotImage);
	AddUI(L"TenthItemSlot",		spTenthItemSlotImage);

	// 아이템 버튼 10개
	shared_ptr<CItemButton> spFirstItemButton = spLevel->CreateUI<CItemButton>(L"FirstItemButton");
	shared_ptr<CItemButton> spSecondItemButton = spLevel->CreateUI<CItemButton>(L"SecondItemButton");
	shared_ptr<CItemButton> spThirdItemButton = spLevel->CreateUI<CItemButton>(L"ThirdItemButton");
	shared_ptr<CItemButton> spFourthItemButton = spLevel->CreateUI<CItemButton>(L"FourthItemButton");
	shared_ptr<CItemButton> spFifthItemButton = spLevel->CreateUI<CItemButton>(L"FifthItemButton");
	shared_ptr<CItemButton> spSixthItemButton = spLevel->CreateUI<CItemButton>(L"SixthItemButton");
	shared_ptr<CItemButton> spSeventhItemButton = spLevel->CreateUI<CItemButton>(L"SeventhItemButton");
	shared_ptr<CItemButton> spEightItemButton = spLevel->CreateUI<CItemButton>(L"EighthItemButton");
	shared_ptr<CItemButton> spNinethItemButton = spLevel->CreateUI<CItemButton>(L"NinethItemButton");
	shared_ptr<CItemButton> spTenthItemButton = spLevel->CreateUI<CItemButton>(L"TenthItemButton");

	spFirstItemButton->SetPriority(5);
	spSecondItemButton->SetPriority(5);
	spThirdItemButton->SetPriority(5);
	spFourthItemButton->SetPriority(5);
	spFifthItemButton->SetPriority(5);
	spSixthItemButton->SetPriority(5);
	spSeventhItemButton->SetPriority(5);
	spEightItemButton->SetPriority(5);
	spNinethItemButton->SetPriority(5);
	spTenthItemButton->SetPriority(5);

	spFirstItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spSecondItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spThirdItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spFourthItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spFifthItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spSixthItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spSeventhItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spEightItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spNinethItemButton->SetItemBelongType(EItemBelongType::INVENTORY);
	spTenthItemButton->SetItemBelongType(EItemBelongType::INVENTORY);

	spFirstItemButton->SetItemSlotType(EItemSlotType::FIRST);
	spSecondItemButton->SetItemSlotType(EItemSlotType::SECOND);
	spThirdItemButton->SetItemSlotType(EItemSlotType::THIRD);
	spFourthItemButton->SetItemSlotType(EItemSlotType::FOURTH);
	spFifthItemButton->SetItemSlotType(EItemSlotType::FIFTH);
	spSixthItemButton->SetItemSlotType(EItemSlotType::SIXTH);
	spSeventhItemButton->SetItemSlotType(EItemSlotType::SEVENTH);
	spEightItemButton->SetItemSlotType(EItemSlotType::EIGHTH);
	spNinethItemButton->SetItemSlotType(EItemSlotType::NINETH);
	spTenthItemButton->SetItemSlotType(EItemSlotType::TENTH);

	m_arrItemButtons[(int32)EItemSlotType::FIRST] = spFirstItemButton;
	m_arrItemButtons[(int32)EItemSlotType::SECOND] = spSecondItemButton;
	m_arrItemButtons[(int32)EItemSlotType::THIRD] = spThirdItemButton;
	m_arrItemButtons[(int32)EItemSlotType::FOURTH] = spFourthItemButton;
	m_arrItemButtons[(int32)EItemSlotType::FIFTH] = spFifthItemButton;
	m_arrItemButtons[(int32)EItemSlotType::SIXTH] = spSixthItemButton;
	m_arrItemButtons[(int32)EItemSlotType::SEVENTH] = spSeventhItemButton;
	m_arrItemButtons[(int32)EItemSlotType::EIGHTH] = spEightItemButton;
	m_arrItemButtons[(int32)EItemSlotType::NINETH] = spNinethItemButton;
	m_arrItemButtons[(int32)EItemSlotType::TENTH] = spTenthItemButton;

	AddUI(L"FirstItemButton", spFirstItemButton);
	AddUI(L"SecondItemButton", spSecondItemButton);
	AddUI(L"ThirdItemButton", spThirdItemButton);
	AddUI(L"FourthItemButton", spFourthItemButton);
	AddUI(L"FifthItemButton", spFifthItemButton);
	AddUI(L"SixthItemButton", spSixthItemButton);
	AddUI(L"SeventhItemButton", spSeventhItemButton);
	AddUI(L"EighthItemButton", spEightItemButton);
	AddUI(L"NinethItemButton", spNinethItemButton);
	AddUI(L"TenthItemButton", spTenthItemButton);

	return S_OK;
}

HRESULT Client::CItemPanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CItemPanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemPanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemPanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemPanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemPanel::Render()
{
	CPanel::Render();
}

void Client::CItemPanel::Release()
{
	CPanel::Release();
}

void Client::CItemPanel::SetItem(const std::shared_ptr<CItem>& _spItem, int32 _iSlot)
{
	if (_iSlot < 0 || _iSlot >= m_arrItemSlots.size()) { return; }

	m_arrItemSlots[_iSlot].lock()->SetItem(_spItem);
	m_arrItemButtons[_iSlot].lock()->SetItem(_spItem);
}

void Client::CItemPanel::SetCraft(const std::shared_ptr<CItem>& _spItem, int32 _iSlot)
{
	if (_iSlot < 0 || _iSlot >= m_arrCraftSlots.size()) { return; }

	m_arrCraftSlots[_iSlot].lock()->SetItem(_spItem);
	m_arrCraftButtons[_iSlot].lock()->SetItem(_spItem);
}
