#include "pch.h"
#include "EquipSlotImage.h"

#include "Item.h"

HRESULT Client::CEquipSlotImage::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	SetPrimitiveType(EPrimitiveType::POINT);
	SetImageNames
	(
		{
			L"Img_EmptySlot_Bg",
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

HRESULT Client::CEquipSlotImage::Initialize()
{
	SetWidth(36.0f);
	SetHeight(23.0f);

	switch (m_eEquipSlotType)
	{
	case Client::EEquipSlotType::WEAPON:SetPivot({ 326.0f, 663.0f });	break;
	case Client::EEquipSlotType::ARMOR:	SetPivot({ 366.0f, 663.0f });	break;
	case Client::EEquipSlotType::HEAD:	SetPivot({ 406.0f, 663.0f });	break;
	case Client::EEquipSlotType::ARM:	SetPivot({ 326.0f, 692.0f });	break;
	case Client::EEquipSlotType::LEG:	SetPivot({ 366.0f, 692.0f });	break;
	case Client::EEquipSlotType::DECO:	SetPivot({ 406.0f, 692.0f });	break;
	default: CHECKF(false, L"Equip slot type is not designated.")		break;
	}

	return CImage::Initialize();
}

HRESULT Client::CEquipSlotImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CEquipSlotImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CEquipSlotImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CEquipSlotImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// 아이템 슬롯에 아이템이 있는 경우
	if (m_spItem)
	{
		SetTextureIndex(static_cast<int32>(m_spItem->GetItemLevel()));
	}
	// 아이템 슬롯에 아이템이 없는 경우
	else
	{
		SetTextureIndex(0);
	}

	return 0;
}

int32 Client::CEquipSlotImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CEquipSlotImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CEquipSlotImage::Render()
{
	CImage::Render();
}

void Client::CEquipSlotImage::Release()
{
	CImage::Release();
}
