#include "pch.h"
#include "GamePlayPanel.h"

#include "GamePlayBackground.h"
#include "GamePlayTimeText.h"

#include "World.h"
#include "Level.h"

HRESULT Editor::CGamePlayPanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CGamePlayPanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CGamePlayPanel::PostInitialize()
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

	return S_OK;
}

HRESULT Editor::CGamePlayPanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CGamePlayPanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CGamePlayPanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CGamePlayPanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CGamePlayPanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CGamePlayPanel::Render()
{
	CPanel::Render();
}

void Editor::CGamePlayPanel::Release()
{
	CPanel::Release();
}
