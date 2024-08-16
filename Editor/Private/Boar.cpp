#include "pch.h"
#include "Boar.h"

#include "BoarStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "SphereComponent.h"
#include "OBBComponent.h"

HRESULT Editor::CBoar::PreInitialize()
{
	{
		m_eWildAnimalHabitType = EWildAnimalHabitType::DIURNAL;
		m_fAttackRange = 2.0f;
		m_fCurMoveSpeed = 3.5f;
		m_fCurHP = 120.0f;
		m_fMaxHP = 120.0f;
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

	return CWildAnimal::PreInitialize();
}

HRESULT Editor::CBoar::Initialize()
{
	if (FAILED(CWildAnimal::Initialize())) { return E_FAIL; }

	/*
	* TODO; 추가할 애니메이션들
	* Boar_01_appear
	* Boar_01_dance
	*/

	{
		// 낮일 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAIT,			L"WAIT",		{ "Boar_01_wait" },						true);
		
		// 경계 안에 들어갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_BEGIN,	L"BEWARE_BEGIN",{ "boar_01_beware_start" },				false);
		
		// 경계 안에 있을 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE,		L"BEWARE",		{ "boar_01_beware_loop" },				true);

		// 경계 밖으로 나갈 때
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
		m_wpBodySphereComponent.lock()->SetRadius(1.0f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.5f, 0.0f });
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

	return S_OK;
}

HRESULT Editor::CBoar::PostInitialize()
{
	if (FAILED(CWildAnimal::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CBoar::BeginPlay()
{
	if (FAILED(CWildAnimal::BeginPlay())) { return E_FAIL; }

	SetActorLocalPosition(m_vSpawnPosition);
	return S_OK;
}

int32 Editor::CBoar::PreTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CBoar::Tick(float _fDeltaSeconds)
{
	switch (CWildAnimal::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CBoar::PostTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CBoar::EndPlay()
{
	if (FAILED(CWildAnimal::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CBoar::Render()
{
	CWildAnimal::Render();
}

void Editor::CBoar::Release()
{
	CWildAnimal::Release();
}

void Editor::CBoar::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionEnter(_spSrc, _spDst);
}

void Editor::CBoar::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionStay(_spSrc, _spDst);
}

void Editor::CBoar::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionExit(_spSrc, _spDst);
}

void Editor::CBoar::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::SKILL:
		m_wpSkillOBBComponent.lock()->SetActive(true);
		break;
	}
}

void Editor::CBoar::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
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
	}
	break;
	}
}

void Editor::CBoar::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::SKILL:
		m_wpSkillOBBComponent.lock()->SetActive(false);
		break;

	case EWildAnimalAnimState::DEATH:
		m_wpSkillOBBComponent.lock()->SetActive(false);
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;
	}
}
