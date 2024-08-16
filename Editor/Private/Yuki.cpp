#include "pch.h"
#include "Yuki.h"

// component
#include "CameraComponent.h"
#include "InputComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "YukiStateComponent.h"
#include "SphereComponent.h"
#include "OBBComponent.h"

#include "WildAnimal.h"

HRESULT Editor::CYuki::PreInitialize()
{
	// 유키 데이터 TODO; 유키 데이터 입력하기
	{
		m_eSurvivorType = ESurvivorType::YUKI;
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

	// TODO; 유키 스킬 입력하기
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

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"YukiSP01");
		m_wpSkeletalMeshComponent.lock()->SetVertexShaderDesc(L"VS_SkeletalMesh");
		m_wpSkeletalMeshComponent.lock()->SetPixelShaderDesc(L"PS_SkeletalMesh");
	}

	{
		m_wpCameraComponent = CreateActorComponent<CCameraComponent>(L"CameraComponent", EComponentType::CAMERA);
		m_wpCameraComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpCameraComponent.lock()->SetOffset({ 0.0f, 1.2f, 0.0f });
		m_wpCameraComponent.lock()->SetRadius(6.0f);
	}

	{
		m_wpNavigationComponent = CreateActorComponent<CNavigationComponent>(L"NavigationComponent", EComponentType::NAVIGATION);
		m_wpNavigationComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpNavigationComponent.lock()->SetNavigation(L"School");
		m_wpNavigationComponent.lock()->SetCurCellIndex(0);
	}
	
	{
		m_wpSurvivorStateComponent = CreateActorComponent<CYukiStateComponent>(L"StateComponent", EComponentType::STATE);
	}
	
	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	return CSurvivor::PreInitialize();
}

HRESULT Editor::CYuki::Initialize()
{
	if (FAILED(CSurvivor::Initialize())) { return E_FAIL; }

	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::WAIT,
			L"WAIT",
			{ "Yuki_2Hand_wait" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::RUN,
			L"RUN",
			{ "Yuki_2Hand_run" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::ATTACK_01,
			L"ATTACK_01",
			{ "Yuki_2Hand_atk01" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::ATTACK_02,
			L"ATTACK_02",
			{ "Yuki_2Hand_atk02" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_01,
			L"SKILL_01",
			{ "Yuki_2Hand_skill01" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_02,
			L"SKILL_02",
			{ "Yuki_2Hand_skill02_upper_wait" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_03_BEGIN,
			L"SKILL_03_BEGIN",
			{ "Yuki_2Hand_skill03_move" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_03,
			L"SKILL_03",
			{ "Yuki_2Hand_skill03_attack" },
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
			// { "Yuki_BareHands_skill04" },
			{ "Yuki_Common_skill04" },
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
		*/

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::SKILL_04_END,
			L"SKILL_04_END",
			// { "Yuki_BareHands_skill04_end" },
			{ "Yuki_Common_skill04_end" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::COLLECT_STONE,
			L"COLLECT_STONE",
			{ "Yuki_Common_collect_Stone" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::COLLECT_WATER,
			L"COLLECT_WATER",
			{ "Yuki_Common_collect_Water" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::COLLECT_WOOD,
			L"COLLECT_WOOD",
			{ "Yuki_Common_collect_Wood" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::CRAFT_FOOD,
			L"CRAFT_FOOD",
			{ "Yuki_Common_craftfood" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::CRAFT_METAL,
			L"CRAFT_METAL",
			{ "Yuki_Common_craftmetal" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::OPERATE,
			L"OPERATE",
			{ "Yuki_Common_operate" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::REST_BEGIN,
			L"REST_BEGIN",
			{ "Yuki_Common_rest_start" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::REST,
			L"REST",
			{ "Yuki_Common_rest_loop" },
			true
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::REST_END,
			L"REST_END",
			{ "Yuki_Common_rest_end" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ESurvivorAnimState::DEATH,
			L"DEATH",
			{ "Yuki_Common_death" },
			false
		);

	}
	
	{
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.8f, 0.0f });
		m_wpBodySphereComponent.lock()->SetRadius(0.8f);
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::ITEM);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::STRUCTURE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}
	
	return S_OK;
}

HRESULT Editor::CYuki::PostInitialize()
{
	if (FAILED(CSurvivor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CYuki::BeginPlay()
{
	if (FAILED(CSurvivor::BeginPlay())) { return E_FAIL; }

	// 맵의 월드 행렬이 항등 행렬일 때만 유효합니다.
	Vector3 vTempPosition = m_wpNavigationComponent.lock()->GetCentroidPosition(0);
	SetActorLocalPosition(vTempPosition);
	return S_OK;
}

int32 Editor::CYuki::PreTick(float _fDeltaSeconds)
{
	switch (CSurvivor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CYuki::Tick(float _fDeltaSeconds)
{
	switch (CSurvivor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CYuki::PostTick(float _fDeltaSeconds)
{
	switch (CSurvivor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CYuki::EndPlay()
{
	if (FAILED(CSurvivor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CYuki::Render()
{
	CSurvivor::Render();
}

void Editor::CYuki::Release()
{
	CSurvivor::Release();
}

void Editor::CYuki::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionEnter(_spSrc, _spDst);
}

void Editor::CYuki::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionStay(_spSrc, _spDst);
}

void Editor::CYuki::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionExit(_spSrc, _spDst);
}

void Editor::CYuki::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CYuki::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CYuki::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
}

void Editor::CYuki::MoveForward(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveForward(_iValue);
}

void Editor::CYuki::MoveBackward(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveBackward(_iValue);
}

void Editor::CYuki::MoveRight(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveRight(_iValue);
}

void Editor::CYuki::MoveLeft(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveLeft(_iValue);
}

