#include "pch.h"
#include "Dog.h"

#include "DogStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "SphereComponent.h"

HRESULT Editor::CDog::PreInitialize()
{
	{
		m_eWildAnimalHabitType = EWildAnimalHabitType::NOCTURNAL;
		m_fAttackRange = 2.0f;
		m_fCurMoveSpeed = 3.5f;
		m_fCurHP = 70.0f;
		m_fMaxHP = 70.0f;
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Dog");
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
		m_wpWildAnimalStateComponent = CreateActorComponent<CDogStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	return CWildAnimal::PreInitialize();
}

HRESULT Editor::CDog::Initialize()
{
	if (FAILED(CWildAnimal::Initialize())) { return E_FAIL; }

	/*
	* TODO; 추가할 애니메이션들
	* dog_01_appear
	* Dog_01_appearwait
	* Dog_01_dance
	*/

	{
		// 낮일 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SLEEP_BEGIN,	L"SLEEP_BEGIN",	{ "Dog_01_sleep_start" },								false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SLEEP,			L"SLEEP",		{ "dog_01_sleep" },										true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAKE,			L"WAKE",		{ "dog_01_wake" },										false);

		// 밤일 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAIT,			L"WAIT",		{ "Dog_01_wait" },										true);
		
		// 경계 안에 들어갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_BEGIN,	L"BEWARE_BEGIN",{ "dog_01_beware_start" },								false);
		
		// 경계 안에 있을 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE,		L"BEWARE",		{ "dog_01_beware_loop", "dog_01_beware_loop_wait" },	true);

		// 경계 밖으로 나갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_END,	L"BEWARE_END",	{ "dog_01_beware_end" },								false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::RUN,			L"RUN",			{ "Dog_01_run" },										true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_01,		L"ATTACK_01",	{ "Dog_01_atk01" },										false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_02,		L"ATTACK_02",	{ "Dog_01_atk02" },										false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::END_BATTLE,	L"END_BATTLE",	{ "dog_01_endbattle" },									false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::DEATH,			L"DEATH",		{ "Dog_01_death" },										false);

		m_wpSkeletalMeshComponent.lock()->SetComponentLocalScale({ 0.8f, 0.8f, 0.8f });
	}
	
	{
		m_wpBodySphereComponent.lock()->SetRadius(1.0f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.5f, 0.0f });
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	return S_OK;
}

HRESULT Editor::CDog::PostInitialize()
{
	if (FAILED(CWildAnimal::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CDog::BeginPlay()
{
	if (FAILED(CWildAnimal::BeginPlay())) { return E_FAIL; }

	SetActorLocalPosition(m_vSpawnPosition);
	return S_OK;
}

int32 Editor::CDog::PreTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CDog::Tick(float _fDeltaSeconds)
{
	switch (CWildAnimal::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CDog::PostTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CDog::EndPlay()
{
	if (FAILED(CWildAnimal::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CDog::Render()
{
	CWildAnimal::Render();
}

void Editor::CDog::Release()
{
	CWildAnimal::Release();
}

void Editor::CDog::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionEnter(_spSrc, _spDst);
}

void Editor::CDog::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionStay(_spSrc, _spDst);
}

void Editor::CDog::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionExit(_spSrc, _spDst);
}

void Editor::CDog::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CDog::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CDog::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::DEATH:
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;
	}
}
