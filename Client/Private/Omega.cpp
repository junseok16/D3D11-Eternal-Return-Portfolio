#include "pch.h"
#include "Omega.h"

#include "OmegaStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "OBBComponent.h"
#include "SphereComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"

#include "Projectile.h"

#include "World.h"
#include "Level.h"

#include "Survivor.h"

HRESULT Client::COmega::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_OBJECT);

	{
		m_eBossType = EBossType::OMEGA;
		m_fAttackRange = 2.0f;
		m_fCurMoveSpeed = 3.5f;
		m_fCurHP = 400.0f;
		m_fMaxHP = 400.0f;
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Omega");
		m_wpSkeletalMeshComponent.lock()->SetVertexShaderDesc(L"VS_SkeletalMesh");
		m_wpSkeletalMeshComponent.lock()->SetPixelShaderDesc(L"PS_SkeletalMesh");
	}

	{
		m_wpNavigationComponent = CreateActorComponent<CNavigationComponent>(L"NavigationComponent", EComponentType::NAVIGATION);
		m_wpNavigationComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpNavigationComponent.lock()->SetNavigation(L"LumiaNavigation");
		m_wpNavigationComponent.lock()->SetCurCellIndex(100 /*m_iSpawnCellIndex*/);
	}

	{
		m_wpBossStateComponent = CreateActorComponent<COmegaStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpFirstSkillOBBComponent = CreateActorComponent<COBBComponent>(L"FirstSkillOBBComponent", EComponentType::OBB);
		m_wpFirstSkillOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpHitEffectComponent = CreateActorComponent<CEffectComponent>(m_wstrActorName + L"HitEffectComponent", EComponentType::EFFECT);
		m_wpHitEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpHitEffectComponent.lock()->OffMeshEffect();

		m_wpRightAttackEffectComponent = CreateActorComponent<CEffectComponent>(m_wstrActorName + L"RightAttackEffectComponent", EComponentType::EFFECT);
		m_wpRightAttackEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpRightAttackEffectComponent.lock()->OffMeshEffect();

		m_wpLeftAttackEffectComponent = CreateActorComponent<CEffectComponent>(m_wstrActorName + L"LeftAttackEffectComponent", EComponentType::EFFECT);
		m_wpLeftAttackEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpLeftAttackEffectComponent.lock()->OffMeshEffect();

		m_wpFirstSkillEffectComponent = CreateActorComponent<CEffectComponent>(m_wstrActorName + L"FirstSkillEffectComponent", EComponentType::EFFECT);
		m_wpFirstSkillEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpFirstSkillEffectComponent.lock()->OffMeshEffect();
	}

	{
		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	return CBoss::PreInitialize();
}

HRESULT Client::COmega::Initialize()
{
	if (FAILED(CBoss::Initialize())) { return E_FAIL; }
	
	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::WAIT,			L"WAIT",		{ "Monster_Alpha_wait" },			true);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::RUN,				L"WALK",		{ "Monster_Alpha_walk" },			true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::ATTACK_01,		L"ATTACK_01",	{ "Monster_Omega_atk01" },			false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::ATTACK_02,		L"ATTACK_02",	{ "Monster_Omega_atk02" },			false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_01_BEGIN,	L"SKILL_BEGIN", { "Monster_Alpha_skill01_ready" },	false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_01,		L"SKILL_01",	{ "Monster_Alpha_skill01_atk" },	false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_02,		L"SKILL_02",	{ "Monster_Alpha_skill02" },		false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::END_BATTLE,		L"END_BATTLE",	{ "Monster_Alpha_endbattle" },		false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::DEATH,			L"DEATH",		{ "Monster_Omega_death" },			false);

		m_wpSkeletalMeshComponent.lock()->SetComponentLocalScale({ 1.3f, 1.3f, 1.3f });
	}

	{
		m_wpBodySphereComponent.lock()->SetRadius(1.2f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.6f, 0.0f });
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	{
		m_wpFirstSkillOBBComponent.lock()->SetCenter({ 0.0f, 0.5f, 1.0f });
		m_wpFirstSkillOBBComponent.lock()->SetExtent({ 2.0f, 1.0f, 2.5f });
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);
		m_wpFirstSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_SKILL);
		m_wpFirstSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
	}

	{
		m_wpHitEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHitStar01");

		m_wpRightAttackEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXAlphaAttackRightWind");

		m_wpLeftAttackEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXAlphaAttackLeftWind");

		m_wpFirstSkillEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXAlphaSkill01Slash");
	}

	return S_OK;
}

HRESULT Client::COmega::PostInitialize()
{
	if (FAILED(CBoss::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::COmega::BeginPlay()
{
	if (FAILED(CBoss::BeginPlay())) { return E_FAIL; }

	// TODO; 임시로 스폰 위치를 설정합니다.
	SetActorLocalPosition(m_wpNavigationComponent.lock()->GetCentroidPosition(100));
	return S_OK;
}

int32 Client::COmega::PreTick(float _fDeltaSeconds)
{
	switch (CBoss::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->PreTick(_fDeltaSeconds);
	}

	return 0;
}

int32 Client::COmega::Tick(float _fDeltaSeconds)
{
	switch (CBoss::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->Tick(_fDeltaSeconds);
	}

	return 0;
}

int32 Client::COmega::PostTick(float _fDeltaSeconds)
{
	switch (CBoss::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->PostTick(_fDeltaSeconds);
	}

	return 0;
}

HRESULT Client::COmega::EndPlay()
{
	if (FAILED(CBoss::EndPlay())) { return E_FAIL; }

	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->EndPlay();
	}

	return S_OK;
}

void Client::COmega::Render()
{
	CBoss::Render();

	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->Render();
	}
}

void Client::COmega::Release()
{
	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->Release();
	}

	CBoss::Release();
}

void Client::COmega::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionEnter(_spSrc, _spDst);
}

void Client::COmega::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionStay(_spSrc, _spDst);
}

void Client::COmega::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionExit(_spSrc, _spDst);
}

void Client::COmega::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	{
		m_wpSurvivor.lock()->TakeDamage(130.0f, nullptr, static_pointer_cast<COmega>(shared_from_this()));
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_atk01", ESoundType::CREATURE_01);
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_atk_hit", ESoundType::HIT_01);
		m_wpRightAttackEffectComponent.lock()->PlayMeshEffect();
	}
	break;

	case EBossAnimState::ATTACK_02:
	{
		m_wpSurvivor.lock()->TakeDamage(130.0f, nullptr, static_pointer_cast<COmega>(shared_from_this()));
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_atk02", ESoundType::CREATURE_01);
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_atk_hit", ESoundType::HIT_01);
		m_wpLeftAttackEffectComponent.lock()->PlayMeshEffect();
	}
	break;

	case EBossAnimState::SKILL_01_BEGIN:
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_skill01_Start", ESoundType::EFFECT_01);
		m_wpFirstSkillEffectComponent.lock()->PlayMeshEffect();
		break;

	case EBossAnimState::SKILL_01:
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_skill01_Swing", ESoundType::EFFECT_02);
		m_wpFirstSkillOBBComponent.lock()->SetActive(true);
		break;

	case EBossAnimState::SKILL_02:
		break;

	case EBossAnimState::DEATH:
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_dead", ESoundType::CREATURE_01);
		break;
	}
}

void Client::COmega::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::SKILL_01:

		if (0.5f <= _fRatio && !m_bFirstSkillApply)
		{
			m_bFirstSkillApply = true;

			unordered_set<shared_ptr<CShapeComponent>> usetShapeComponents = m_wpFirstSkillOBBComponent.lock()->GetShapeComponents();
			for (const auto& spShapeComponent : usetShapeComponents)
			{
				if (spShapeComponent->GetCollisionLayer() == ECollisionLayer::PLAYER)
				{
					m_wpSurvivor.lock()->PlaySoundEx("AlphaOmega_skill01_Hit", ESoundType::CREATURE_01);
					m_wpSurvivor.lock()->TakeDamage(200.0f, nullptr, nullptr);
				}
			}
		}

		break;

	default:
		break;
	}
}

void Client::COmega::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	case EBossAnimState::ATTACK_02:
		break;

	case EBossAnimState::SKILL_01:
		m_bFirstSkillApply = false;
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);
		break;

	case EBossAnimState::DEATH:
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);

		m_wpHitEffectComponent.lock()->StopMeshEffect();
		m_wpFirstSkillEffectComponent.lock()->StopMeshEffect();
		m_wpRightAttackEffectComponent.lock()->StopMeshEffect();
		m_wpLeftAttackEffectComponent.lock()->PlayMeshEffect();
		break;
	}
}
