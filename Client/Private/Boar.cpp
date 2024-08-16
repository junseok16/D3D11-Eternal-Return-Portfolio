#include "pch.h"
#include "Boar.h"

#include "BoarStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "SphereComponent.h"
#include "OBBComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"

#include "Survivor.h"

HRESULT Client::CBoar::PreInitialize()
{
	{
		m_eWildAnimalType = EWildAnimalType::BOAR;
		m_eWildAnimalHabitType = EWildAnimalHabitType::DIURNAL;
		m_fAttackRange = 2.0f;
		m_fCurMoveSpeed = 3.5f;
		m_fCurHP = 240.0f;
		m_fMaxHP = 240.0f;
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Boar");
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
		m_wpWildAnimalStateComponent = CreateActorComponent<CBoarStateComponent>(L"StateComponent", EComponentType::STATE);
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

HRESULT Client::CBoar::Initialize()
{
	if (FAILED(CWildAnimal::Initialize())) { return E_FAIL; }

	/*
	* TODO; �߰��� �ִϸ��̼ǵ�
	* Boar_01_appear
	* Boar_01_dance
	*/

	{
		// ���� ��
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAIT,			L"WAIT",		{ "Boar_01_wait" },						true);
		
		// ��� �ȿ� �� ��
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_BEGIN,	L"BEWARE_BEGIN",{ "boar_01_beware_start" },				false);
		
		// ��� �ȿ� ���� ��
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE,		L"BEWARE",		{ "boar_01_beware_loop" },				true);

		// ��� ������ ���� ��
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_END,	L"BEWARE_END",	{ "boar_01_beware_end" },				false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::RUN,			L"RUN",			{ "Boar_01_run" },						true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_01,		L"ATTACK",		{ "Boar_01_atk01" },					false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_02,		L"ATTACK",		{  "Boar_01_atk02" },					false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SKILL_BEGIN,	L"SKILL_BEGIN",	{ "Boar_01_skill01_ready" },			false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SKILL,			L"SKILL",		{ "Boar_01_skill01_assault" },			false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::END_BATTLE,	L"END_BATTLE",	{ "Boar_01_endbattle" },				false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::DEATH,			L"DEATH",		{ "Boar_01_death" },					false);
	}
	
	{
		m_wpBodySphereComponent.lock()->SetRadius(2.0f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 1.0f, 0.0f });
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	{
		m_wpSkillOBBComponent.lock()->SetCenter({ 0.0f, 0.5f, 0.6f });
		m_wpSkillOBBComponent.lock()->SetExtent({ 1.0f, 1.0f, 0.2f });
		m_wpSkillOBBComponent.lock()->SetActive(false);
		m_wpSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_SKILL);
		m_wpSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
	}

	{
		m_wpSkillEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXBoarSkillHitRange");

		m_wpHitEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHitStar01");
	}
	return S_OK;
}

HRESULT Client::CBoar::PostInitialize()
{
	if (FAILED(CWildAnimal::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBoar::BeginPlay()
{
	if (FAILED(CWildAnimal::BeginPlay())) { return E_FAIL; }

	SetActorLocalPosition(m_vSpawnPosition);
	return S_OK;
}

int32 Client::CBoar::PreTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBoar::Tick(float _fDeltaSeconds)
{
	switch (CWildAnimal::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBoar::PostTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CBoar::EndPlay()
{
	if (FAILED(CWildAnimal::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CBoar::Render()
{
	CWildAnimal::Render();
}

void Client::CBoar::Release()
{
	CWildAnimal::Release();
}

void Client::CBoar::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionEnter(_spSrc, _spDst);
}

void Client::CBoar::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionStay(_spSrc, _spDst);
}

void Client::CBoar::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionExit(_spSrc, _spDst);
}

void Client::CBoar::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::ATTACK_01:
	case EWildAnimalAnimState::ATTACK_02:
		m_wpSurvivor.lock()->TakeDamage(120.0f, nullptr, static_pointer_cast<CBoar>(shared_from_this()));
		m_wpSoundComponent.lock()->PlaySoundEx("boar_attack", ESoundType::CREATURE_01);
		m_wpSoundComponent.lock()->PlaySoundEx("bearHit", ESoundType::HIT_01);
		break;

	case EWildAnimalAnimState::RUN:
		m_wpSkillOBBComponent.lock()->SetActive(false);
		break;

	case EWildAnimalAnimState::SKILL_BEGIN:
		m_wpSoundComponent.lock()->PlaySoundEx("boar_Skill_Activation", ESoundType::CREATURE_01);
		m_wpSkillEffectComponent.lock()->PlayMeshEffect();
		break;

	case EWildAnimalAnimState::SKILL:
		m_wpSoundComponent.lock()->PlaySoundEx("boarAttack", ESoundType::CREATURE_01);
		m_wpSkillOBBComponent.lock()->SetActive(true);
		m_wpSkillEffectComponent.lock()->OffMeshEffect();
		break;

	case EWildAnimalAnimState::DEATH:
		m_wpSoundComponent.lock()->PlaySoundEx("boarDie", ESoundType::CREATURE_01);
		m_wpSkillEffectComponent.lock()->OffMeshEffect();
		break;
	}
}

void Client::CBoar::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::SKILL:
	{
		Vector3 vForward = GetActorWorldForwardVector().value();
		vForward.Normalize();

		Vector3 vLocalPosition = GetActorLocalPosition().value();
		vLocalPosition += vForward * m_fDeltaSeconds * m_fCurMoveSpeed * 4.0f;

		Vector3 vOutWorldPosition = Vector3::Zero;
		if (!m_wpNavigationComponent.lock()->IsValidCell(vLocalPosition, vOutWorldPosition))
		{
			m_wpWildAnimalStateComponent.lock()->SetWildAnimalState(EWildAnimalState::CHASE);
			return;
		}
		SetActorLocalPosition(vOutWorldPosition);

		if (m_bSkillApply)
		{
			break;
		}

		// ���� �浹�� ���, ������ �о���ϴ�.
		std::unordered_set<std::shared_ptr<CShapeComponent>>& usetShapeComponents = m_wpSkillOBBComponent.lock()->GetShapeComponents();
		for (const auto& spShapeComponent : usetShapeComponents)
		{
			if (spShapeComponent->GetCollisionLayer() != ECollisionLayer::PLAYER) { continue; }

			shared_ptr<CSurvivor> spSurvivor = dynamic_pointer_cast<CSurvivor>(spShapeComponent->GetOwnerActor());
			
			if (spSurvivor)
			{
				if (spSurvivor->GetCurHP() <= 0.0f) { break; }

				m_bSkillApply = true;
				spSurvivor->TakeDamage(160.0f, nullptr, static_pointer_cast<CBoar>(shared_from_this()));
				m_wpSoundComponent.lock()->PlaySoundEx("bearHit", ESoundType::HIT_01);
				break;
			}
		}
	}
	break;
	}
}

void Client::CBoar::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::SKILL:
	{
		if (++m_iSumSkillFire >= m_iMaxSkillFire)
		{
			m_bSkillApply = false;
			m_iSumSkillFire = 0;
			m_wpWildAnimalStateComponent.lock()->SetWildAnimalState(EWildAnimalState::CHASE);
			m_wpSkillOBBComponent.lock()->SetActive(false);
		}
	}
	break;

	case EWildAnimalAnimState::DEATH:
		m_wpSkillOBBComponent.lock()->SetActive(false);
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;
	}
}
