#include "pch.h"
#include "Alpha.h"

// component
#include "AlphaStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "OBBComponent.h"
#include "SphereComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"
#include "CameraComponent.h"

#include "Projectile.h"

#include "World.h"
#include "Level.h"

#include "Survivor.h"

HRESULT Client::CAlpha::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_OBJECT);

	{
		m_eBossType = EBossType::ALPHA;
		m_fAttackRange = 2.0f;
		m_fCurMoveSpeed = 3.5f;
		m_fCurHP = 1100.0f;
		m_fMaxHP = 1100.0f;
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Alpha");
		m_wpSkeletalMeshComponent.lock()->SetVertexShaderDesc(L"VS_SkeletalMesh");
		m_wpSkeletalMeshComponent.lock()->SetPixelShaderDesc(L"PS_SkeletalMesh");
	}

	{
		m_wpNavigationComponent = CreateActorComponent<CNavigationComponent>(L"NavigationComponent", EComponentType::NAVIGATION);
		m_wpNavigationComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpNavigationComponent.lock()->SetNavigation(L"LumiaNavigation");
		m_wpNavigationComponent.lock()->SetCurCellIndex(5561);
	}

	{
		m_wpBossStateComponent = CreateActorComponent<CAlphaStateComponent>(L"StateComponent", EComponentType::STATE);
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

	{
		m_wpCameraComponent = CreateActorComponent<CCameraComponent>(L"AlphaCameraComponent", EComponentType::CAMERA);
		m_wpCameraComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpCameraComponent.lock()->SetOffset({ 0.0f, 0.0f, 0.0f });
		m_wpCameraComponent.lock()->SetRadius(3.0f);

		m_wpCameraComponent.lock()->SetThisCameraOnAir();
		m_wpCameraComponent.lock()->SetCameraWalk(true);
	}
	return CBoss::PreInitialize();
}

HRESULT Client::CAlpha::Initialize()
{
	if (FAILED(CBoss::Initialize())) { return E_FAIL; }

	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::WAIT,			L"WAIT",		{ "Monster_Alpha_wait" },			true);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::RUN,				L"WALK",		{ "Monster_Alpha_walk" },			true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::ATTACK_01,		L"ATTACK_01",	{ "Monster_Alpha_atk01" },			false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::ATTACK_02,		L"ATTACK_02",	{ "Monster_Alpha_atk02" },			false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_01_BEGIN,	L"SKILL_BEGIN", { "Monster_Alpha_skill01_ready" },	false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_01,		L"SKILL_01",	{ "Monster_Alpha_skill01_atk" },	false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_02,		L"SKILL_02",	{ "Monster_Alpha_skill02" },		false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_03,		L"SKILL_03",	{ "Monster_Alpha_skill02" },		false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::END_BATTLE,		L"END_BATTLE",	{ "Monster_Alpha_endbattle" },		false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::DEATH,			L"DEATH",		{ "Monster_Alpha_death" },			false);

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
		m_wpFirstSkillOBBComponent.lock()->SetExtent({ 2.0f, 1.0f, 1.0f });
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

HRESULT Client::CAlpha::PostInitialize()
{
	if (FAILED(CBoss::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CAlpha::BeginPlay()
{
	if (FAILED(CBoss::BeginPlay())) { return E_FAIL; }

	// TODO; 임시로 스폰 위치를 설정합니다.
	SetActorLocalPosition(m_wpNavigationComponent.lock()->GetCentroidPosition(5561));
	// SetWanderDirection();
	return S_OK;
}

int32 Client::CAlpha::PreTick(float _fDeltaSeconds)
{
	switch (CBoss::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecAlphaProjectiles)
	{
		spProjectile->PreTick(_fDeltaSeconds);
	}

	return 0;
}

int32 Client::CAlpha::Tick(float _fDeltaSeconds)
{
	switch (CBoss::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecAlphaProjectiles)
	{
		spProjectile->Tick(_fDeltaSeconds);
	}
	return 0;
}

int32 Client::CAlpha::PostTick(float _fDeltaSeconds)
{
	switch (CBoss::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecAlphaProjectiles)
	{
		spProjectile->PostTick(_fDeltaSeconds);
	}
	return 0;
}

HRESULT Client::CAlpha::EndPlay()
{
	if (FAILED(CBoss::EndPlay())) { return E_FAIL; }

	for (const auto& spProjectile : m_vecAlphaProjectiles)
	{
		spProjectile->EndPlay();
	}
	return S_OK;
}

void Client::CAlpha::Render()
{
	CBoss::Render();

	for (const auto& spProjectile : m_vecAlphaProjectiles)
	{
		spProjectile->Render();
	}
}

void Client::CAlpha::Release()
{
	for (auto& spProjectile : m_vecAlphaProjectiles)
	{
		spProjectile->Release();
		spProjectile = nullptr;
	}

	CBoss::Release();
}

void Client::CAlpha::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionEnter(_spSrc, _spDst);
}

void Client::CAlpha::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionStay(_spSrc, _spDst);
}

void Client::CAlpha::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionExit(_spSrc, _spDst);
}

void Client::CAlpha::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	{
		m_wpSurvivor.lock()->TakeDamage(120.0f, nullptr, static_pointer_cast<CAlpha>(shared_from_this()));
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_atk01", ESoundType::CREATURE_01);
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_atk_hit", ESoundType::HIT_01);
		m_wpRightAttackEffectComponent.lock()->PlayMeshEffect();
	}
	break;

	case EBossAnimState::ATTACK_02:
	{
		m_wpSurvivor.lock()->TakeDamage(120.0f, nullptr, static_pointer_cast<CAlpha>(shared_from_this()));
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_atk02", ESoundType::CREATURE_01);
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_atk_hit", ESoundType::HIT_01);
	}
	break;

	case EBossAnimState::SKILL_01_BEGIN:
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_skill01_Start", ESoundType::EFFECT_01);
		m_wpFirstSkillEffectComponent.lock()->PlayMeshEffect();
		m_wpFirstSkillOBBComponent.lock()->SetActive(true);
		break;

	case EBossAnimState::SKILL_01:
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_skill01_Swing", ESoundType::EFFECT_02);
		break;

	case EBossAnimState::SKILL_02:
	{
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(0.7f);
	}
	break;

	case EBossAnimState::SKILL_03:
	{
		m_wpSoundComponent.lock()->PlaySoundEx("Echion_Skill04_Start", ESoundType::EFFECT_02);
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(0.7f);
	}
	break;

	case EBossAnimState::DEATH:
		m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_dead", ESoundType::CREATURE_01);
		break;
	}
}

void Client::CAlpha::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_02:

		if (0.2f <= _fRatio && !m_bLeftAttackApply)
		{
			m_bLeftAttackApply = true;
			m_wpLeftAttackEffectComponent.lock()->PlayMeshEffect();
		}
		
		break;

	case EBossAnimState::SKILL_01:
	{
		if (0.7f <= _fRatio && !m_bFirstSkillApply)
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
	}
	break;

	case EBossAnimState::SKILL_02:
	{
		if (0.1f <= _fRatio && !m_bSecondSkillApply[0])
		{
			m_bSecondSkillApply[0] = true;
			FireSecondSkill();
		}

		else if (0.3f <= _fRatio && !m_bSecondSkillApply[1])
		{
			m_bSecondSkillApply[1] = true;
			FireSecondSkill();
		}
		
		else if (0.5f <= _fRatio && !m_bSecondSkillApply[2])
		{
			m_bSecondSkillApply[2] = true;
			FireSecondSkill();
		}

		else if (0.7f <= _fRatio && !m_bSecondSkillApply[3])
		{
			m_bSecondSkillApply[3] = true;
			FireSecondSkill();
		}

		else if (0.9f <= _fRatio && !m_bSecondSkillApply[4])
		{
			m_bSecondSkillApply[4] = true;
			FireSecondSkill();
		}
	}
	break;

	case EBossAnimState::SKILL_03:
	{
		if (0.1f <= _fRatio && !m_bThirdSkillApply[0])
		{
			m_bThirdSkillApply[0] = true;
			FireThirdSkill(3.0f);
		}

		else if (0.2f <= _fRatio && !m_bThirdSkillApply[1])
		{
			m_bThirdSkillApply[1] = true;
			FireThirdSkill(3.0f);
		}

		else if (0.3f <= _fRatio && !m_bThirdSkillApply[2])
		{
			m_bThirdSkillApply[2] = true;
			FireThirdSkill(3.0f);
		}

		else if (0.4f <= _fRatio && !m_bThirdSkillApply[3])
		{
			m_bThirdSkillApply[3] = true;
			FireThirdSkill(3.0f);
		}

		else if (0.5f <= _fRatio && !m_bThirdSkillApply[4])
		{
			m_bThirdSkillApply[4] = true;
			FireThirdSkill(3.0f);
		}
	}
	break;
	default:
		break;
	}
}

void Client::CAlpha::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	case EBossAnimState::ATTACK_02:
		m_bLeftAttackApply = false;
		break;

	case EBossAnimState::SKILL_01:
		m_bFirstSkillApply = false;
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);
		break;

	case EBossAnimState::SKILL_02:
		m_bSecondSkillApply[0] = false;
		m_bSecondSkillApply[1] = false;
		m_bSecondSkillApply[2] = false;
		m_bSecondSkillApply[3] = false;
		m_bSecondSkillApply[4] = false;
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		break;

	case EBossAnimState::SKILL_03:
		m_bThirdSkillApply[0] = false;
		m_bThirdSkillApply[1] = false;
		m_bThirdSkillApply[2] = false;
		m_bThirdSkillApply[3] = false;
		m_bThirdSkillApply[4] = false;
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		break;

	case EBossAnimState::DEATH:
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);

		m_wpHitEffectComponent.lock()->StopMeshEffect();
		m_wpFirstSkillEffectComponent.lock()->StopMeshEffect();
		m_wpRightAttackEffectComponent.lock()->StopMeshEffect();
		m_wpLeftAttackEffectComponent.lock()->StopMeshEffect();
		break;
	}
}

void Client::CAlpha::FireSecondSkill()
{
	m_wpSoundComponent.lock()->PlaySoundEx("AlphaOmega_skill02_Ready", ESoundType::EFFECT_01);
	Vector3 vPosition = m_wpSurvivor.lock()->GetActorWorldPosition().value();

	bool bFoundDead = false;

	for (const auto& spProjectile : m_vecAlphaProjectiles)
	{
		if (spProjectile->IsDead() && spProjectile->GetProjectileType() == EProjectileType::ALPHA_SKILL_02)
		{
			spProjectile->Revive
			(
				vPosition,
				Vector3::Forward,
				2.5f,
				0.0f,
				200.0f,
				m_wpSurvivor.lock(),
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::ALPHA_SKILL_02,
				EProjectileState::STAY
			);
			bFoundDead = true;
			break;
		}
	}

	if (bFoundDead == false)
	{
		shared_ptr<CProjectile> spProjectile = CProjectile::Create<CProjectile>
			(
				vPosition,
				Vector3::Forward,
				2.5f,
				0.0f,
				200.0f,
				m_wpSurvivor.lock(),
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::ALPHA_SKILL_02,
				EProjectileState::STAY,
				(int32)m_vecAlphaProjectiles.size()
			);
		m_vecAlphaProjectiles.push_back(spProjectile);
	}
}

void Client::CAlpha::FireThirdSkill(float _fDegree)
{
	Vector3 vPosition = m_wpSurvivor.lock()->GetActorWorldPosition().value();
	Vector3 vAlphaPosition = GetActorWorldPosition().value();

	Vector3 vDirection = vPosition - vAlphaPosition;
	vDirection.Normalize();

	int32 iSumThirdSkills = 5;
	int32 iNumThirdSkills = 0;
	Matrix matRotate = Matrix::CreateRotationY(XMConvertToRadians(360.0f / iSumThirdSkills + _fDegree));

	for (const auto& spProjectile : m_vecAlphaProjectiles)
	{
		if (4 < iNumThirdSkills)
		{
			iNumThirdSkills = 0;
			return;
		}

		if (spProjectile->IsDead() && (spProjectile->GetProjectileType() == EProjectileType::ALPHA_SKILL_03))
		{
			vDirection = vDirection.TransformNormal(vDirection, matRotate);

			spProjectile->Revive
			(
				vAlphaPosition,
				vDirection,
				2.5f,
				0.1f,
				150.0f,
				m_wpSurvivor.lock(),
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::ALPHA_SKILL_03,
				EProjectileState::MOVE
			);
			iNumThirdSkills++;
		}
	}

	for (int32 iIndex = iNumThirdSkills; iIndex < 5; ++iIndex)
	{
		vDirection = vDirection.TransformNormal(vDirection, matRotate);

		shared_ptr<CProjectile> spProjectile = CProjectile::Create<CProjectile>
			(
				vAlphaPosition,
				vDirection,
				2.5f,
				0.1f,
				150.0f,
				m_wpSurvivor.lock(),
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::ALPHA_SKILL_03,
				EProjectileState::MOVE,
				(int32)m_vecAlphaProjectiles.size()
			);
		iNumThirdSkills++;

		m_vecAlphaProjectiles.push_back(spProjectile);
	}
}
