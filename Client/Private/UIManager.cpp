#include "pch.h"
#include "UIManager.h"

// user interface
#include "SkillPanel.h"
#include "StatusPanel.h"
#include "ItemPanel.h"
#include "ItemBoxPanel.h"
#include "GamePlayPanel.h"
#include "ItemInfoPanel.h"
#include "InItemBoxPanel.h"
#include "InGamePanel.h"

#include "World.h"
#include "Level.h"

IMPLEMENT_SINGLETON(CUIManager)

HRESULT Client::CUIManager::Initialize()
{
	return S_OK;
}

int32 Client::CUIManager::Tick(float _fDeltaSeconds)
{
	return 0;
}

void Client::CUIManager::Release()
{
	for (auto& spInItemBoxPanel : m_vecInItemBoxPanels)
	{
		spInItemBoxPanel->Release();
		spInItemBoxPanel = nullptr;
	}
	m_vecInItemBoxPanels.clear();

	for (auto& spInGamePanel : m_vecInGamePanels)
	{
		spInGamePanel->Release();
		spInGamePanel = nullptr;
	}
	m_vecInGamePanels.clear();

	// 싱글턴 매니저를 메모리에서 해제합니다.
	m_spInstance = nullptr;
}

void Client::CUIManager::LoadUserInterface()
{
	shared_ptr<CLevel> spCurLevel = CWorld::GetInstance()->GetCurLevel();

	m_wpGamePlayPanel	= spCurLevel->CreateActor<CGamePlayPanel>(L"GamePlayPanel");
	m_wpItemInfoPanel	= spCurLevel->CreateActor<CItemInfoPanel>(L"ItemInfoPanel");
	m_wpSkillPanel		= spCurLevel->CreateActor<CSkillPanel>(L"SkillPanel");
	m_wpStatusPanel		= spCurLevel->CreateActor<CStatusPanel>(L"StatusPanel");
	m_wpItemPanel		= spCurLevel->CreateActor<CItemPanel>(L"ItemPanel");
	m_wpItemBoxPanel	= spCurLevel->CreateActor<CItemBoxPanel>(L"ItemBoxPanel");
}
