#include "pch.h"
#include "Projectile.h"

#include "SphereComponent.h"
#include "OBBComponent.h"
#include "SoundComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"
#include "SphereComponent.h"

#include "WildAnimal.h"
#include "Boss.h"
#include "Pawn.h"

#include "MathUtility.h"

#include "GameManager.h"

#include "Survivor.h"

void Client::CProjectile::InitializeProjectile
(
	const Vector3& _vSpawnPosition,
	const Vector3& _vSpawnDirection,
	float _fLifeSeconds,
	float _fProjectileSpeed,
	float _fProjectileDamage,
	const std::shared_ptr<CActor>& _spTargetActor,
	const std::shared_ptr<CActor>& _spOwnerActor,
	EProjectileType _eProjectileType,
	EProjectileState _eProjectileState,
	int32 _iProjectileIndex
)
{
	m_vSpawnPosition = _vSpawnPosition;
	m_vSpawnDirection = _vSpawnDirection;
	m_fMaxLifeSeconds = _fLifeSeconds;
	m_fProjectileSpeed = _fProjectileSpeed,
	m_fProjectileDamage = _fProjectileDamage,
	m_wpTargetActor = _spTargetActor;
	m_wpOwnerActor = _spOwnerActor;
	m_eProjectileType = _eProjectileType;
	m_eProjectileState = _eProjectileState;
	m_iProjectileIndex = _iProjectileIndex;
}

HRESULT Client::CProjectile::PreInitialize()
{
	switch (m_eProjectileType)
	{
	case Client::EProjectileType::AYA:
	{
		m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		SetRootComponent(m_wpSphereComponent.lock());

		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());

		wstring strName = L"AyaProjectile" + to_wstring(m_iProjectileIndex);
		m_wpEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"EffectComponent", EComponentType::EFFECT);
		m_wpEffectComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());
	}
	break;

	case Client::EProjectileType::WICKLINE_SKILL_01:
	{
		m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		SetRootComponent(m_wpSphereComponent.lock());

		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());

		wstring strName = L"Wickline1Projectile" + to_wstring(m_iProjectileIndex);
		m_wpEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"EffectComponent", EComponentType::EFFECT);
		m_wpEffectComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());

		m_wpSecondEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"SecondEffectComponent", EComponentType::EFFECT);
		m_wpSecondEffectComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());
	}
	break;

	case Client::EProjectileType::WICKLINE_SKILL_03:
	{
		m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		SetRootComponent(m_wpSphereComponent.lock());

		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());

		wstring strName = L"Wickline3Projectile" + to_wstring(m_iProjectileIndex);
		m_wpEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"EffectComponent", EComponentType::EFFECT);
		m_wpEffectComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());

		m_wpSecondEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"SecondEffectComponent", EComponentType::EFFECT);
		m_wpSecondEffectComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());
	}
	break;

	case Client::EProjectileType::ALPHA_SKILL_02:
	{
		m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		SetRootComponent(m_wpSphereComponent.lock());

		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());

		wstring strName = L"Alpha2Projectile" + to_wstring(m_iProjectileIndex);
		m_wpEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"EffectComponent", EComponentType::EFFECT);
		m_wpEffectComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());
	}
	break;

	case Client::EProjectileType::ALPHA_SKILL_03:
	{
		m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		SetRootComponent(m_wpSphereComponent.lock());

		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());

		wstring strName = L"Alpha3Projectile" + to_wstring(m_iProjectileIndex);
		m_wpEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"EffectComponent", EComponentType::EFFECT);
		m_wpEffectComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());
	}
	break;

	case Client::EProjectileType::OMEGA_SKILL_02:
	{
		m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		SetRootComponent(m_wpSphereComponent.lock());

		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());

		wstring strName = L"OmegaProjectile" + to_wstring(m_iProjectileIndex);
		m_wpEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"EffectComponent", EComponentType::EFFECT);
		m_wpEffectComponent.lock()->SetOwnerComponent(m_wpSphereComponent.lock());
	}
	break;

	default:
		CHECKF(false, L"Projectile type is not designated.");
		break;
	}

	return CActor::PreInitialize();
}

HRESULT Client::CProjectile::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	switch (m_eProjectileType)
	{
	case Client::EProjectileType::AYA:
	{
		SetActorLocalPosition(m_vSpawnPosition);
		LookAt(m_vSpawnPosition + m_vSpawnDirection);

		{
			m_wpEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXAyaAttackProjectile");
			m_wpEffectComponent.lock()->OffMeshEffect();
		}

		{
			m_wpSphereComponent.lock()->SetCenter({ 0.0f, 0.0f, 0.0f });
			m_wpSphereComponent.lock()->SetRadius(0.2f);
			m_wpSphereComponent.lock()->SetActive(true);
			m_wpSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_PROJECTILE);
			m_wpSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
		}
	}
	break;

	case Client::EProjectileType::WICKLINE_SKILL_01:
	{
		SetActorLocalPosition(m_vSpawnPosition);

		{
			m_wpEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXWicklineSkill02Core");
			m_wpEffectComponent.lock()->SetComponentLocalScale({ 1.5f, 1.5f, 1.5f });
			m_wpEffectComponent.lock()->OffMeshEffect();
		}

		{
			m_wpSecondEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXWicklineSkill02Explode");
			m_wpSecondEffectComponent.lock()->SetComponentLocalScale({ 1.5f, 1.5f, 1.5f });
			m_wpSecondEffectComponent.lock()->OffMeshEffect();
		}

		{
			m_wpSphereComponent.lock()->SetCenter({ 0.0f, 0.0f, 0.0f });
			m_wpSphereComponent.lock()->SetRadius(0.5f);
			m_wpSphereComponent.lock()->SetActive(true);
			m_wpSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_PROJECTILE);
			m_wpSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		}
	}
	break;

	case Client::EProjectileType::WICKLINE_SKILL_03:
	{
		{
			m_wpEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXWicklineSkill03Trap");
			m_wpEffectComponent.lock()->OffMeshEffect();

			m_wpSecondEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXWicklineSkill03Activate");
			m_wpSecondEffectComponent.lock()->OffMeshEffect();
		}

		{
			m_wpSphereComponent.lock()->SetCenter({ 0.0f, 0.0f, 0.0f });
			m_wpSphereComponent.lock()->SetRadius(0.5f);
			m_wpSphereComponent.lock()->SetActive(true);
			m_wpSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_PROJECTILE);
			m_wpSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		}
	}
	break;

	case Client::EProjectileType::ALPHA_SKILL_02:
	case Client::EProjectileType::OMEGA_SKILL_02:
	{
		SetActorLocalPosition(m_vSpawnPosition);

		{
			m_wpEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXAlphaSkill02");
			m_wpEffectComponent.lock()->OffMeshEffect();
		}

		{
			m_wpSphereComponent.lock()->SetCenter({ 0.0f, 0.0f, 0.0f });
			m_wpSphereComponent.lock()->SetRadius(0.6f);
			m_wpSphereComponent.lock()->SetActive(true);
			m_wpSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_PROJECTILE);
			m_wpSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		}
	}
	break;

	case Client::EProjectileType::ALPHA_SKILL_03:
	case Client::EProjectileType::OMEGA_SKILL_03:
	{
		SetActorLocalPosition(m_vSpawnPosition);

		{
			m_wpEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXAlphaSkill03Projectile");
			m_wpEffectComponent.lock()->OffMeshEffect();
		}

		{
			m_wpSphereComponent.lock()->SetCenter({ 0.0f, 0.0f, 0.0f });
			m_wpSphereComponent.lock()->SetRadius(0.6f);
			m_wpSphereComponent.lock()->SetActive(true);
			m_wpSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_PROJECTILE);
			m_wpSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		}
	}
	break;

	default:
		break;
	}

	return S_OK;
}

HRESULT Client::CProjectile::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CProjectile::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CProjectile::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CProjectile::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	switch (m_eProjectileState)
	{
	case Client::EProjectileState::STAY:
	{
		if (m_eProjectileType == EProjectileType::WICKLINE_SKILL_03)
		{
			if (!m_bSkillApply)
			{
				m_wpSphereComponent.lock()->SetActive(true);
				m_wpSoundComponent.lock()->PlaySoundEx("Trap_ClangClatter_common_Wait", ESoundType::EFFECT_03);
				m_wpEffectComponent.lock()->PlayMeshEffect();
				m_bSkillApply = true;
			}

			m_fSumLifeSeconds += _fDeltaSeconds;

			if (m_fSumLifeSeconds >= m_fMaxLifeSeconds)
			{
				m_fSumLifeSeconds = 0.0f;
				m_wpSphereComponent.lock()->SetActive(false);
				m_wpEffectComponent.lock()->OffMeshEffect();

				m_bSkillApply = false;

				SetActorLocalPosition(m_vSpawnPosition);
				m_eProjectileState = EProjectileState::DIE;
				break;
			}

			SetActorLocalPosition(m_vSpawnPosition);
		}

		if (m_eProjectileType == EProjectileType::ALPHA_SKILL_02 || m_eProjectileType == EProjectileType::OMEGA_SKILL_02)
		{
			if (!m_bSkillApply)
			{
				m_wpEffectComponent.lock()->PlayMeshEffect();
				m_bSkillApply = true;
			}

			m_fSumLifeSeconds += _fDeltaSeconds;

			if (2.0f <= m_fSumLifeSeconds && !m_bSoundApply)
			{
				m_bSoundApply = true;
				m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_skill02_Spout", ESoundType::EFFECT_03);

				unordered_set<shared_ptr<CShapeComponent>> usetShapeComponents = m_wpSphereComponent.lock()->GetShapeComponents();
				for (const auto& spShapeComponent : usetShapeComponents)
				{
					if (spShapeComponent->GetCollisionLayer() == ECollisionLayer::PLAYER)
					{
						m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_skill01_Hit", ESoundType::CREATURE_01);
						m_wpTargetActor.lock()->TakeDamage(200.0f, nullptr, nullptr);
					}
				}
			}

			if (m_fSumLifeSeconds >= m_fMaxLifeSeconds)
			{
				m_fSumLifeSeconds = 0.0f;
				m_wpSphereComponent.lock()->SetActive(false);
				m_wpEffectComponent.lock()->OffMeshEffect();
				
				m_bSkillApply = false;
				m_bSoundApply = false;

				SetActorLocalPosition(m_vSpawnPosition);
				m_eProjectileState = EProjectileState::DIE;
				break;
			}

			m_wpSphereComponent.lock()->SetActive(true);
			SetActorLocalPosition(m_vSpawnPosition);
		}
	}
	break;

	case Client::EProjectileState::MOVE:
	{
		m_wpEffectComponent.lock()->PlayMeshEffect();
		m_fSumLifeSeconds += _fDeltaSeconds;

		if (m_fSumLifeSeconds >= m_fMaxLifeSeconds)
		{
			if (m_eProjectileType == EProjectileType::WICKLINE_SKILL_01)
			{
				m_wpSoundComponent.lock()->PlaySoundEx("Haze_Skill04_Rocket_02_Hit", ESoundType::EFFECT_03);
			}

			m_fSumLifeSeconds = 0.0f;
			m_wpSphereComponent.lock()->SetActive(false);
			m_wpEffectComponent.lock()->OffMeshEffect();
			m_bAlphaThirdSkillApply = false;

			m_eProjectileState = EProjectileState::DIE;
			SetActorLocalPosition(m_vSpawnPosition);
			break;
		}
		
		if (m_eProjectileType == EProjectileType::ALPHA_SKILL_03)
		{
			if (!m_bAlphaThirdSkillApply)
			{
				unordered_set<shared_ptr<CShapeComponent>> usetShapeComponents = m_wpSphereComponent.lock()->GetShapeComponents();
				for (const auto& spShapeComponent : usetShapeComponents)
				{
					if (spShapeComponent->GetCollisionLayer() == ECollisionLayer::PLAYER)
					{
						m_bAlphaThirdSkillApply = true;
						m_wpSoundComponent.lock()->PlaySoundEx("Cathy_Skill04_Hit", ESoundType::CREATURE_01);
						m_wpTargetActor.lock()->TakeDamage(70.0f, nullptr, nullptr);
					}
				}
			}
		}

		m_wpSphereComponent.lock()->SetActive(true);
		Vector3 vWorldPosition = GetActorWorldPosition().value();
		Vector3 vTargetPosition = vWorldPosition + m_vSpawnDirection * m_fProjectileSpeed;
		SetActorLocalPosition(vTargetPosition);
	}
	break;

	case Client::EProjectileState::TRACE:
	{
		if (!m_bSkillApply)
		{
			m_wpEffectComponent.lock()->PlayMeshEffect();
			m_bSkillApply = true;
		}

		m_fSumLifeSeconds += _fDeltaSeconds;

		if (m_fSumLifeSeconds >= m_fMaxLifeSeconds)
		{
			m_bSkillApply = false;
			m_fSumLifeSeconds = 0.0f;
			m_wpSphereComponent.lock()->SetActive(false);

			m_eProjectileState = EProjectileState::DIE;
			SetActorLocalPosition(m_vSpawnPosition);
			break;
		}

		m_wpSphereComponent.lock()->SetActive(true);
		Vector3 vWorldPosition = GetActorWorldPosition().value();
		Vector3 vSurvivorPosition = CGameManager::GetInstance()->GetSurvivor()->GetActorWorldPosition().value();

		Vector3 vTargetDirection = vSurvivorPosition - vWorldPosition;
		vTargetDirection.Normalize();

		Vector3 vTargetPosition = vWorldPosition + vTargetDirection * m_fProjectileSpeed;
		SetActorLocalPosition(vTargetPosition);
	}
	break;

	case Client::EProjectileState::DIE:
		break;

	default:
		CHECKF(false, L"Projectile type is not designated.");
		break;
	}

	return 0;
}

int32 Client::CProjectile::PostTick(float _fDeltaSeconds)
{
	if (m_eProjectileState == EProjectileState::DIE) { return 0; }

	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CProjectile::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CProjectile::Render()
{
	if (m_eProjectileState == EProjectileState::DIE) { return; }

	CActor::Render();
}

void Client::CProjectile::Release()
{
	CActor::Release();
}

void Client::CProjectile::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CActor::OnCollisionEnter(_spSrc, _spDst);

	if (_spSrc->GetCollisionLayer() == ECollisionLayer::PLAYER_PROJECTILE)
	{
		switch (_spDst->GetCollisionLayer())
		{
		case ECollisionLayer::MONSTER:
		{
			shared_ptr<CWildAnimal> spWildAnimal = dynamic_pointer_cast<CWildAnimal>(_spDst->GetOwnerActor());
			if (spWildAnimal && spWildAnimal->IsDead()) { break; }

			shared_ptr<CBoss> spBoss = dynamic_pointer_cast<CBoss>(_spDst->GetOwnerActor());
			if (spBoss && spBoss->IsDead()) { break; }

			_spDst->GetOwnerActor()->TakeDamage(m_fProjectileDamage, nullptr, static_pointer_cast<CPawn>(m_wpOwnerActor.lock()));

			m_fSumLifeSeconds = 0.0f;
			m_wpSphereComponent.lock()->SetActive(false);
			m_wpEffectComponent.lock()->OffMeshEffect();
			
			if (m_eProjectileType == EProjectileType::AYA)
			{
				string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));
				m_wpSoundComponent.lock()->PlaySoundEx("hitPistol_in_r" + strIndex, ESoundType::HIT_02, 1.0f);
			}

			SetActorLocalPosition(m_vSpawnPosition);
			m_eProjectileState = EProjectileState::DIE;
		}
		break;

		default:
			break;
		}
	}
	else if (_spSrc->GetCollisionLayer() == ECollisionLayer::MONSTER_PROJECTILE)
	{
		if (_spSrc->GetComponentWorldMatrix() == Matrix::Identity) { return; }
		if (_spDst->GetComponentWorldMatrix() == Matrix::Identity) { return; }

		switch (_spDst->GetCollisionLayer())
		{
		case ECollisionLayer::PLAYER:
		{
			if (m_eProjectileType == EProjectileType::WICKLINE_SKILL_01)
			{
				_spDst->GetOwnerActor()->TakeDamage(150.0f, nullptr, dynamic_pointer_cast<CPawn>(m_wpOwnerActor.lock()));

				m_wpEffectComponent.lock()->OffMeshEffect();
				m_wpSecondEffectComponent.lock()->PlayMeshEffect();
				m_wpSphereComponent.lock()->SetActive(false);
				m_wpSoundComponent.lock()->PlaySoundEx("Haze_Skill04_Rocket_02_Hit", ESoundType::CREATURE_01);

			}

			else if (m_eProjectileType == EProjectileType::WICKLINE_SKILL_03)
			{
				if (m_fSumLifeSeconds <= 1.0f) { break; }
				_spDst->GetOwnerActor()->TakeDamage(100.0f, nullptr, dynamic_pointer_cast<CPawn>(m_wpOwnerActor.lock()));

				m_wpEffectComponent.lock()->OffMeshEffect();
				m_wpSecondEffectComponent.lock()->PlayMeshEffect();
				m_wpSphereComponent.lock()->SetActive(false);
				m_wpSoundComponent.lock()->PlaySoundEx("Trap_Guillotine_common_Attack", ESoundType::EFFECT_03);
			}
		}
		break;
		}
	}
}

void Client::CProjectile::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CActor::OnCollisionStay(_spSrc, _spDst);
}

void Client::CProjectile::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CActor::OnCollisionExit(_spSrc, _spDst);
}

void Client::CProjectile::Revive
(
	const Vector3& _vSpawnPosition,
	const Vector3& _vSpawnDirection,
	float _fLifeSeconds,
	float _fProjectileSpeed,
	float _fProjectileDamage,
	const std::shared_ptr<CActor>& _spTargetActor,
	const std::shared_ptr<CActor>& _spOwnerActor,
	EProjectileType _eProjectileType,
	EProjectileState _eProjectileState)
{
	m_vSpawnPosition = _vSpawnPosition;
	m_vSpawnDirection = _vSpawnDirection;
	m_fMaxLifeSeconds = _fLifeSeconds;
	m_fProjectileSpeed = _fProjectileSpeed,
	m_fProjectileDamage = _fProjectileDamage;
	m_wpTargetActor = _spTargetActor;
	m_wpOwnerActor = _spOwnerActor;
	m_eProjectileType = _eProjectileType;
	m_eProjectileState = _eProjectileState;

	SetActorLocalPosition(m_vSpawnPosition);
	LookAt(m_vSpawnPosition + m_vSpawnDirection);

	SetActorRenderType(ERenderType::OPAQUE_OBJECT);
}

void Client::CProjectile::MoveTo(const Vector3& _vDirection)
{
	m_eProjectileState = EProjectileState::MOVE;

	Vector3 vPosition = GetActorLocalPosition().value();
	LookAt(vPosition + _vDirection);
}

void Client::CProjectile::TraceTo(const std::shared_ptr<CActor> _spTargetActor)
{

}
