#include "pch.h"
#include "Rozzi.h"

// component
#include "CameraComponent.h"
#include "InputComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "RozziStateComponent.h"
#include "SphereComponent.h"
#include "OBBComponent.h"

#include "WildAnimal.h"

HRESULT Client::CRozzi::PreInitialize()
{
	// 로지 데이터 TODO; 로지 데이터 입력하기
	{
		m_eSurvivorType = ESurvivorType::ROZZI;
		m_iCurSurvivorLevel = 0;
		m_arrAttackPower = { 30.0f, 34.9f, 39.8f, 44.7f, 49.6f, 54.5f, 59.4f, 64.3f, 69.2f, 74.1f };
		m_arrDefensePower = { 44.0f, 46.9f, 49.8f, 52.7f, 55.6f, 58.5f, 61.4f, 64.3f, 67.2f, 70.1f };
		m_fCurHP = 880.0f;
		m_arrHPRegenerations = { 1.8f, 1.89f, 1.98f, 2.07f, 2.16f, 2.25f, 2.34f, 2.43f, 2.52f, 2.61f, };
		m_arrMaxHPs = { 880.0f, 972.0f, 1064.0f, 1156.0f, 1248.0f, 1340.0f, 1432.0f, 1524.0f, 1616.0f, 1708.0f };
		m_fCurSP = 350.0f;
		m_arrSPRegenerations = { 2.9f, 2.92f, 2.94f, 2.96f, 2.98f, 3.0f, 3.02f, 3.04f, 3.06f, 3.08f };
		m_arrMaxSPs = { 350.0f, 366.0f, 382.0f, 398.0f, 414.0f, 430.0f, 446.0f, 462.0f, 478.0f, 494.0f };
		m_fSightRange = 8.5f;
		m_fCurMoveSpeed = 4.5f;
	}

	// TODO; 로지 스킬 입력하기
	// 첫 번째 스킬; Stomping Foot
	{
		m_arrSkillInfos[0].m_vecDamages = { 50.0f, 100.0f, 150.0f, 200.0f, 250.0f };
		m_arrSkillInfos[0].m_vecMoveSpeedBoost = { 6.0f, 7.0f, 8.0f, 9.0f, 10.0f };
		m_arrSkillInfos[0].m_vecStamina = { 60.0f, 70.0f, 80.0f, 90.0f, 100.0f };
		m_arrSkillInfos[0].m_vecCoolDown = { 9.0f, 8.0f, 7.0f, 6.0f, 5.0f };
	}

	// 두 번째 스킬; Bluff
	{
		m_arrSkillInfos[1].m_vecDefenseBoost = { 4.0f, 13.0f, 22.0f, 31.0f, 40.0f };
		m_arrSkillInfos[1].m_vecStamina = { 50.0f, 50.0f, 50.0f, 50.0f, 50.0f };
		m_arrSkillInfos[1].m_vecCoolDown = { 18.0f, 17.0f, 16.0f, 15.0f, 14.0f };
	}

	// 세 번째 스킬; First Attack
	{
		m_arrSkillInfos[2].m_vecDamages = { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
		m_arrSkillInfos[2].m_vecAdditionalDamages = { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
		m_arrSkillInfos[2].m_vecStamina = { 70.0f, 75.0f, 80.0f, 85.0f, 90.0f };
		m_arrSkillInfos[2].m_vecCoolDown = { 14.0f, 13.0f, 12.0f, 11.0f, 10.0f };
	}

	// 네 번째 스킬; Haymaker
	{
		m_arrSkillInfos[3].m_vecDamages = { 100.0f, 140.0f, 180.0f };
		m_arrSkillInfos[3].m_vecStamina = { 150.0f, 150.0f, 150.0f };
		m_arrSkillInfos[3].m_vecCoolDown = { 60.0f, 50.0f, 40.0f };
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"LRozziS001");
		m_wpSkeletalMeshComponent.lock()->SetVertexShaderDesc(L"VS_SkeletalMesh");
		m_wpSkeletalMeshComponent.lock()->SetPixelShaderDesc(L"PS_SkeletalMesh");
	}

	{
		m_wpCameraComponent = CreateActorComponent<CCameraComponent>(L"CameraComponent", EComponentType::CAMERA);
		m_wpCameraComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpCameraComponent.lock()->SetOffset({ 0.0f, 1.2f, 0.0f });
		m_wpCameraComponent.lock()->SetRadius(4.0f);
	}

	{
		m_wpNavigationComponent = CreateActorComponent<CNavigationComponent>(L"NavigationComponent", EComponentType::NAVIGATION);
		m_wpNavigationComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpNavigationComponent.lock()->SetNavigation(L"School");
		m_wpNavigationComponent.lock()->SetCurCellIndex(0);
	}

	{
		m_wpSurvivorStateComponent = CreateActorComponent<CRozziStateComponent>(L"StateComponent", EComponentType::STATE);
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
		m_wpSecondSkillSphereComponent = CreateActorComponent<CSphereComponent>(L"SecondSkillSphereComponent", EComponentType::SPHERE);
		m_wpSecondSkillSphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	return CSurvivor::PreInitialize();
}

HRESULT Client::CRozzi::Initialize()
{
	if (FAILED(CSurvivor::Initialize())) { return E_FAIL; }

	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::WAIT,
			L"WAIT",
			{ "Rozzi_Common_Wait" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::RUN,
			L"RUN",
			{ "Rozzi_Common_Run" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::ATTACK_01,
			L"ATTACK_01",
			{ "Rozzi_Pistol_Atk01" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::ATTACK_02,
			L"ATTACK_02",
			{ "Rozzi_Pistol_Atk02" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_01,
			L"SKILL_01",
			{ "Rozzi_Pistol_Skill01" },
			// { "Rozzi_Pistol_Skill01_Move" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_02,
			L"SKILL_02",
			{ "Rozzi_Pistol_Skill02" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_03_BEGIN,
			L"SKILL_03_BEGIN",
			{ "Rozzi_Pistol_Skill03_Jump" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_03,
			L"SKILL_03",
			{ "Rozzi_Pistol_Skill03_Shot" },
			false
		);

		/*
		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_03_END,
			L"SKILL_03_END",
			{ "Hyunwoo_Glove_skill03_end" },
			false
		);
		*/

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_04_BEGIN,
			L"SKILL_04_BEGIN",
			{ "Rozzi_Common_Skill04" },
			false
		);

		/*
		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_04,
			L"SKILL_04",
			{ "Yuki_BareHands_skill04_end" },
			false
		);
		

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_04_END,
			L"SKILL_04_END",
			// { "Yuki_BareHands_skill04_end" },
			{ "Yuki_Common_skill04_end" },
			false
		);
		*/

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::COLLECT_STONE,
			L"COLLECT_STONE",
			{ "Rozzi_Common_Collect_Stone" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::COLLECT_WATER,
			L"COLLECT_WATER",
			{ "Rozzi_Common_Collect_Water" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::COLLECT_WOOD,
			L"COLLECT_WOOD",
			{ "Rozzi_Common_Collect_Wood" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::CRAFT_FOOD,
			L"CRAFT_FOOD",
			{ "Rozzi_Common_Craftfood" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::CRAFT_METAL,
			L"CRAFT_METAL",
			{ "Rozzi_Common_Craftmetal" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::OPERATE,
			L"OPERATE",
			{ "Rozzi_Common_Operate" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::REST_BEGIN,
			L"REST_BEGIN",
			{ "Rozzi_Common_Rest_Start" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::REST,
			L"REST",
			{ "Rozzi_Common_Rest_Loop" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::REST_END,
			L"REST_END",
			{ "Rozzi_Common_Rest_End" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::DEATH,
			L"DEATH",
			{ "Rozzi_Common_Death" },
			false
		);

	}

	{
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.8f, 0.0f });
		m_wpBodySphereComponent.lock()->SetRadius(0.8f);
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::ITEM);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER_SKILL);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER_PROJECTILE);
	}

	{
		m_wpFirstSkillOBBComponent.lock()->SetCenter({ 0.0f, 1.0f, 2.0f });
		m_wpFirstSkillOBBComponent.lock()->SetExtent({ 0.6f, 1.0f, 2.0f });
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);
		m_wpFirstSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_SKILL);
		m_wpFirstSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}

	{
		m_wpSecondSkillSphereComponent.lock()->SetCenter({ 0.0f, 0.0f, 0.0f });
		m_wpSecondSkillSphereComponent.lock()->SetRadius(6.0f);
		m_wpSecondSkillSphereComponent.lock()->SetActive(false);
		m_wpSecondSkillSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_SKILL);
		m_wpSecondSkillSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}

	return S_OK;
}

HRESULT Client::CRozzi::PostInitialize()
{
	if (FAILED(CSurvivor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CRozzi::BeginPlay()
{
	if (FAILED(CSurvivor::BeginPlay())) { return E_FAIL; }

	// 맵의 월드 행렬이 항등 행렬일 때만 유효합니다.
	Vector3 vTempPosition = m_wpNavigationComponent.lock()->GetCentroidPosition(0);
	SetActorLocalPosition(vTempPosition);
	return S_OK;
}

int32 Client::CRozzi::PreTick(float _fDeltaSeconds)
{
	switch (CSurvivor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CRozzi::Tick(float _fDeltaSeconds)
{
	switch (CSurvivor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CRozzi::PostTick(float _fDeltaSeconds)
{
	switch (CSurvivor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CRozzi::EndPlay()
{
	if (FAILED(CSurvivor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CRozzi::Render()
{
	CSurvivor::Render();
}

void Client::CRozzi::Release()
{
	CSurvivor::Release();
}

void Client::CRozzi::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionEnter(_spSrc, _spDst);
}

void Client::CRozzi::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionStay(_spSrc, _spDst);
}

void Client::CRozzi::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionExit(_spSrc, _spDst);
}

void Client::CRozzi::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorState>(_iAnimState))
	{
	case ESurvivorState::SKILL_01:	m_wpFirstSkillOBBComponent.lock()->SetActive(true);		break;
	case ESurvivorState::SKILL_02:	m_wpSecondSkillSphereComponent.lock()->SetActive(true);	break;
	default:																				break;
	}
}

void Client::CRozzi::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorState>(_iAnimState))
	{
	case ESurvivorState::SKILL_03_BEGIN:
	case ESurvivorState::SKILL_03:
	{
		Vector3 vForward = GetActorWorldForwardVector().value();
		vForward.Normalize();

		Vector3 vLocalPosition = GetActorLocalPosition().value();
		vLocalPosition += vForward * m_fDeltaSeconds * m_fCurMoveSpeed * m_fThirdSkillSpeedOffset;

		Vector3 vOutWorldPosition = Vector3::Zero;
		if (!m_wpNavigationComponent.lock()->IsValidCell(vLocalPosition, vOutWorldPosition)) { break; }

		SetActorLocalPosition(vOutWorldPosition);
	}
	break;

	default: break;
	}
}

void Client::CRozzi::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorState>(_iAnimState))
	{
	case ESurvivorState::SKILL_01:	m_wpFirstSkillOBBComponent.lock()->SetActive(false);	break;
	case ESurvivorState::SKILL_02:	m_wpSecondSkillSphereComponent.lock()->SetActive(false);break;
	default:																				break;
	}
}

void Client::CRozzi::MoveForward(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveForward(_iValue);
}

void Client::CRozzi::MoveBackward(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveBackward(_iValue);
}

void Client::CRozzi::MoveRight(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveRight(_iValue);
}

void Client::CRozzi::MoveLeft(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveLeft(_iValue);
}
