#include "pch.h"
#include "Boss.h"

#include "BossStateComponent.h"
#include "InGamePanel.h"

HRESULT Editor::CBoss::PreInitialize()
{
	return CCharacter::PreInitialize();
}

HRESULT Editor::CBoss::Initialize()
{
	if (FAILED(CCharacter::Initialize())) { return E_FAIL; }

	m_spInGamePanel = CInGamePanel::Create(static_pointer_cast<CActor>(shared_from_this()), EEnemyType::BOSS);
	return S_OK;
}

HRESULT Editor::CBoss::PostInitialize()
{
	if (FAILED(CCharacter::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CBoss::BeginPlay()
{
	if (FAILED(CCharacter::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CBoss::PreTick(float _fDeltaSeconds)
{
	switch (CCharacter::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CBoss::Tick(float _fDeltaSeconds)
{
	switch (CCharacter::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CBoss::PostTick(float _fDeltaSeconds)
{
	switch (CCharacter::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CBoss::EndPlay()
{
	if (FAILED(CCharacter::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CBoss::Render()
{
	CCharacter::Render();
}

void Editor::CBoss::Release()
{
	m_spInGamePanel->Release();
	m_spInGamePanel = nullptr;

	CCharacter::Release();
}

void Editor::CBoss::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Editor::CBoss::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Editor::CBoss::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

float Editor::CBoss::TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn)
{
	m_bAttacked = true;
	m_fCurHP -= _fDamageAmount;
	return 0.0f;
}

void Editor::CBoss::SetBossState(EBossState _eBossState)
{
	m_wpBossStateComponent.lock()->SetBossState(_eBossState);
}

EBossState Editor::CBoss::GetBossState() const
{
	return m_wpBossStateComponent.lock()->GetBossState();
}
