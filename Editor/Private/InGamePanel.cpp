#include "pch.h"
#include "InGamePanel.h"

#include "InHPBarSlider.h"
#include "InRetreatBarSlider.h"
#include "InLevelImage.h"

#include "World.h"
#include "Level.h"

std::shared_ptr<CInGamePanel> Editor::CInGamePanel::Create
(
	const std::shared_ptr<CActor>& _spPanelOwner,
	EEnemyType _eEnemyType
)
{
	const std::shared_ptr<CInGamePanel> spInGamePanel = make_shared<CInGamePanel>();
	spInGamePanel->Initialize(_spPanelOwner, _eEnemyType);
	return spInGamePanel;
}

void Editor::CInGamePanel::Initialize(const std::shared_ptr<CActor>& _spPanelOwner, EEnemyType _eEnemyType)
{
	m_wpPanelOwner = _spPanelOwner;
	m_eEnemyType = _eEnemyType;

	shared_ptr<CLevel> spLevel = CWorld::GetInstance()->GetCurLevel();

	// WicklineInHPBarSlider
	wstring wstrKey = _spPanelOwner->GetActorName() + L"InHPBarSlider";
	m_wpInHPBarSlider = spLevel->CreateUI<CInHPBarSlider>(wstrKey);
	m_wpInHPBarSlider.lock()->SetPriority(30);
	m_wpInHPBarSlider.lock()->SetEnemyType(_eEnemyType);
	m_wpInHPBarSlider.lock()->SetActor(_spPanelOwner);
	AddUI(wstrKey, m_wpInHPBarSlider.lock());

	/*
	m_wpInRetreatBarSlider = spLevel->CreateUI<CInRetreatBarSlider>(L"InRetreatBarSlider");
	m_wpInRetreatBarSlider.lock()->SetPriority(30);
	m_wpInRetreatBarSlider.lock()->SetActor(m_wpOwnerActor.lock());
	AddUI(L"InRetreatBarSlider", m_wpInRetreatBarSlider.lock());

	m_wpInLevelImage = spLevel->CreateUI<CInLevelImage>(L"InlevelImage");
	m_wpInLevelImage.lock()->SetPriority(25);
	AddUI(L"InlevelImage", m_wpInLevelImage.lock());
	*/
}

HRESULT Editor::CInGamePanel::PreInitialize()
{
	if (FAILED(CPanel::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CInGamePanel::Initialize()
{
	if (FAILED(CPanel::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CInGamePanel::PostInitialize()
{
	if (FAILED(CPanel::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CInGamePanel::BeginPlay()
{
	if (FAILED(CPanel::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CInGamePanel::PreTick(float _fDeltaSeconds)
{
	switch (CPanel::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CInGamePanel::Tick(float _fDeltaSeconds)
{
	switch (CPanel::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CInGamePanel::PostTick(float _fDeltaSeconds)
{
	switch (CPanel::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CInGamePanel::EndPlay()
{
	if (FAILED(CPanel::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CInGamePanel::Render()
{
	CPanel::Render();
}

void Editor::CInGamePanel::Release()
{
	CPanel::Release();
}
