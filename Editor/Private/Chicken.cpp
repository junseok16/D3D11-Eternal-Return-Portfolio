#include "pch.h"
#include "Chicken.h"

#include "ChickenStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "SphereComponent.h"

HRESULT Editor::CChicken::PreInitialize()
{
	{
		m_eWildAnimalHabitType = EWildAnimalHabitType::DIURNAL;
		m_fAttackRange = 2.0f;
		m_fCurMoveSpeed = 3.5f;
		m_fCurHP = 40.0f;
		m_fMaxHP = 40.0f;
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Chicken");
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
		m_wpWildAnimalStateComponent = CreateActorComponent<CChickenStateComponent>(L"StateComponent", EComponentType::STATE);
	}
	
	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	return CWildAnimal::PreInitialize();
}

HRESULT Editor::CChicken::Initialize()
{
	if (FAILED(CWildAnimal::Initialize())) { return E_FAIL; }

	/*
	* TODO; 추가할 애니메이션들
	* Chicken_01_appear
	* Chicken_01_dance
	*/

	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAIT,			L"WAIT",		{ "Chicken_01_wait" },			true);
		
		// 경계 안에 들어갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_BEGIN,	L"BEWARE_BEGIN",{ "chicken_01_beware_start" },	false);
		
		// 경계 안에 있을 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE,		L"BEWARE",		{ "chicken_01_beware_loop" },	true);

		// 경계 밖으로 나갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_END,	L"BEWARE_END",	{ "chicken_01_beware_end" },	false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::RUN,			L"RUN",			{ "Chicken_01_run" },			true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_01,		L"ATTACK_01",	{ "Chicken_01_atk01" },			false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_02,		L"ATTACK_02",	{ "Chicken_01_atk02" },			false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::END_BATTLE,	L"END_BATTLE",	{ "Chicken_01_endbattle" },		false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::DEATH,			L"DEATH",		{ "Chicken_01_death" },			false);

		m_wpSkeletalMeshComponent.lock()->SetComponentLocalScale({ 0.7f, 0.7f, 0.7f });
	}
	
	{
		m_wpBodySphereComponent.lock()->SetRadius(0.6f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.3f, 0.0f });
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	return S_OK;
}

HRESULT Editor::CChicken::PostInitialize()
{
	if (FAILED(CWildAnimal::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CChicken::BeginPlay()
{
	if (FAILED(CWildAnimal::BeginPlay())) { return E_FAIL; }

	SetActorLocalPosition(m_vSpawnPosition);
	return S_OK;
}

int32 Editor::CChicken::PreTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CChicken::Tick(float _fDeltaSeconds)
{
	switch (CWildAnimal::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CChicken::PostTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CChicken::EndPlay()
{
	if (FAILED(CWildAnimal::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CChicken::Render()
{
	CWildAnimal::Render();
}

void Editor::CChicken::Release()
{
	CWildAnimal::Release();
}

void Editor::CChicken::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionEnter(_spSrc, _spDst);
}

void Editor::CChicken::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionStay(_spSrc, _spDst);
}

void Editor::CChicken::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionExit(_spSrc, _spDst);
}

void Editor::CChicken::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CChicken::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CChicken::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::DEATH:
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;
	}
}
