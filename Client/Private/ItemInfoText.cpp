#include "pch.h"
#include "ItemInfoText.h"

HRESULT Client::CItemInfoText::PreInitialize()
{
	switch (m_eItemInfoType)
	{
	case Client::EItemInfoType::NAME:
		SetTextPosition({ 797.0f, 433.0f });
		SetTextScale(0.45f);
		SetText(L"이름");
		break;

	case Client::EItemInfoType::LEVEL:
		SetTextPosition({ 797.0f, 458.0f });
		SetTextScale(0.28f);
		SetText(L"레벨");
		break;

	case Client::EItemInfoType::CATEGORY:
		SetTextPosition({ 797.0f, 472.0f });
		SetTextScale(0.28f);
		SetText(L"카테고리");
		SetTextColor({ 0.8f, 0.8f, 0.8f, 1.0f });
		break;

	case Client::EItemInfoType::EFFECT:
		SetTextPosition({ 776.0f, 518.0f });
		SetTextScale(0.33f);
		SetText(L"효과");
		SetTextColor({ 0.8f, 0.8f, 0.8f, 1.0f });
		break;

	case Client::EItemInfoType::EXPLANATION:
		SetTextPosition({ 776.0f, 538.0f });
		SetTextScale(0.33f);
		SetText(L"설명");
		SetTextColor({ 0.8f, 0.8f, 0.8f, 1.0f });
		break;

	default:
		break;
	}

	SetActorRenderType(ERenderType::OPAQUE_USER_INTERFACE);
	return CText::PreInitialize();
}

HRESULT Client::CItemInfoText::Initialize()
{
	return CText::Initialize();
}

HRESULT Client::CItemInfoText::PostInitialize()
{
	return CText::PostInitialize();
}

HRESULT Client::CItemInfoText::BeginPlay()
{
	return CText::BeginPlay();
}

int32 Client::CItemInfoText::PreTick(float _fDeltaSeconds)
{
	switch (CText::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoText::Tick(float _fDeltaSeconds)
{
	switch (CText::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CItemInfoText::PostTick(float _fDeltaSeconds)
{
	switch (CText::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CItemInfoText::EndPlay()
{
	if (FAILED(CText::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemInfoText::Render()
{
	CText::Render();
}

void Client::CItemInfoText::Release()
{
	CText::Release();
}
