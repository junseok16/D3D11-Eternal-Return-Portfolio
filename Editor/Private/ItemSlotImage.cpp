#include "pch.h"
#include "ItemSlotImage.h"

#include "Item.h"

HRESULT Editor::CItemSlotImage::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames
	(
		{
			L"Img_Main_ItemSlot",
			L"Ico_ItemGradebg_01",
			L"Ico_ItemGradebg_02",
			L"Ico_ItemGradebg_03",
			L"Ico_ItemGradebg_04",
			L"Ico_ItemGradebg_05",
			L"Ico_ItemGradebg_06",
		}
	);

	return CImage::PreInitialize();
}

HRESULT Editor::CItemSlotImage::Initialize()
{
	SetWidth(43.0f);
	SetHeight(26.0f);

	switch (m_eItemBelongType)
	{
	case Editor::EItemBelongType::CRAFT:
	{
		SetWidth(43.0f);
		SetHeight(26.0f);

		switch (m_eItemSlotType)
		{
		case Editor::EItemSlotType::FIRST:	SetPivot({ 824.0f, 608.0f });	break;
		case Editor::EItemSlotType::SECOND:	SetPivot({ 871.0f, 608.0f });	break;
		case Editor::EItemSlotType::THIRD:	SetPivot({ 918.0f, 608.0f });	break;
		case Editor::EItemSlotType::FOURTH:	SetPivot({ 965.0f, 608.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Editor::EItemBelongType::INVENTORY:
	{
		switch (m_eItemSlotType)
		{
		case Editor::EItemSlotType::FIRST:	SetPivot({ 777.0f, 651.0f });	break;
		case Editor::EItemSlotType::SECOND:	SetPivot({ 824.0f, 651.0f });	break;
		case Editor::EItemSlotType::THIRD:	SetPivot({ 871.0f, 651.0f });	break;
		case Editor::EItemSlotType::FOURTH:	SetPivot({ 918.0f, 651.0f });	break;
		case Editor::EItemSlotType::FIFTH:	SetPivot({ 965.0f, 651.0f });	break;
		case Editor::EItemSlotType::SIXTH:	SetPivot({ 777.0f, 684.0f });	break;
		case Editor::EItemSlotType::SEVENTH:SetPivot({ 824.0f, 684.0f });	break;
		case Editor::EItemSlotType::EIGHTH:	SetPivot({ 871.0f, 684.0f });	break;
		case Editor::EItemSlotType::NINETH:	SetPivot({ 918.0f, 684.0f });	break;
		case Editor::EItemSlotType::TENTH:	SetPivot({ 965.0f, 684.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Editor::EItemBelongType::ITEM_BOX:
	{
		switch (m_eItemSlotType)
		{
		case Editor::EItemSlotType::FIRST:	SetPivot({ 878.0f, 518.0f });	break;
		case Editor::EItemSlotType::SECOND:	SetPivot({ 930.0f, 518.0f });	break;
		case Editor::EItemSlotType::THIRD:	SetPivot({ 982.0f, 518.0f });	break;
		case Editor::EItemSlotType::FOURTH:	SetPivot({ 1034.0f, 518.0f });	break;
		case Editor::EItemSlotType::FIFTH:	SetPivot({ 878.0f, 554.0f });	break;
		case Editor::EItemSlotType::SIXTH:	SetPivot({ 930.0f, 554.0f });	break;
		case Editor::EItemSlotType::SEVENTH:SetPivot({ 982.0f, 554.0f });	break;
		case Editor::EItemSlotType::EIGHTH:	SetPivot({ 1034.0f, 554.0f });	break;
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

	return CImage::Initialize();
}

HRESULT Editor::CItemSlotImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CItemSlotImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CItemSlotImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CItemSlotImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// 아이템 슬롯에 아이템이 있는 경우
	if (!m_wpItem.expired())
	{
		m_bActive = true;
		SetTextureIndex(static_cast<int32>(m_wpItem.lock()->GetItemLevel()));
	}
	// 아이템 슬롯에 아이템이 없는 경우
	else
	{
		if (m_eItemBelongType == EItemBelongType::CRAFT)
		{
			m_bActive = false;
		}
		else
		{
			SetTextureIndex(0);
		}
	}

	return 0;
}

int32 Editor::CItemSlotImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CItemSlotImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CItemSlotImage::Render()
{
	CImage::Render();
}

void Editor::CItemSlotImage::Release()
{
	CImage::Release();
}
