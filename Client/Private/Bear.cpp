#include "pch.h"
#include "Bear.h"

#include "BearStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "SphereComponent.h"
#include "OBBComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"

#include "Survivor.h"

#include "MathUtility.h"

HRESULT Client::CBear::PreInitialize()
{
	{
		m_eWildAnimalType = EWildAnimalType::BEAR;
		m_eWildAnimalHabitType = EWildAnimalHabitType::NOCTURNAL;
		m_fAttackRange = 2.5f;
		m_fCurMoveSpeed = 4.0f;
		m_fCurHP = 300.0f;
		m_fMaxHP = 300.0f;
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent"
			, EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Bear");
		m_wpSkeletalMeshComponent.lock()->SetVertexShaderDesc(L"VS_SkeletalMesh");
		m_wpSkeletalMeshComponent.lock()->SetPixelShaderDesc(L"PS_SkeletalMesh");
	}

	{
		m_wpNavigationComponent = CreateActorComponent<CNavigationComponent>(L"NavigationComponent", EComponentType::NAVIGATION);
		m_wpNavigationComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpNavigationComponent.lock()->SetNavigation(L"LumiaNavigation");
		m_wpNavigationComponent.lock()->SetCurCellIndex(m_iSpawnCellIndex);
	}
	
	{
		m_wpWildAnimalStateComponent = CreateActorComponent<CBearStateComponent>(L"StateComponent", EComponentType::STATE);
	}
	
	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpSkillOBBComponent = CreateActorComponent<COBBComponent>(L"SkillComponent", EComponentType::OBB);
		m_wpSkillOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpSkillEffectComponent = CreateActorComponent<CEffectComponent>(m_wstrActorName + L"SkillEffectComponent", EComponentType::EFFECT);
		m_wpSkillEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpSkillEffectComponent.lock()->OffMeshEffect();

		m_wpHitEffectComponent = CreateActorComponent<CEffectComponent>(m_wstrActorName + L"HitEffectComponent", EComponentType::EFFECT);
		m_wpHitEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpHitEffectComponent.lock()->OffMeshEffect();
	}

	{
		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	SetActorLocalRotate(Vector3::Up, m_fSpawnYDegree);

	return CWildAnimal::PreInitialize();
}

HRESULT Client::CBear::Initialize()
{
	if (FAILED(CWildAnimal::Initialize())) { return E_FAIL; }

	/*
	* TODO; 추가할 애니메이션들
	* Bear_01_appear
	* Bear_01_appearwait
	* Bear_01_dance
	*/

	{
		// 낮일 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SLEEP_BEGIN,	L"SLEEP_BEGIN",	{ "Bear_01_sleep_start" },				false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SLEEP,			L"SLEEP",		{ "Bear_01_sleep" },					true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAKE,			L"WAKE",		{ "Bear_01_wake" },						false);
		
		// 밤일 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAIT,			L"WAIT",		{ "Bear_01_wait" },						true);
		
		// 경계 안에 들어갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_BEGIN,	L"BEWARE_BEGIN",{ "Bear_01_beware_start" },				false);
		
		// 경계 안에 있을 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE,		L"BEWARE",		{ "Bear_01_beware_loop" },				true);

		// 경계 밖으로 나갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_END,	L"BEWARE_END",	{ "Bear_01_beware_end" },				false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::RUN,			L"RUN",			{ "Bear_01_run" },						true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_01,		L"ATTACK",		{ "Bear_01_atk01" },					false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_02,		L"ATTACK",		{ "Bear_01_atk02" },					false);
		
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SKILL,			L"SKILL",		{ "Bear_01_skill01" },					false);
		
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::END_BATTLE,	L"END_BATTLE",	{ "Bear_01_endbattle" },				false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::DEATH,			L"DEATH",		{ "Bear_01_death" },					false);
	
		m_wpSkeletalMeshComponent.lock()->SetComponentLocalScale({ 0.7f, 0.7f, 0.7f });
	}
	
	{
		m_wpBodySphereComponent.lock()->SetRadius(1.6f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.8f, 0.0f });
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	{
		m_wpSkillOBBComponent.lock()->SetCenter({ 0.0f, 0.5f, 2.0f });
		m_wpSkillOBBComponent.lock()->SetExtent({ 1.0f, 0.5f, 2.0f });
		m_wpSkillOBBComponent.lock()->SetActive(false);
		m_wpSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_SKILL);
		m_wpSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
	}

	{
		m_wpSkillEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXBearSkillHitRange");

		m_wpHitEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHitStar01");
	}
	return S_OK;
}

HRESULT Client::CBear::PostInitialize()
{
	if (FAILED(CWildAnimal::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBear::BeginPlay()
{
	if (FAILED(CWildAnimal::BeginPlay())) { return E_FAIL; }

	SetActorLocalPosition(m_vSpawnPosition);
	return S_OK;
}

int32 Client::CBear::PreTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBear::Tick(float _fDeltaSeconds)
{
	switch (CWildAnimal::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBear::PostTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CBear::EndPlay()
{
	if (FAILED(CWildAnimal::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CBear::Render()
{
	CWildAnimal::Render();
}

void Client::CBear::Release()
{
	CWildAnimal::Release();
}

void Client::CBear::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionEnter(_spSrc, _spDst);
}

void Client::CBear::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionStay(_spSrc, _spDst);
}

void Client::CBear::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionExit(_spSrc, _spDst);
}

void Client::CBear::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::ATTACK_01:
	case EWildAnimalAnimState::ATTACK_02:
		m_wpSurvivor.lock()->TakeDamage(160.0f, nullptr, static_pointer_cast<CBear>(shared_from_this()));
		m_wpSoundComponent.lock()->PlaySoundEx("bearAttack", ESoundType::CREATURE_01);
		m_wpSoundComponent.lock()->PlaySoundEx("boarHit", ESoundType::HIT_01);
		break;

	case EWildAnimalAnimState::WAKE:
	{
		// string strIndex = to_string(CMathUtility::GetRandomInteger(1, 2));
		// m_wpSoundComponent.lock()->PlaySoundEx("bearWakeUp_Ing_v" + strIndex, ESoundType::CREATURE_01);
	}
	break;

	case EWildAnimalAnimState::BEWARE_BEGIN:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(1, 2));
		m_wpSoundComponent.lock()->PlaySoundEx("bearWakeUp_Start_v" + strIndex, ESoundType::CREATURE_01);
	}
	break;

	case EWildAnimalAnimState::SKILL:
		m_wpSoundComponent.lock()->PlaySoundEx("bear_Skill_Activation", ESoundType::CREATURE_01);
		m_wpSkillEffectComponent.lock()->PlayMeshEffect();
		m_wpSkillOBBComponent.lock()->SetActive(true);
		break;

	case EWildAnimalAnimState::DEATH:
		m_wpSoundComponent.lock()->PlaySoundEx("bearDie", ESoundType::CREATURE_01);
		m_wpSkillEffectComponent.lock()->OffMeshEffect();
		break;
	}
}

void Client::CBear::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::SKILL:
	{
		if (0.4f <= _fRatio && !m_bSkillApply)
		{
			m_bSkillApply = true;

			unordered_set<shared_ptr<CShapeComponent>> usetShapeComponents = m_wpSkillOBBComponent.lock()->GetShapeComponents();
			for (const auto& spShapeComponent : usetShapeComponents)
			{
				if (spShapeComponent->GetCollisionLayer() == ECollisionLayer::PLAYER)
				{
					spShapeComponent->GetOwnerActor()->TakeDamage(240.0f, nullptr, nullptr);
					m_wpSoundComponent.lock()->PlaySoundEx("bear_Skill_Impact", ESoundType::EFFECT_01);
				}
			}
		}
	}
	break;

	default:
		break;
	}
}

void Client::CBear::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::SKILL:
		m_bSkillApply = false;
		m_wpSkillOBBComponent.lock()->SetActive(false);
		m_wpSkillEffectComponent.lock()->OffMeshEffect();
		break;

	case EWildAnimalAnimState::DEATH:
		m_wpSkillOBBComponent.lock()->SetActive(false);
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;
	}
}
