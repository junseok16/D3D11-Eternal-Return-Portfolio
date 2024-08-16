#include "pch.h"
#include "Wickline.h"

#include "WicklineStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "OBBComponent.h"
#include "SphereComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"
#include "CameraComponent.h"

#include "Projectile.h"
#include "BillboardProjectile.h"
#include "MathUtility.h"

#include "Survivor.h"

HRESULT Client::CWickline::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_OBJECT);

	{
		m_eBossType = EBossType::WICKLINE;
		m_fAttackRange = 4.0f;
		m_fCurMoveSpeed = 5.5f;
		m_fCurHP = 1500.0f;
		m_fMaxHP = 1500.0f;
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Wickline");
		m_wpSkeletalMeshComponent.lock()->SetVertexShaderDesc(L"VS_SkeletalMesh");
		m_wpSkeletalMeshComponent.lock()->SetPixelShaderDesc(L"PS_SkeletalMesh");
	}

	{
		m_wpNavigationComponent = CreateActorComponent<CNavigationComponent>(L"NavigationComponent", EComponentType::NAVIGATION);
		m_wpNavigationComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpNavigationComponent.lock()->SetNavigation(L"LumiaNavigation");
		m_wpNavigationComponent.lock()->SetCurCellIndex(3941);// 3941
	}

	{
		m_wpBossStateComponent = CreateActorComponent<CWicklineStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpSecondSkillOBBComponent = CreateActorComponent<COBBComponent>(L"OBBComponent", EComponentType::OBB);
		m_wpSecondSkillOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpHitEffectComponent = CreateActorComponent<CEffectComponent>(m_wstrActorName + L"HitEffectComponent", EComponentType::EFFECT);
		m_wpHitEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpHitEffectComponent.lock()->OffMeshEffect(); 
	}

	{
		m_wpSecondSkillEffectComponent = CreateActorComponent<CEffectComponent>(m_wstrActorName + L"SecondSkillEffectComponent", EComponentType::EFFECT);
		m_wpSecondSkillEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpSecondSkillEffectComponent.lock()->OffMeshEffect();
	}

	{
		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpCameraComponent = CreateActorComponent<CCameraComponent>(L"WicklineCameraComponent", EComponentType::CAMERA);
		m_wpCameraComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpCameraComponent.lock()->SetOffset({ 0.0f, 0.0f, 0.0f });
		m_wpCameraComponent.lock()->SetRadius(3.0f);

		m_wpCameraComponent.lock()->SetThisCameraOnAir();
		m_wpCameraComponent.lock()->SetCameraWalk(true);
	}
	return CBoss::PreInitialize();
}

HRESULT Client::CWickline::Initialize()
{
	if (FAILED(CBoss::Initialize())) { return E_FAIL; }
	
	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::WAIT,			L"WAIT",			{ "Wickline_01_wait" },			true);
		
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::RUN,				L"RUN",				{ "Wickline_01_run" },			true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::ATTACK_01,		L"ATTACK_01",		{ "Wickline_01_atk01" },		false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::ATTACK_02,		L"ATTACK_02",		{ "Wickline_01_atk02" },		false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_01_BEGIN,	L"SKILL_01_BEGIN",	{ "Wickline_01_skill1_loop" },	false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_01,		L"SKILL_01",		{ "Wickline_01_skill1_end" },	false);
		
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_02,		L"SKILL_02",		{ "Wickline_01_skill2" },		false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_03,		L"SKILL_03",		{ "Wickline_01_skill1_loop" },	false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::END_BATTLE,		L"END_BATTLE",		{ "Wickline_01_endbattle" },	false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::DEATH,			L"DEATH",			{ "Wickline_01_death" },		false);

		m_wpSkeletalMeshComponent.lock()->SetComponentLocalScale({ 1.2f, 1.2f, 1.2f });
		m_wpSkeletalMeshComponent.lock()->SetComponentLocalRotate(Vector3::Up, 90.0f);
	}
	
	{
		m_wpBodySphereComponent.lock()->SetRadius(1.2f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.6f, 0.0f });
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	{
		m_wpSecondSkillOBBComponent.lock()->SetCenter({ 0.0f, 0.5f, 3.0f });
		m_wpSecondSkillOBBComponent.lock()->SetExtent({ 0.5f, 0.5f, 3.0f });
		m_wpSecondSkillOBBComponent.lock()->SetActive(false);
		m_wpSecondSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_SKILL);
		m_wpSecondSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
	}

	{
		m_wpHitEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHitStar01");

		m_wpSecondSkillEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXWicklineSkill01HitSpread");
	}

	return S_OK;
}

HRESULT Client::CWickline::PostInitialize()
{
	if (FAILED(CBoss::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CWickline::BeginPlay()
{
	if (FAILED(CBoss::BeginPlay())) { return E_FAIL; }

	// TODO; 임시로 스폰 위치를 설정합니다.
	SetActorLocalPosition(m_wpNavigationComponent.lock()->GetCentroidPosition(3941));// 3941
	return S_OK;
}

int32 Client::CWickline::PreTick(float _fDeltaSeconds)
{
	switch (CBoss::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecWicklineProjectiles)
	{
		spProjectile->PreTick(_fDeltaSeconds);
	}

	return 0;
}

int32 Client::CWickline::Tick(float _fDeltaSeconds)
{
	switch (CBoss::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecWicklineProjectiles)
	{
		spProjectile->Tick(_fDeltaSeconds);
	}

	return 0;
}

int32 Client::CWickline::PostTick(float _fDeltaSeconds)
{
	switch (CBoss::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecWicklineProjectiles)
	{
		spProjectile->PostTick(_fDeltaSeconds);
	}

	return 0;
}

HRESULT Client::CWickline::EndPlay()
{
	if (FAILED(CBoss::EndPlay())) { return E_FAIL; }

	for (const auto& spProjectile : m_vecWicklineProjectiles)
	{
		spProjectile->EndPlay();
	}

	return S_OK;
}

void Client::CWickline::Render()
{
	CBoss::Render();

	for (const auto& spProjectile : m_vecWicklineProjectiles)
	{
		spProjectile->Render();
	}
}

void Client::CWickline::Release()
{
	for (auto& spProjectile : m_vecWicklineProjectiles)
	{
		spProjectile->Release();
		spProjectile = nullptr;
	}

	CBoss::Release();
}

void Client::CWickline::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionEnter(_spSrc, _spDst);
}

void Client::CWickline::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionStay(_spSrc, _spDst);
}

void Client::CWickline::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionExit(_spSrc, _spDst);
}

void Client::CWickline::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	case EBossAnimState::ATTACK_02:
	{
		m_wpSurvivor.lock()->TakeDamage(80.0f, nullptr, static_pointer_cast<CWickline>(shared_from_this()));
		string strIndex = to_string(CMathUtility::GetRandomInteger(1, 2));
		m_wpSoundComponent.lock()->PlaySoundEx("wicklineAttack_r" + strIndex, ESoundType::CREATURE_01);
	}
	break;

	case EBossAnimState::SKILL_01_BEGIN:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(0, 4));
		m_wpSoundComponent.lock()->PlaySoundEx("wicklineDay_" + strIndex, ESoundType::CREATURE_02);
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
	}
	break;

	case EBossAnimState::SKILL_02:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(0, 4));
		m_wpSoundComponent.lock()->PlaySoundEx("wicklineDay_" + strIndex, ESoundType::CREATURE_02);
		m_wpSecondSkillOBBComponent.lock()->SetActive(true);
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(0.8f);
	}
	break;

	case EBossAnimState::SKILL_03:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(0, 4));
		m_wpSoundComponent.lock()->PlaySoundEx("wicklineDay_" + strIndex, ESoundType::CREATURE_02);
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
	}
	break;

	case EBossAnimState::DEATH:
		m_wpSoundComponent.lock()->PlaySoundEx("wicklineDie", ESoundType::CREATURE_01);
		break;
	}
}

void Client::CWickline::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::SKILL_02:
	{
		if (0.05f <= _fRatio && !m_bSecondSkillReady)
		{
			m_wpSoundComponent.lock()->PlaySoundEx("wickline_Skill02_Activation", ESoundType::CREATURE_01);
			m_bSecondSkillReady = true;
		}

		if (0.55f <= _fRatio && !m_bSecondSkillFire)
		{
			m_wpSoundComponent.lock()->PlaySoundEx("wickline_Skill02_Impact", ESoundType::CREATURE_01);
			m_wpSecondSkillEffectComponent.lock()->PlayMeshEffect();
			m_bSecondSkillFire = true;

			unordered_set<shared_ptr<CShapeComponent>> usetShapeComponents = m_wpSecondSkillOBBComponent.lock()->GetShapeComponents();
			for (const auto& spShapeComponent : usetShapeComponents)
			{
				if (spShapeComponent->GetCollisionLayer() == ECollisionLayer::PLAYER)
				{
					m_wpSurvivor.lock()->PlaySoundEx("wickline_Skill02_Hit", ESoundType::CREATURE_01);
					m_wpSurvivor.lock()->TakeDamage(200.0f, nullptr, nullptr);
				}
			}
		}
	}
	break;

	case EBossAnimState::SKILL_01_BEGIN:
	{
		if (0.1f <= _fRatio && !m_bFirstSkillReady[0])
		{
			m_bFirstSkillReady[0] = true;
			CreateFirstSkillProjectile(-10.0f);
			m_wpSoundComponent.lock()->PlaySoundEx("Celine_Skill02_Explosion", ESoundType::EFFECT_03, 1.0f);
		}

		else if (0.3f <= _fRatio && !m_bFirstSkillReady[1])
		{
			m_bFirstSkillReady[1] = true;
			CreateFirstSkillProjectile(-5.0f);
			m_wpSoundComponent.lock()->PlaySoundEx("Celine_Skill02_Explosion", ESoundType::EFFECT_03, 1.0f);
		}

		else if (0.5f <= _fRatio && !m_bFirstSkillReady[2])
		{
			m_bFirstSkillReady[2] = true;
			CreateFirstSkillProjectile(0.0f);
			m_wpSoundComponent.lock()->PlaySoundEx("Celine_Skill02_Explosion", ESoundType::EFFECT_03, 1.0f);
		}

		else if (0.7f <= _fRatio && !m_bFirstSkillReady[3])
		{
			m_bFirstSkillReady[3] = true;
			CreateFirstSkillProjectile(5.0f);
			m_wpSoundComponent.lock()->PlaySoundEx("Celine_Skill02_Explosion", ESoundType::EFFECT_03, 1.0f);
		}

		else if (0.9f <= _fRatio && !m_bFirstSkillReady[4])
		{
			m_bFirstSkillReady[4] = true;
			CreateFirstSkillProjectile(10.0f);
			m_wpSoundComponent.lock()->PlaySoundEx("Celine_Skill02_Explosion", ESoundType::EFFECT_03, 1.0f);
		}
	}
	break;

	case EBossAnimState::SKILL_03:
	{
		if (0.1f <= _fRatio && !m_bThirdSkillApply[0])
		{
			m_bThirdSkillApply[0] = true;
			FireThirdSkillTrap();
		}

		else if (0.4f <= _fRatio && !m_bThirdSkillApply[1])
		{
			m_bThirdSkillApply[1] = true;
			FireThirdSkillTrap();
		}

		else if (0.7f <= _fRatio && !m_bThirdSkillApply[2])
		{
			m_bThirdSkillApply[2] = true;
			FireThirdSkillTrap();
		}
	}
	break;
	}
}

void Client::CWickline::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	case EBossAnimState::ATTACK_02:
		break;
		
	case EBossAnimState::SKILL_01_BEGIN:
		m_bFirstSkillReady = { false, false, false, false, false };
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		break;

	case EBossAnimState::SKILL_02:
		m_bSecondSkillReady = false;
		m_bSecondSkillFire = false;

		if (++m_iSumSecondSkillFire >= m_iMaxSecondSkillFire)
		{
			m_iSumSecondSkillFire = 0;
			m_wpBossStateComponent.lock()->SetBossState(EBossState::CHASE);
			m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
			m_wpSecondSkillOBBComponent.lock()->SetActive(false);
		}
		break;

	case EBossAnimState::SKILL_03:
		m_bThirdSkillApply[0] = false;
		m_bThirdSkillApply[1] = false;
		m_bThirdSkillApply[2] = false;
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		break;

	case EBossAnimState::DEATH:
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		m_wpHitEffectComponent.lock()->StopMeshEffect();
		m_wpSecondSkillEffectComponent.lock()->StopMeshEffect();
		break;
	}
}

void Client::CWickline::CreateFirstSkillProjectile(float _fDegree)
{
	Vector3 vWicklinePosition = GetActorWorldPosition().value();
	Vector3 vSurvivorPosition = m_wpSurvivor.lock()->GetActorWorldPosition().value();
	Vector3 vForward = vSurvivorPosition - vWicklinePosition;
	vForward.Normalize();

	Vector3 vSpawnPosition = vWicklinePosition + Vector3(0.0f, 1.0f, 0.0f);
	/*
	bool bFoundDead = false;

	for (const auto& spProjectile : m_vecWicklineProjectiles)
	{
		if (spProjectile->IsDead() && spProjectile->GetProjectileType() == EProjectileType::WICKLINE_SKILL_01)
		{
			spProjectile->Revive
			(
				vSpawnPosition,
				vForward,
				3.2f,
				0.1f,
				300.0f,
				nullptr,
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::WICKLINE_SKILL_01,
				EProjectileState::MOVE
			);
			bFoundDead = true;
			break;
		}
	}

	if (bFoundDead == false)
	{
		shared_ptr<CProjectile> spProjectile = CProjectile::Create<CProjectile>
		(
			vSpawnPosition,
			vForward,
			3.2f,
			0.1f,
			300.0f,
			nullptr,
			static_pointer_cast<CActor>(shared_from_this()),
			EProjectileType::WICKLINE_SKILL_01,
			EProjectileState::MOVE,
			(int32)m_vecWicklineProjectiles.size()
		);
		m_vecWicklineProjectiles.push_back(spProjectile);
	}
	*/

	int32 iSumFirstSkills = 3;
	int32 iNumFirstSkills = 0;
	Matrix matRotate = Matrix::CreateRotationY(XMConvertToRadians(360.0f / iSumFirstSkills + _fDegree));

	for (const auto& spProjectile : m_vecWicklineProjectiles)
	{
		if (3 < iNumFirstSkills)
		{
			iNumFirstSkills = 0;
			return;
		}

		if (spProjectile->IsDead() && (spProjectile->GetProjectileType() == EProjectileType::WICKLINE_SKILL_01))
		{
			vForward = vForward.TransformNormal(vForward, matRotate);

			spProjectile->Revive
			(
				vSpawnPosition,
				vForward,
				3.2f,
				0.1f,
				150.0f,
				m_wpSurvivor.lock(),
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::WICKLINE_SKILL_01,
				EProjectileState::MOVE
			);
			iNumFirstSkills++;
		}
	}

	for (int32 iIndex = iNumFirstSkills; iIndex < 3; ++iIndex)
	{
		vForward = vForward.TransformNormal(vForward, matRotate);

		shared_ptr<CProjectile> spProjectile = CProjectile::Create<CProjectile>
			(
				vSpawnPosition,
				vForward,
				3.2f,
				0.1f,
				150.0f,
				m_wpSurvivor.lock(),
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::WICKLINE_SKILL_01,
				EProjectileState::MOVE,
				(int32)m_vecWicklineProjectiles.size()
			);
		iNumFirstSkills++;

		m_vecWicklineProjectiles.push_back(spProjectile);
	}
}

void Client::CWickline::FireThirdSkillTrap()
{
	Vector3 vPosition = m_wpSurvivor.lock()->GetActorWorldPosition().value();

	bool bFoundDead = false;

	for (const auto& spProjectile : m_vecWicklineProjectiles)
	{
		if (spProjectile->IsDead() && spProjectile->GetProjectileType() == EProjectileType::WICKLINE_SKILL_03)
		{
			spProjectile->Revive
			(
				vPosition,
				Vector3::Forward,
				11.0f,
				0.0f,
				300.0f,
				m_wpSurvivor.lock(),
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::WICKLINE_SKILL_03,
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
				11.0f,
				0.0f,
				300.0f,
				m_wpSurvivor.lock(),
				static_pointer_cast<CActor>(shared_from_this()),
				EProjectileType::WICKLINE_SKILL_03,
				EProjectileState::STAY,
				(int32)m_vecWicklineProjectiles.size()
			);
		m_vecWicklineProjectiles.push_back(spProjectile);
	}
}
