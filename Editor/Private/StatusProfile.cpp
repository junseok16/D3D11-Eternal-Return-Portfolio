#include "pch.h"
#include "StatusProfile.h"

#include "GameManager.h"
#include "Survivor.h"

HRESULT Editor::CStatusProfile::PreInitialize()
{
	m_wpGameManager = CGameManager::GetInstance();

	SetActorRenderType(ERenderType::TRANSLUCENT_OBJECT);
	SetPrimitiveType(EPrimitiveType::POINT);

	SetImageNames
	(
		{
			L"CharProfile_Hyunwoo_S001",
			L"CharProfile_Aya_S001",
			L"CharProfile_Yuki_S003",
			L"CharProfile_Rozzi_S001"
		}
	);

	/*
	switch (m_eSurvivorType)
	{
	case Editor::ESurvivorType::HYUNWOO:SetImageNames({ L"CharProfile_Hyunwoo_S001" });	break;
	case Editor::ESurvivorType::AYA:	SetImageNames({ L"CharProfile_Aya_S001" });		break;
	case Editor::ESurvivorType::YUKI:	SetImageNames({ L"CharProfile_Yuki_S003" });	break;
	case Editor::ESurvivorType::ROZZI:	SetImageNames({ L"CharProfile_Rozzi_S001" });	break;
	default: CHECKF(false, L"Survivor type is not designated.");						break;
	}
	*/

	return CImage::PreInitialize();
}

HRESULT Editor::CStatusProfile::Initialize()
{
	SetPivot({ 228.0f, 612.0f });
	SetWidth(82.0f);
	SetHeight(102.0f);
	return CImage::Initialize();
}

HRESULT Editor::CStatusProfile::PostInitialize()
{
	if (FAILED(CImage::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CStatusProfile::BeginPlay()
{
	if (FAILED(CImage::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CStatusProfile::PreTick(float _fDeltaSeconds)
{
	switch (CImage::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CStatusProfile::Tick(float _fDeltaSeconds)
{
	switch (CImage::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	switch (m_wpGameManager.lock()->GetSurvivor()->GetSurvivorType())
	{
	case ESurvivorType::HYUNWOO:
		SetTextureIndex(0);
		break;

	case ESurvivorType::AYA:
		SetTextureIndex(1);
		break;

	default:
		break;
	}

	return 0;
}

int32 Editor::CStatusProfile::PostTick(float _fDeltaSeconds)
{
	switch (CImage::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CStatusProfile::EndPlay()
{
	if (FAILED(CImage::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CStatusProfile::Render()
{
	CImage::Render();
}

void Editor::CStatusProfile::Release()
{
	CImage::Release();
}
