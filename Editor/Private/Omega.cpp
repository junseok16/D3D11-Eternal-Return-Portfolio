#include "pch.h"
#include "Omega.h"

#include "OmegaStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "OBBComponent.h"
#include "SphereComponent.h"

#include "Projectile.h"

#include "World.h"
#include "Level.h"

HRESULT Editor::COmega::PreInitialize()
{
	{
		m_fAttackRange = 2.0f;
		m_fCurMoveSpeed = 3.5f;
		m_fCurHP = 100.0f;
		m_fMaxHP = 100.0f;
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

		m_wpNavigationComponent.lock()->SetNavigation(L"School");

		// TODO; 임시로 셀 번호를 지정합니다.
		m_wpNavigationComponent.lock()->SetCurCellIndex(10 /*m_iSpawnCellIndex*/);
	}

	{
		m_wpBossStateComponent = CreateActorComponent<COmegaStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpAttackOBBComponent = CreateActorComponent<COBBComponent>(L"AttackOBBComponent", EComponentType::OBB);
		m_wpAttackOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpFirstSkillOBBComponent = CreateActorComponent<COBBComponent>(L"FirstSkillOBBComponent", EComponentType::OBB);
		m_wpFirstSkillOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}
	return CBoss::PreInitialize();
}

HRESULT Editor::COmega::Initialize()
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
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	{
		m_wpAttackOBBComponent.lock()->SetCenter({ 0.0f, 0.5f, 0.5f });
		m_wpAttackOBBComponent.lock()->SetExtent({ 1.0f, 1.0f, 1.0f });
		m_wpAttackOBBComponent.lock()->SetActive(false);
		m_wpAttackOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_SKILL);
		m_wpAttackOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
	}

	{
		m_wpFirstSkillOBBComponent.lock()->SetCenter({ 0.0f, 0.5f, 0.5f });
		m_wpFirstSkillOBBComponent.lock()->SetExtent({ 2.0f, 1.0f, 1.0f });
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);
		m_wpFirstSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_SKILL);
		m_wpFirstSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
	}
	return S_OK;
}

HRESULT Editor::COmega::PostInitialize()
{
	if (FAILED(CBoss::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::COmega::BeginPlay()
{
	if (FAILED(CBoss::BeginPlay())) { return E_FAIL; }

	// TODO; 임시로 스폰 위치를 설정합니다.
	SetActorLocalPosition(m_wpNavigationComponent.lock()->GetCentroidPosition(10));
	return S_OK;
}

int32 Editor::COmega::PreTick(float _fDeltaSeconds)
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

int32 Editor::COmega::Tick(float _fDeltaSeconds)
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

int32 Editor::COmega::PostTick(float _fDeltaSeconds)
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

HRESULT Editor::COmega::EndPlay()
{
	if (FAILED(CBoss::EndPlay())) { return E_FAIL; }

	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->EndPlay();
	}

	return S_OK;
}

void Editor::COmega::Render()
{
	CBoss::Render();

	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->Render();
	}
}

void Editor::COmega::Release()
{
	for (const auto& spProjectile : m_vecOmegaProjectiles)
	{
		spProjectile->Release();
	}
	CBoss::Release();
}

void Editor::COmega::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionEnter(_spSrc, _spDst);
}

void Editor::COmega::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionStay(_spSrc, _spDst);
}

void Editor::COmega::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionExit(_spSrc, _spDst);
}

void Editor::COmega::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	case EBossAnimState::ATTACK_02:
		m_wpAttackOBBComponent.lock()->SetActive(true);
		break;

	case EBossAnimState::SKILL_01:
		m_wpFirstSkillOBBComponent.lock()->SetActive(true);
		break;
	}
}

void Editor::COmega::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::COmega::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	case EBossAnimState::ATTACK_02:
		m_wpAttackOBBComponent.lock()->SetActive(false);
		break;

	case EBossAnimState::SKILL_01:
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);
		break;

	case EBossAnimState::DEATH:
		m_wpAttackOBBComponent.lock()->SetActive(false);
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;
	}
}
