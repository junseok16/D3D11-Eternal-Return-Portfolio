#include "pch.h"
#include "Wolf.h"

#include "WolfStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "SphereComponent.h"

HRESULT Editor::CWolf::PreInitialize()
{
	{
		m_eWildAnimalHabitType = EWildAnimalHabitType::NOCTURNAL;
		m_fAttackRange = 2.5f;
		m_fCurMoveSpeed = 4.0f;
		m_fCurHP = 150.0f;
		m_fMaxHP = 150.0f;
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Wolf");
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
		m_wpWildAnimalStateComponent = CreateActorComponent<CWolfStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	return CWildAnimal::PreInitialize();
}

HRESULT Editor::CWolf::Initialize()
{
	if (FAILED(CWildAnimal::Initialize())) { return E_FAIL; }

	/*
	* TODO; 추가할 애니메이션들
	* Wolf_01_appear
	* Wolf_01_appearwait
	* Wolf_01_dance
	*/

	{
		// 낮일 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SLEEP_BEGIN,	L"SLEEP_BEGIN",	{ "Wolf_01_sleep_start" },		false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SLEEP,			L"SLEEP",		{ "Wolf_01_sleep" },			true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAKE,			L"WAKE",		{ "Wolf_01_wake" },				false);

		// 밤일 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::WAIT,			L"WAIT",		{ "Wolf_01_wait" },				true);

		// 경계 안에 들어갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_BEGIN,	L"BEWARE_BEGIN",{ "wolf_01_beware_start" },		false);
		
		// 경계 안에 있을 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE,		L"BEWARE",		{ "wolf_01_beware_loop" },		true);

		// 경계 밖으로 나갈 때
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::BEWARE_END,	L"BEWARE_END",	{ "wolf_01_beware_end" },		false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::RUN,			L"RUN",			{ "Wolf_01_run" },				true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_01,		L"ATTACK_01",	{ "Wolf_01_atk01" },			false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::ATTACK_02,		L"ATTACK_02",	{ "Wolf_01_atk02" },			false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::SKILL,			L"SKILL",		{ "Wolf_01_skill01" },			false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::END_BATTLE,	L"END_BATTLE",	{ "Wolf_01_endbattle" },		false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EWildAnimalAnimState::DEATH,			L"DEATH",		{ "Wolf_01_death" },			false);
	}
	
	{
		m_wpBodySphereComponent.lock()->SetRadius(1.2f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.6f, 0.0f });
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	return S_OK;
}

HRESULT Editor::CWolf::PostInitialize()
{
	if (FAILED(CWildAnimal::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CWolf::BeginPlay()
{
	if (FAILED(CWildAnimal::BeginPlay())) { return E_FAIL; }

	SetActorLocalPosition(m_vSpawnPosition);
	return S_OK;
}

int32 Editor::CWolf::PreTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CWolf::Tick(float _fDeltaSeconds)
{
	switch (CWildAnimal::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CWolf::PostTick(float _fDeltaSeconds)
{
	switch (CWildAnimal::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CWolf::EndPlay()
{
	if (FAILED(CWildAnimal::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CWolf::Render()
{
	CWildAnimal::Render();
}

void Editor::CWolf::Release()
{
	CWildAnimal::Release();
}

void Editor::CWolf::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionEnter(_spSrc, _spDst);
}

void Editor::CWolf::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionStay(_spSrc, _spDst);
}

void Editor::CWolf::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CWildAnimal::OnCollisionExit(_spSrc, _spDst);
}

void Editor::CWolf::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CWolf::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CWolf::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EWildAnimalAnimState>(_iAnimState))
	{
	case EWildAnimalAnimState::DEATH:
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;
	}
}
