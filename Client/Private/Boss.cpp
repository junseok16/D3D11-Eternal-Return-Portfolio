#include "pch.h"
#include "Boss.h"

// component
#include "BossStateComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"
#include "InGamePanel.h"
#include "Survivor.h"
#include "MathUtility.h"
#include "GameManager.h"

HRESULT Client::CBoss::PreInitialize()
{
	return CCharacter::PreInitialize();
}

HRESULT Client::CBoss::Initialize()
{
	if (FAILED(CCharacter::Initialize())) { return E_FAIL; }

	// m_spInGamePanel = CInGamePanel::Create(static_pointer_cast<CActor>(shared_from_this()), EEnemyType::BOSS);
	return S_OK;
}

HRESULT Client::CBoss::PostInitialize()
{
	if (FAILED(CCharacter::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBoss::BeginPlay()
{
	if (FAILED(CCharacter::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CBoss::PreTick(float _fDeltaSeconds)
{
	m_wpSurvivor = CGameManager::GetInstance()->GetSurvivor();

	switch (CCharacter::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBoss::Tick(float _fDeltaSeconds)
{
	switch (CCharacter::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBoss::PostTick(float _fDeltaSeconds)
{
	switch (CCharacter::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CBoss::EndPlay()
{
	if (FAILED(CCharacter::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CBoss::Render()
{
	CCharacter::Render();
}

void Client::CBoss::Release()
{
	if (m_spInGamePanel)
	{
		m_spInGamePanel->Release();
		m_spInGamePanel = nullptr;
	}

	CCharacter::Release();
}

void Client::CBoss::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Client::CBoss::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

void Client::CBoss::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
}

float Client::CBoss::TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn)
{
	switch (m_eBossType)
	{
	case Client::EBossType::WICKLINE:
		break;
	case Client::EBossType::ALPHA:
		break;
	case Client::EBossType::OMEGA:
		break;
	case Client::EBossType::ENUM_END:
		break;
	default:
		break;
	}

	if (m_bDead)
	{
		return 0.0f;
	}

	m_bAttacked = true;
	m_fCurHP -= _fDamageAmount;

	if ((m_fCurHP <= 0.0f) && !m_bDead)
	{
		m_bDead = true;
		dynamic_pointer_cast<CSurvivor>(_spInstigatorPawn)->AddCurExp(m_fExp);

		Vector3 vFrom = { -1.0f, 0.9f, -1.0f };
		Vector3 vTo = { 1.0f, 1.1f, -0.5f };

		Vector3 vPosition = CMathUtility::GetRandomDirection(vFrom, vTo);
		float fScale = static_cast<float>(CMathUtility::GetRandomInteger(1, 2));
		fScale /= 10.0f;

		m_wpHitEffectComponent.lock()->SetComponentLocalPosition(vPosition);
		m_wpHitEffectComponent.lock()->SetComponentLocalScale({ fScale, fScale, fScale });
		m_wpHitEffectComponent.lock()->PlayMeshEffect();
		return 0.0f;
	}

	Vector3 vFrom = { -1.0f, 0.9f, -2.0f };
	Vector3 vTo = { 1.0f, 1.1f, -1.0f };

	Vector3 vPosition = CMathUtility::GetRandomDirection(vFrom, vTo);
	float fScale = static_cast<float>(CMathUtility::GetRandomInteger(12, 20));
	fScale /= 10.0f;

	m_wpHitEffectComponent.lock()->SetComponentLocalPosition(vPosition);
	m_wpHitEffectComponent.lock()->SetComponentLocalScale({ fScale, fScale, fScale });
	m_wpHitEffectComponent.lock()->PlayMeshEffect();
	return 0.0f;
}

void Client::CBoss::SetBossState(EBossState _eBossState)
{
	m_wpBossStateComponent.lock()->SetBossState(_eBossState);
}

EBossState Client::CBoss::GetBossState() const
{
	return m_wpBossStateComponent.lock()->GetBossState();
}
