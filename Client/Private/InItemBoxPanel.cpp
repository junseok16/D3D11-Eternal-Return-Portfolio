#include "pch.h"
#include "InItemBoxPanel.h"

#include "InItemBoxBackground.h"
#include "InItemBoxImage.h"

#include "World.h"
#include "Level.h"

#include "ItemBox.h"

#include "UIManager.h"

std::shared_ptr<CInItemBoxPanel> Client::CInItemBoxPanel::Create(const std::shared_ptr<CItemBox>& _spPanelOwner)
{
	const std::shared_ptr<CInItemBoxPanel> spInItemBoxPanel = make_shared<CInItemBoxPanel>();
	spInItemBoxPanel->Initialize(_spPanelOwner);
	
	CUIManager::GetInstance()->AddInItemBoxPanel(spInItemBoxPanel);
	return spInItemBoxPanel;
}

void Client::CInItemBoxPanel::Initialize(const std::shared_ptr<CItemBox>& _spPanelOwner)
{
	m_wpPanelOwner = _spPanelOwner;

	shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();

	wstring wstrKey = _spPanelOwner->GetActorName() + L"InItemBoxBackground";
	m_wpInItemBoxBackground = spLevel->CreateUI<CInItemBoxBackground>(wstrKey);
	m_wpInItemBoxBackground.lock()->SetPriority(30);
	m_wpInItemBoxBackground.lock()->SetItemBox(_spPanelOwner);
	AddUI(wstrKey, m_wpInItemBoxBackground.lock());
}

HRESULT Client::CInItemBoxPanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CInItemBoxPanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CInItemBoxPanel::PostInitialize()
{
	if (FAILED(CPanel::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CInItemBoxPanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CInItemBoxPanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CInItemBoxPanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CInItemBoxPanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CInItemBoxPanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CInItemBoxPanel::Render()
{
	CPanel::Render();
}

void Client::CInItemBoxPanel::Release()
{
	CPanel::Release();
}
