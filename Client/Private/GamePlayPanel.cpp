#include "pch.h"
#include "GamePlayPanel.h"

#include "GamePlayBackground.h"
#include "GamePlayTimeText.h"
#include "GamePlayDayNightImage.h"
#include "GamePlayDayNightText.h"

#include "World.h"
#include "Level.h"

HRESULT Client::CGamePlayPanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CGamePlayPanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CGamePlayPanel::PostInitialize()
{
	if (FAILED(CPanel::PostInitialize())) { return E_FAIL; }

	shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();

	// 패널 1개
	shared_ptr<CGamePlayBackground> spGamePlayBackground = spLevel->CreateUI<CGamePlayBackground>(L"GamePlayBackground");
	spGamePlayBackground->SetPriority(20);
	AddUI(L"GamePlayBackground", spGamePlayBackground);

	// 시간 텍스트 1개
	shared_ptr<CGamePlayTimeText> spGamePlayTimeText = spLevel->CreateUI<CGamePlayTimeText>(L"GamePlayTimeText");
	spGamePlayTimeText->SetFontName(L"EternalReturn");
	spGamePlayTimeText->SetPriority(5);
	AddUI(L"GamePlayTimeText", spGamePlayTimeText);

	// 해달 이미지 1개
	shared_ptr<CGamePlayDayNightImage> spGamePlayDayNightImage = spLevel->CreateUI<CGamePlayDayNightImage>(L"GamePlayDayNightImage");
	spGamePlayDayNightImage->SetPriority(10);
	AddUI(L"GamePlayDayNightImage", spGamePlayDayNightImage);

	// 일차 텍스트 1개
	shared_ptr<CGamePlayDayNightText> spGamePlayDayNightText = spLevel->CreateUI<CGamePlayDayNightText>(L"GamePlayDayNightText");
	spGamePlayDayNightText->SetFontName(L"KBIZM");
	spGamePlayDayNightText->SetPriority(5);
	AddUI(L"GamePlayDayNightText", spGamePlayDayNightText);

	return S_OK;
}

HRESULT Client::CGamePlayPanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CGamePlayPanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CGamePlayPanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CGamePlayPanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CGamePlayPanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CGamePlayPanel::Render()
{
	CPanel::Render();
}

void Client::CGamePlayPanel::Release()
{
	CPanel::Release();
}
