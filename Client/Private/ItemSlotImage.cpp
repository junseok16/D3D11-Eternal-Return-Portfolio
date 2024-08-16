#include "pch.h"
#include "ItemSlotImage.h"

#include "Item.h"

HRESULT Client::CItemSlotImage::PreInitialize()
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

HRESULT Client::CItemSlotImage::Initialize()
{
	SetWidth(43.0f);
	SetHeight(26.0f);

	switch (m_eItemBelongType)
	{
	case Client::EItemBelongType::CRAFT:
	{
		SetWidth(43.0f);
		SetHeight(26.0f);

		switch (m_eItemSlotType)
		{
		case Client::EItemSlotType::FIRST:	SetPivot({ 824.0f, 608.0f });	break;
		case Client::EItemSlotType::SECOND:	SetPivot({ 871.0f, 608.0f });	break;
		case Client::EItemSlotType::THIRD:	SetPivot({ 918.0f, 608.0f });	break;
		case Client::EItemSlotType::FOURTH:	SetPivot({ 965.0f, 608.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Client::EItemBelongType::INVENTORY:
	{
		switch (m_eItemSlotType)
		{
		case Client::EItemSlotType::FIRST:	SetPivot({ 777.0f, 651.0f });	break;
		case Client::EItemSlotType::SECOND:	SetPivot({ 824.0f, 651.0f });	break;
		case Client::EItemSlotType::THIRD:	SetPivot({ 871.0f, 651.0f });	break;
		case Client::EItemSlotType::FOURTH:	SetPivot({ 918.0f, 651.0f });	break;
		case Client::EItemSlotType::FIFTH:	SetPivot({ 965.0f, 651.0f });	break;
		case Client::EItemSlotType::SIXTH:	SetPivot({ 777.0f, 684.0f });	break;
		case Client::EItemSlotType::SEVENTH:SetPivot({ 824.0f, 684.0f });	break;
		case Client::EItemSlotType::EIGHTH:	SetPivot({ 871.0f, 684.0f });	break;
		case Client::EItemSlotType::NINETH:	SetPivot({ 918.0f, 684.0f });	break;
		case Client::EItemSlotType::TENTH:	SetPivot({ 965.0f, 684.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Client::EItemBelongType::ITEM_BOX:
	{
		switch (m_eItemSlotType)
		{
		case Client::EItemSlotType::FIRST:	SetPivot({ 776.0f, 318.0f });	break;
		case Client::EItemSlotType::SECOND:	SetPivot({ 828.0f, 318.0f });	break;
		case Client::EItemSlotType::THIRD:	SetPivot({ 880.0f, 318.0f });	break;
		case Client::EItemSlotType::FOURTH:	SetPivot({ 932.0f, 318.0f });	break;
		case Client::EItemSlotType::FIFTH:	SetPivot({ 776.0f, 354.0f });	break;
		case Client::EItemSlotType::SIXTH:	SetPivot({ 828.0f, 354.0f });	break;
		case Client::EItemSlotType::SEVENTH:SetPivot({ 880.0f, 354.0f });	break;
		case Client::EItemSlotType::EIGHTH:	SetPivot({ 932.0f, 354.0f });	break;
		default: CHECKF(false, L"Item slot type is not designated.");		break;
		}
	}
	break;

	case Client::EItemBelongType::DEAD_BODY:
	{

	}
	break;

	default:
		CHECKF(false, L"Item belong type is not designated.")
		break;
	}

	return CImage::Initialize();
}

HRESULT Client::CItemSlotImage::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CItemSlotImage::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CItemSlotImage::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemSlotImage::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// ������ ���Կ� �������� �ִ� ���
	if (!m_wpItem.expired())
	{
		m_bActive = true;
		SetTextureIndex(static_cast<int32>(m_wpItem.lock()->GetItemLevel()));
	}
	// ������ ���Կ� �������� ���� ���
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

int32 Client::CItemSlotImage::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemSlotImage::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemSlotImage::Render()
{
	CImage::Render();
}

void Client::CItemSlotImage::Release()
{
	CImage::Release();
}
