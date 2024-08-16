#include "pch.h"
#include "Wickline.h"

#include "WicklineStateComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "OBBComponent.h"
#include "SphereComponent.h"

HRESULT Editor::CWickline::PreInitialize()
{
	{
		m_fAttackRange = 4.0f;
		m_fCurMoveSpeed = 5.5f;
		m_fCurHP = 500.0f;
		m_fMaxHP = 500.0f;
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

		m_wpNavigationComponent.lock()->SetNavigation(L"School");

		// TODO; 임시로 셀 번호를 지정합니다.
		m_wpNavigationComponent.lock()->SetCurCellIndex(10 /*m_iSpawnCellIndex*/);
	}

	{
		m_wpBossStateComponent = CreateActorComponent<CWicklineStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpAttackOBBComponent = CreateActorComponent<COBBComponent>(L"OBBComponent", EComponentType::OBB);
		m_wpAttackOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}
	return CBoss::PreInitialize();
}

HRESULT Editor::CWickline::Initialize()
{
	if (FAILED(CBoss::Initialize())) { return E_FAIL; }
	
	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::WAIT,			L"WAIT",		{ "Wickline_01_wait" },			true);
		
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::RUN,				L"RUN",			{ "Wickline_01_run" },			true);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::ATTACK_01,		L"ATTACK_01",	{ "Wickline_01_atk01" },		false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::ATTACK_02,		L"ATTACK_02",	{ "Wickline_01_atk02" },		false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_01_BEGIN,	L"SKILL_BEGIN",	{ "Wickline_01_skill1_loop" },	false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_01,		L"SKILL_01",	{ "Wickline_01_skill1_end" },	false);
		
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_02,		L"SKILL_02",	{ "Wickline_01_skill2" },		false);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::SKILL_03,		L"SKILL_03",	{ "Wickline_01_wait" },			true);

		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::END_BATTLE,		L"END_BATTLE",	{ "Wickline_01_endbattle" },	false);
		m_wpSkeletalMeshComponent.lock()->AddAnimState((uint32)EBossAnimState::DEATH,			L"DEATH",		{ "Wickline_01_death" },		false);

		m_wpSkeletalMeshComponent.lock()->SetComponentLocalScale({ 1.4f, 1.4f, 1.4f });
	}
	
	{
		m_wpBodySphereComponent.lock()->SetRadius(1.4f);
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.7f, 0.0f });
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_PROJECTILE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER_SKILL);
	}

	{
		m_wpAttackOBBComponent.lock()->SetCenter({ 0.0f, 0.5f, 1.0f });
		m_wpAttackOBBComponent.lock()->SetExtent({ 1.0f, 1.0f, 2.0f });
		m_wpAttackOBBComponent.lock()->SetActive(false);
		m_wpAttackOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::MONSTER_SKILL);
		m_wpAttackOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
	}

	return S_OK;
}

HRESULT Editor::CWickline::PostInitialize()
{
	if (FAILED(CBoss::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CWickline::BeginPlay()
{
	if (FAILED(CBoss::BeginPlay())) { return E_FAIL; }

	// TODO; 임시로 스폰 위치를 설정합니다.
	SetActorLocalPosition(m_wpNavigationComponent.lock()->GetCentroidPosition(10));
	return S_OK;
}

int32 Editor::CWickline::PreTick(float _fDeltaSeconds)
{
	switch (CBoss::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CWickline::Tick(float _fDeltaSeconds)
{
	switch (CBoss::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CWickline::PostTick(float _fDeltaSeconds)
{
	switch (CBoss::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CWickline::EndPlay()
{
	if (FAILED(CBoss::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CWickline::Render()
{
	CBoss::Render();
}

void Editor::CWickline::Release()
{
	CBoss::Release();
}

void Editor::CWickline::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionEnter(_spSrc, _spDst);
}

void Editor::CWickline::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionStay(_spSrc, _spDst);
}

void Editor::CWickline::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CBoss::OnCollisionExit(_spSrc, _spDst);
}

void Editor::CWickline::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	case EBossAnimState::ATTACK_02:
		m_wpAttackOBBComponent.lock()->SetActive(true);
		break;

	case EBossAnimState::SKILL_01:
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(3.0f);
		break;

	case EBossAnimState::SKILL_02:
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(0.8f);
		break;
	}
}

void Editor::CWickline::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CWickline::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<EBossAnimState>(_iAnimState))
	{
	case EBossAnimState::ATTACK_01:
	case EBossAnimState::ATTACK_02:
		m_wpAttackOBBComponent.lock()->SetActive(false);
		break;
		
	case EBossAnimState::SKILL_01:
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		break;

	case EBossAnimState::SKILL_02:
		if (++m_iSumSecondSkillFire >= m_iMaxSecondSkillFire)
		{
			m_iSumSecondSkillFire = 0;
			m_wpBossStateComponent.lock()->SetBossState(EBossState::CHASE);
			m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		}
		break;

	case EBossAnimState::DEATH:
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		m_wpAttackOBBComponent.lock()->SetActive(false);
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;
	}
}
