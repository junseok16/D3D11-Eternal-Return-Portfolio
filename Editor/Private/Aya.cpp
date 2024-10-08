#include "pch.h"
#include "Aya.h"

// component
#include "CameraComponent.h"
#include "InputComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "AyaStateComponent.h"
#include "SphereComponent.h"
#include "OBBComponent.h"
#include "LightComponent.h"

// enemy
#include "WildAnimal.h"

// socket
#include "Socket.h"
#include "Weapon.h"
#include "CraftTool.h"

// projectile
#include "Projectile.h"

HRESULT Editor::CAya::PreInitialize()
{
	// 아야 데이터 TODO; 아야 데이터 입력하기
	{
		m_eSurvivorType		= ESurvivorType::AYA;
		m_iCurSurvivorLevel	= 0;
		m_arrAttackPower	= { 30.0f, 34.9f, 39.8f, 44.7f, 49.6f, 54.5f, 59.4f, 64.3f, 69.2f, 74.1f };
		m_arrDefensePower	= { 44.0f, 46.9f, 49.8f, 52.7f, 55.6f, 58.5f, 61.4f, 64.3f, 67.2f, 70.1f };
		m_fCurHP			= 880.0f;
		m_arrHPRegenerations= { 1.8f, 1.89f, 1.98f, 2.07f, 2.16f, 2.25f, 2.34f, 2.43f, 2.52f, 2.61f, };
		m_arrMaxHPs			= { 880.0f, 972.0f, 1064.0f, 1156.0f, 1248.0f, 1340.0f, 1432.0f, 1524.0f, 1616.0f, 1708.0f };
		m_fCurSP			= 350.0f;
		m_arrSPRegenerations= { 2.9f, 2.92f, 2.94f, 2.96f, 2.98f, 3.0f, 3.02f, 3.04f, 3.06f, 3.08f };
		m_arrMaxSPs			= { 350.0f, 366.0f, 382.0f, 398.0f, 414.0f, 430.0f, 446.0f, 462.0f, 478.0f, 494.0f };
		m_fSightRange		= 8.5f;
		m_fCurMoveSpeed		= 6.0f;

		m_arrMaxExps		= { 13.0f, 26.0f, 39.0f, 52.0f, 65.0f, 78.0f, 91.0f, 104.0f, 117.0f, 130.0f };
		m_arrMaxSkillLevels = { 5, 5, 5, 3, 3 };
	
		m_vecMaxSkillCoolDown.resize(4);
		m_vecMaxSkillCoolDown[0] = {  7.0f,  6.0f,  5.0f, 4.0f, 3.0f };
		m_vecMaxSkillCoolDown[1] = {  8.0f,  7.0f,  6.0f, 5.0f, 4.0f };
		m_vecMaxSkillCoolDown[2] = { 13.0f, 11.0f,  9.0f, 7.0f, 5.0f };
		m_vecMaxSkillCoolDown[3] = { 30.0f, 20.0f, 10.0f };

		m_vecCurSkillCoolDown.resize(4);
		m_vecCurSkillCoolDown = { 0.0f, 0.0f, 0.0f, 0.0f };
	}
	
	// 첫 번째 스킬; Stomping Foot
	{
		m_arrSkillInfos[0].m_vecDamages				= { 50.0f, 100.0f, 150.0f, 200.0f, 250.0f };
		m_arrSkillInfos[0].m_vecMoveSpeedBoost		= { 6.0f, 7.0f, 8.0f, 9.0f, 10.0f };
		m_arrSkillInfos[0].m_vecStamina				= { 60.0f, 70.0f, 80.0f, 90.0f, 100.0f };
		m_arrSkillInfos[0].m_vecCoolDown			= { 9.0f, 8.0f, 7.0f, 6.0f, 5.0f };
	}
	
	// 두 번째 스킬; Bluff
	{
		m_arrSkillInfos[1].m_vecDefenseBoost		= { 4.0f, 13.0f, 22.0f, 31.0f, 40.0f };
		m_arrSkillInfos[1].m_vecStamina				= { 50.0f, 50.0f, 50.0f, 50.0f, 50.0f };
		m_arrSkillInfos[1].m_vecCoolDown			= { 18.0f, 17.0f, 16.0f, 15.0f, 14.0f };
	}
	
	// 세 번째 스킬; First Attack
	{
		m_arrSkillInfos[2].m_vecDamages				= { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
		m_arrSkillInfos[2].m_vecAdditionalDamages	= { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
		m_arrSkillInfos[2].m_vecStamina				= { 70.0f, 75.0f, 80.0f, 85.0f, 90.0f };
		m_arrSkillInfos[2].m_vecCoolDown			= { 14.0f, 13.0f, 12.0f, 11.0f, 10.0f };
	}
	
	// 네 번째 스킬; Haymaker
	{
		m_arrSkillInfos[3].m_vecDamages				= { 100.0f, 140.0f, 180.0f };
		m_arrSkillInfos[3].m_vecStamina				= { 150.0f, 150.0f, 150.0f };
		m_arrSkillInfos[3].m_vecCoolDown			= { 60.0f, 50.0f, 40.0f };
	}

	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Aya");
		m_wpSkeletalMeshComponent.lock()->SetVertexShaderDesc(L"VS_SkeletalMesh");
		m_wpSkeletalMeshComponent.lock()->SetPixelShaderDesc(L"PS_SkeletalMesh");
	}

	{
		m_wpCameraComponent = CreateActorComponent<CCameraComponent>(L"CameraComponent", EComponentType::CAMERA);
		m_wpCameraComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpCameraComponent.lock()->SetOffset({ 0.0f, 1.2f, 0.0f });
		m_wpCameraComponent.lock()->SetRadius(3.0f);
	}

	{
		m_wpNavigationComponent = CreateActorComponent<CNavigationComponent>(L"NavigationComponent", EComponentType::NAVIGATION);
		m_wpNavigationComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpNavigationComponent.lock()->SetNavigation(L"LumiaNavigation");
		m_wpNavigationComponent.lock()->SetCurCellIndex(3);
	}

	{
		m_wpSurvivorStateComponent = CreateActorComponent<CAyaStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	{
		m_wpLightComponent = CreateActorComponent<CLightComponent>(L"AyaLightComponent", EComponentType::POINT_LIGHT);
		m_wpLightComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"BodySphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpFourthSkillSphereComponent = CreateActorComponent<CSphereComponent>(L"FourthSkillSphereComponent", EComponentType::SPHERE);
		m_wpFourthSkillSphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	m_arrSockets[0] = CWeapon::Create(dynamic_pointer_cast<CActor>(shared_from_this()), "Weapon_R", EWeaponType::PISTOL);
	m_arrSockets[0]->PreInitialize();

	return CSurvivor::PreInitialize();
}

HRESULT Editor::CAya::Initialize()
{
	if (FAILED(CSurvivor::Initialize())) { return E_FAIL; }

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::WAIT,
		L"WAIT",
		{ "Aya_Pistol_wait" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::ARRIVE,
		L"ARRIVE",
		{ "Aya_Common_arrive" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::RUN,
		L"RUN",
		{ "Aya_Pistol_run" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::ATTACK_01,
		L"ATTACK_01",
		{ "Aya_Pistol_atk01" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::ATTACK_02,
		L"ATTACK_02",
		{ "Aya_Pistol_atk02" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState(
		(uint32)ESurvivorAnimState::SKILL_01,
		L"SKILL_01",
		{ "Aya_Pistol_skill01" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_02_BEGIN,
		L"SKILL_02",
		{ "Aya_Pistol_skill02_shot" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_03_BEGIN,
		L"SKILL_03_BEGIN",
		{ "Aya_Pistol_skill03" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_04_BEGIN,
		L"SKILL_04_BEGIN",
		{ "Aya_Pistol_skill04" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::COLLECT_STONE,
		L"COLLECT_STONE",
		{ "Aya_Common_collect_Stone" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::COLLECT_WATER,
		L"COLLECT_WATER",
		{ "Aya_Common_collect_Water" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::COLLECT_WOOD,
		L"COLLECT_WOOD",
		{ "Aya_Common_collect_Wood" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::CRAFT_FOOD,
		L"CRAFT_FOOD",
		{ "Aya_Common_craftfood" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::CRAFT_METAL,
		L"CRAFT_METAL",
		{ "Aya_Common_craftmetal" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::OPERATE,
		L"OPERATE",
		{ "Aya_Common_operate" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::REST_BEGIN,
		L"REST_BEGIN",
		{ "Aya_Common_rest_start" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::REST,
		L"REST",
		{ "Aya_Common_rest_loop" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::REST_END,
		L"REST_END",
		{ "Aya_Common_rest_end" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::DEATH,
		L"DEATH",
		{ "Aya_Common_death" },
		false
	);

	{
		m_wpBodySphereComponent.lock()->SetCenter({ 0.0f, 0.8f, 0.0f });
		m_wpBodySphereComponent.lock()->SetRadius(0.8f);
		m_wpBodySphereComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::ITEM);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::STRUCTURE);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::BOUNDARY);
		m_wpBodySphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER_SKILL);
	}

	{
		m_wpFourthSkillSphereComponent.lock()->SetCenter({ 0.0f, 0.0f, 0.0f });
		m_wpFourthSkillSphereComponent.lock()->SetRadius(6.0f);
		m_wpFourthSkillSphereComponent.lock()->SetActive(false);
		m_wpFourthSkillSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_SKILL);
		m_wpFourthSkillSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}

	{
		TLightDesc tLightDesc =
		{
			ELightType::POINT,
			Vector3::One,
			5.0f,
			Vector3::One,
			0.0f,
			Vector3::Zero,
			10.0f,
			Vector3::Zero,
			1.0f,
			Vector3::Down,
			Vector3::One
		};

		m_wpLightComponent.lock()->SetLightDesc(tLightDesc);
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->Initialize();
	}
	return S_OK;
}

HRESULT Editor::CAya::PostInitialize()
{
	if (FAILED(CSurvivor::PostInitialize())) { return E_FAIL; }

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->PostInitialize();
	}
	return S_OK;
}

HRESULT Editor::CAya::BeginPlay()
{
	if (FAILED(CSurvivor::BeginPlay())) { return E_FAIL; }

	// 맵의 월드 행렬이 항등 행렬일 때만 유효합니다.
	Vector3 vTempPosition = m_wpNavigationComponent.lock()->GetCentroidPosition(3);
	SetActorLocalPosition(vTempPosition);

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->BeginPlay();
	}
	return S_OK;
}

int32 Editor::CAya::PreTick(float _fDeltaSeconds)
{
	if (!m_bPosessed) { return 0; }

	switch (CSurvivor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecAyaProjectiles)
	{
		spProjectile->PreTick(_fDeltaSeconds);
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->PreTick(_fDeltaSeconds);
	}
	return 0;
}

int32 Editor::CAya::Tick(float _fDeltaSeconds)
{
	if (!m_bPosessed) { return 0; }

	switch (CSurvivor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecAyaProjectiles)
	{
		spProjectile->Tick(_fDeltaSeconds);
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->Tick(_fDeltaSeconds);
	}
	return 0;
}

int32 Editor::CAya::PostTick(float _fDeltaSeconds)
{
	if (!m_bPosessed) { return 0; }

	switch (CSurvivor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spProjectile : m_vecAyaProjectiles)
	{
		spProjectile->PostTick(_fDeltaSeconds);
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->PostTick(_fDeltaSeconds);
	}
	return 0;
}

HRESULT Editor::CAya::EndPlay()
{
	if (FAILED(CSurvivor::EndPlay())) { return E_FAIL; }

	for (const auto& spProjectile : m_vecAyaProjectiles)
	{
		spProjectile->EndPlay();
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->EndPlay();
	}
	return S_OK;
}

void Editor::CAya::Render()
{
	if (!m_bPosessed) { return; }

	CSurvivor::Render();

	for (const auto& spProjectile : m_vecAyaProjectiles)
	{
		spProjectile->Render();
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->Render();
	}
}

void Editor::CAya::Release()
{
	for (auto& spProjectile : m_vecAyaProjectiles)
	{
		spProjectile->Release();
		spProjectile = nullptr;
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->Release();
	}
	CSurvivor::Release();
}

void Editor::CAya::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionEnter(_spSrc, _spDst);
}

void Editor::CAya::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionStay(_spSrc, _spDst);
}

void Editor::CAya::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionExit(_spSrc, _spDst);
}

void Editor::CAya::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::ATTACK_01:
	case ESurvivorAnimState::ATTACK_02:
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(2.0f);
		break;

	case ESurvivorAnimState::SKILL_02_BEGIN:
		m_bSecondSkillApplying = true;
		break;

	case ESurvivorAnimState::SKILL_04_BEGIN:
		m_wpFourthSkillSphereComponent.lock()->SetActive(true);
		break;
		
	default:
		break;
	}
}

void Editor::CAya::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::ATTACK_01:
	case ESurvivorAnimState::ATTACK_02:
	{
		if (0.2f <= _fRatio && m_bAttackApply == false)
		{
			m_bAttackApply = true;

			Vector3 vForward = GetActorWorldForwardVector().value();
			Vector3 vLocalPosition = GetActorLocalPosition().value() + Vector3(0.0f, 1.5f, 0.0f) + vForward;

			bool bFoundDead = false;

			for (const auto& spProjectile : m_vecAyaProjectiles)
			{
				if (spProjectile->IsDead())
				{
					spProjectile->Revive
					(
						vLocalPosition,
						vForward,
						3.0f,
						0.1f,
						m_arrAttackPower[m_iCurSurvivorLevel],
						nullptr,
						static_pointer_cast<CActor>(shared_from_this()),
						EProjectileType::AYA,
						EProjectileState::MOVE
					);
					bFoundDead = true;
					break;
				}
			}

			if (bFoundDead == false)
			{
				shared_ptr<CProjectile> spProjectile = CProjectile::Create
				(
					vLocalPosition,
					vForward,
					3.0f,
					0.1f,
					m_arrAttackPower[m_iCurSurvivorLevel],
					nullptr,
					static_pointer_cast<CActor>(shared_from_this()),
					EProjectileType::AYA,
					EProjectileState::MOVE
				);
				m_vecAyaProjectiles.push_back(spProjectile);
			}
		}
	}
	break;

	case ESurvivorAnimState::SKILL_01:
	{
		if (0.3f <= _fRatio && m_bFirstSkillFirstFire == false)
		{
			m_bFirstSkillFirstFire = true;

			Vector3 vForward = GetActorWorldForwardVector().value();
			Vector3 vLocalPosition = GetActorLocalPosition().value() + Vector3(0.0f, 1.5f, 0.0f) + vForward;

			bool bFoundDead = false;

			for (const auto& spProjectile : m_vecAyaProjectiles)
			{
				if (spProjectile->IsDead())
				{
					spProjectile->Revive
					(
						vLocalPosition,
						vForward,
						3.0f,
						0.1f,
						m_arrAttackPower[m_iCurSurvivorLevel],
						nullptr,
						static_pointer_cast<CActor>(shared_from_this()),
						EProjectileType::AYA,
						EProjectileState::MOVE
					);
					bFoundDead = true;
					break;
				}
			}

			if (bFoundDead == false)
			{
				shared_ptr<CProjectile> spProjectile = CProjectile::Create
				(
					vLocalPosition,
					vForward,
					3.0f,
					0.1f,
					m_arrAttackPower[m_iCurSurvivorLevel],
					nullptr,
					static_pointer_cast<CActor>(shared_from_this()),
					EProjectileType::AYA,
					EProjectileState::MOVE
				);
				m_vecAyaProjectiles.push_back(spProjectile);
			}
		}

		if (0.6f <= _fRatio && m_bFirstSkillSecondFire == false)
		{
			m_bFirstSkillSecondFire = true;

			Vector3 vForward = GetActorWorldForwardVector().value();
			Vector3 vLocalPosition = GetActorLocalPosition().value() + Vector3(0.0f, 1.5f, 0.0f) + vForward;

			bool bFoundDead = false;

			for (const auto& spProjectile : m_vecAyaProjectiles)
			{
				if (spProjectile->IsDead())
				{
					spProjectile->Revive
					(
						vLocalPosition,
						vForward,
						3.0f,
						0.1f,
						m_arrAttackPower[m_iCurSurvivorLevel],
						nullptr,
						static_pointer_cast<CActor>(shared_from_this()),
						EProjectileType::AYA,
						EProjectileState::MOVE
					);
					bFoundDead = true;
					break;
				}
			}

			if (bFoundDead == false)
			{
				shared_ptr<CProjectile> spProjectile = CProjectile::Create
				(
					vLocalPosition,
					vForward,
					3.0f,
					0.1f,
					m_arrAttackPower[m_iCurSurvivorLevel],
					nullptr,
					static_pointer_cast<CActor>(shared_from_this()),
					EProjectileType::AYA,
					EProjectileState::MOVE
				);
				m_vecAyaProjectiles.push_back(spProjectile);
			}
		}
	}
	break;

	case ESurvivorAnimState::SKILL_02_BEGIN:
		break;

	case ESurvivorAnimState::SKILL_03_BEGIN:
	{
		if (_fRatio <= 0.8f)
		{
			Vector3 vForward = GetActorWorldForwardVector().value();
			vForward.Normalize();

			Vector3 vLocalPosition = GetActorLocalPosition().value();
			vLocalPosition += vForward * m_fDeltaSeconds * m_fCurMoveSpeed * m_fThirdSkillSpeedOffset;

			Vector3 vOutWorldPosition = Vector3::Zero;
			if (!m_wpNavigationComponent.lock()->IsValidCell(vLocalPosition, vOutWorldPosition)) { break; }

			SetActorLocalPosition(vOutWorldPosition);
		}
	}
	break;

	default:
		break;
	}
}

void Editor::CAya::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::ATTACK_01:
	case ESurvivorAnimState::ATTACK_02:
	{
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		m_bAttackApply = false;
	}
	break;

	case ESurvivorAnimState::SKILL_01:
		m_bFirstSkillFirstFire = false;
		m_bFirstSkillSecondFire = false;
		break;

	case ESurvivorAnimState::SKILL_02_BEGIN:
	{
		if (++m_iSumSecondSkillFire >= m_iMaxSecondSkillFire)
		{
			m_bSecondSkillApplying = false;
			m_iSumSecondSkillFire = 0;
			m_wpSurvivorStateComponent.lock()->SetServivorState(ESurvivorState::WAIT);
		}
	}
	break;

	case ESurvivorAnimState::SKILL_04_BEGIN:
		m_wpFourthSkillSphereComponent.lock()->SetActive(false);
		break;

	default:
		break;
	}
}

void Editor::CAya::MoveForward(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveForward(_iValue);
}

void Editor::CAya::MoveBackward(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveBackward(_iValue);
}

void Editor::CAya::MoveRight(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveRight(_iValue);
}

void Editor::CAya::MoveLeft(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveLeft(_iValue);
}
