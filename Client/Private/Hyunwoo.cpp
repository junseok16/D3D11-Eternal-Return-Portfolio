// default
#include "pch.h"
#include "Hyunwoo.h"

// manager
#include "GameManager.h"

// controller
#include "Controller.h"

// component
#include "CameraComponent.h"
#include "InputComponent.h"
#include "NavigationComponent.h"
#include "SkeletalMeshComponent.h"
#include "HyunwooStateComponent.h"
#include "SphereComponent.h"
#include "OBBComponent.h"
#include "LightComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"

// enemy
#include "WildAnimal.h"
#include "Boss.h"

// socket
#include "Socket.h"
#include "Weapon.h"
#include "CraftTool.h"

// utility
#include "MathUtility.h"

#include "Inventory.h"
#include "Item.h"

HRESULT Client::CHyunwoo::PreInitialize()
{
	SetActorRenderType(ERenderType::OPAQUE_OBJECT);

	// 현우 개인 데이터
	{
		m_eSurvivorType								= ESurvivorType::HYUNWOO;
		m_iCurSurvivorLevel							= 0;
		m_arrAttackPower							= { 30.0f, 34.9f, 39.8f, 44.7f, 49.6f, 54.5f, 59.4f, 64.3f, 69.2f, 74.1f };
		m_arrDefensePower							= { 44.0f, 46.9f, 49.8f, 52.7f, 55.6f, 58.5f, 61.4f, 64.3f, 67.2f, 70.1f };
		m_fCurHP									= 880.0f;
		m_arrHPRegenerations						= { 1.8f, 1.89f, 1.98f, 2.07f, 2.16f, 2.25f, 2.34f, 2.43f, 2.52f, 2.61f, };
		m_arrMaxHPs									= { 880.0f, 972.0f, 1064.0f, 1156.0f, 1248.0f, 1340.0f, 1432.0f, 1524.0f, 1616.0f, 1708.0f };
		m_fCurSP									= 350.0f;
		m_arrSPRegenerations						= { 2.9f, 2.92f, 2.94f, 2.96f, 2.98f, 3.0f, 3.02f, 3.04f, 3.06f, 3.08f };
		m_arrMaxSPs									= { 350.0f, 366.0f, 382.0f, 398.0f, 414.0f, 430.0f, 446.0f, 462.0f, 478.0f, 494.0f };
		m_fSightRange								= 8.5f;
		m_fCurMoveSpeed								= 6.0f;

		m_arrMaxExps								= { 20.0f, 40.0f, 60.0f, 80.0f, 100.0f, 120.0f, 140.0f, 160.0f, 180.0f, 200.0f };
		m_arrMaxSkillLevels							= { 4, 4, 4, 2, 2 };

		m_vecMaxSkillCoolDown.resize(4);
		m_vecMaxSkillCoolDown[0]					= {  7.0f,  6.0f,  5.0f, 4.0f, 3.0f };
		m_vecMaxSkillCoolDown[1]					= { 15.0f, 13.0f, 11.0f, 9.0f, 7.0f };
		m_vecMaxSkillCoolDown[2]					= { 13.0f, 11.0f,  9.0f, 7.0f, 5.0f };
		m_vecMaxSkillCoolDown[3]					= { 30.0f, 20.0f, 10.0f };

		m_vecCurSkillCoolDown.resize(4);
		m_vecCurSkillCoolDown						= { 0.0f, 0.0f, 0.0f, 0.0f };
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

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(L"Hyunwoo");
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
		m_wpNavigationComponent.lock()->SetCurCellIndex(5757);
	}
	
	{
		m_wpSurvivorStateComponent = CreateActorComponent<CHyunwooStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	{
		m_wpLightComponent = CreateActorComponent<CLightComponent>(L"HyunwooLightComponent", EComponentType::POINT_LIGHT);
		m_wpLightComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpBodySphereComponent = CreateActorComponent<CSphereComponent>(L"BodySphereComponent", EComponentType::SPHERE);
		m_wpBodySphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}
	
	{
		m_wpAttackSphereComponent = CreateActorComponent<CSphereComponent>(L"AttackSphereComponent", EComponentType::SPHERE);
		m_wpAttackSphereComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpFirstSkillOBBComponent = CreateActorComponent<COBBComponent>(L"FirstSkillOBBComponent", EComponentType::OBB);
		m_wpFirstSkillOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpThirdSkillOBBComponent = CreateActorComponent<COBBComponent>(L"ThirdSkillOBBComponent", EComponentType::OBB);
		m_wpThirdSkillOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpFourthSkillOBBComponent = CreateActorComponent<COBBComponent>(L"FourthSkillOBBComponent", EComponentType::OBB);
		m_wpFourthSkillOBBComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpLeftAttackEffectComponent = CreateActorComponent<CEffectComponent>(L"HyunwooLeftAttackEffectComponent", EComponentType::EFFECT);
		m_wpLeftAttackEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpRightAttackEffectComponent = CreateActorComponent<CEffectComponent>(L"HyunwooRightAttackEffectComponent", EComponentType::EFFECT);
		m_wpRightAttackEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpHitEffectComponent = CreateActorComponent<CEffectComponent>(L"HyunwooHitEffectComponent", EComponentType::EFFECT);
		m_wpHitEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpFirstSkillEffectComponent = CreateActorComponent<CEffectComponent>(L"HyunwooFirstSkillEffectComponent", EComponentType::EFFECT);
		m_wpFirstSkillEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	
		m_wpSecondSkillEffectComponent = CreateActorComponent<CEffectComponent>(L"SecondSkillEffectComponent", EComponentType::EFFECT);
		m_wpSecondSkillEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	
		m_wpThirdSkillEffectComponent = CreateActorComponent<CEffectComponent>(L"HyunwooThirdSkillEffectComponent", EComponentType::EFFECT);
		m_wpThirdSkillEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpFourthSkillSlashEffectComponent = CreateActorComponent<CEffectComponent>(L"HyunwooFourthSkillSlashEffectComponent", EComponentType::EFFECT);
		m_wpFourthSkillSlashEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());

		m_wpFourthSkillEffectComponent = CreateActorComponent<CEffectComponent>(L"HyunwooFourthSkillEffectComponent", EComponentType::EFFECT);
		m_wpFourthSkillEffectComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
	}

	{
		m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
		m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSkeletalMeshComponent.lock());
		m_wpSoundComponent.lock()->SetListener(dynamic_pointer_cast<CActor>(shared_from_this()));
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

	// m_arrSockets[0] = CWeapon::Create(dynamic_pointer_cast<CActor>(shared_from_this()), "Weapon_R", EWeaponType::GLOVE);
	// m_arrSockets[0]->PreInitialize();

	m_arrSockets[0] = CCraftTool::Create(dynamic_pointer_cast<CActor>(shared_from_this()), "Craft_R_Hammer", ECraftToolType::HAMMER);
	m_arrSockets[0]->PreInitialize();

	return CSurvivor::PreInitialize();
}

HRESULT Client::CHyunwoo::Initialize()
{
	if (FAILED(CSurvivor::Initialize())) { return E_FAIL; }

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::WAIT,
		L"WAIT",
		{ "Hyunwoo_Glove_wait" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::ARRIVE,
		L"ARRIVE",
		{ "Hyunwoo_Common_arrive" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::RUN,
		L"RUN",
		{ "Hyunwoo_Glove_run" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::ATTACK_01,
		L"ATTACK_01",
		{ "Hyunwoo_Glove_atk01" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::ATTACK_02,
		L"ATTACK_02",
		{ "Hyunwoo_Glove_atk02" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState(
		(uint32)ESurvivorAnimState::SKILL_01,
		L"SKILL_01",
		{ "Hyunwoo_Glove_skill01" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_02,
		L"SKILL_02",
		{ "Hyunwoo_Glove_wait" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_03_BEGIN,
		L"SKILL_03_BEGIN",
		{ "Hyunwoo_Glove_skill03_start" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_03,
		L"SKILL_03",
		{ "Hyunwoo_Glove_skill03_loop" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_03_END,
		L"SKILL_03_END",
		{ "Hyunwoo_Glove_skill03_end" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_04_BEGIN,
		L"SKILL_04_BEGIN",
		{ "Hyunwoo_Glove_skill04_start" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_04,
		L"SKILL_04",
		{ "Hyunwoo_Glove_skill04_loop" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::SKILL_04_END,
		L"SKILL_04_END",
		{ "Hyunwoo_Glove_skill04_end" },
		false
	);
	
	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::COLLECT_STONE,
		L"COLLECT_STONE",
		{ "Hyunwoo_Common_Collect_Stone" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::COLLECT_WATER,
		L"COLLECT_WATER",
		{ "Hyunwoo_Common_Collect_Water" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::COLLECT_WOOD,
		L"COLLECT_WOOD",
		{ "Hyunwoo_Common_Collect_Wood" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::CRAFT_FOOD,
		L"CRAFT_FOOD",
		{ "Hyunwoo_Common_craftfood" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::CRAFT_METAL,
		L"CRAFT_METAL",
		{ "Hyunwoo_Common_craftmetal" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::OPERATE,
		L"OPERATE",
		{ "Hyunwoo_Common_operate" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::REST_BEGIN,
		L"REST_BEGIN",
		{ "Hyunwoo_Common_Rest_start" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::REST,
		L"REST",
		{ "Hyunwoo_Common_Rest_loop" },
		true
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::REST_END,
		L"REST_END",
		{ "Hyunwoo_Common_Rest_end" },
		false
	);

	m_wpSkeletalMeshComponent.lock()->AddAnimState
	(
		(uint32)ESurvivorAnimState::DEATH,
		L"DEATH",
		{ "Hyunwoo_Common_Death" },
		false
	);

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
		m_wpAttackSphereComponent.lock()->SetCenter({ 0.0f, 1.2f, 0.8f });
		m_wpAttackSphereComponent.lock()->SetRadius(1.0f);
		m_wpAttackSphereComponent.lock()->SetActive(false);
		m_wpAttackSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_SKILL);
		m_wpAttackSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}
	
	{
		m_wpFirstSkillOBBComponent.lock()->SetCenter({ 0.0f, 0.2f, 2.8f });
		m_wpFirstSkillOBBComponent.lock()->SetExtent({ 1.6f, 0.3f, 1.6f });
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);
		m_wpFirstSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_SKILL);
		m_wpFirstSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}
	
	{
		m_wpThirdSkillOBBComponent.lock()->SetCenter({ 0.0f, 1.0f, 0.6f });
		m_wpThirdSkillOBBComponent.lock()->SetExtent({ 1.8f, 1.0f, 0.3f });
		m_wpThirdSkillOBBComponent.lock()->SetActive(false);
		m_wpThirdSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_SKILL);
		m_wpThirdSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}
	
	{
		m_wpFourthSkillOBBComponent.lock()->SetCenter({ 0.0f, 1.0f, 0.1f });
		m_wpFourthSkillOBBComponent.lock()->SetExtent({ 2.6f, 1.0f, 0.1f });
		m_wpFourthSkillOBBComponent.lock()->SetActive(false);
		m_wpFourthSkillOBBComponent.lock()->SetCollisionLayer(ECollisionLayer::PLAYER_SKILL);
		m_wpFourthSkillOBBComponent.lock()->AddCollisionFlag(ECollisionLayer::MONSTER);
	}

	{
		m_wpLeftAttackEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHyunwooAttackLeftWind");
		m_wpLeftAttackEffectComponent.lock()->OffMeshEffect();

		m_wpRightAttackEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHyunwooAttackRightWind");
		m_wpRightAttackEffectComponent.lock()->OffMeshEffect();

		m_wpHitEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHitStar02");
		m_wpHitEffectComponent.lock()->OffMeshEffect();

		m_wpFirstSkillEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHyunwooSkill01HitRange");
		m_wpFirstSkillEffectComponent.lock()->OffMeshEffect();

		m_wpSecondSkillEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHyunwooSkill02");
		m_wpSecondSkillEffectComponent.lock()->OffMeshEffect();

		// m_wpThirdSkillEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHyunwooSkill03");
		// m_wpThirdSkillEffectComponent.lock()->OffMeshEffect();

		m_wpFourthSkillEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHyunwooSkill04HitRange");
		m_wpFourthSkillEffectComponent.lock()->OffMeshEffect();

		m_wpFourthSkillSlashEffectComponent.lock()->CreateMeshEffectDataGroup(L"FXHyunwooSkill04Slash");
		m_wpFourthSkillSlashEffectComponent.lock()->OffMeshEffect();

		/*
		{
			FParticleColorEffectProperty tParticleColorProperty;
			tParticleColorProperty.m_vStartColor = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
			tParticleColorProperty.m_vFinishColor = Vector4(0.8f, 0.8f, 0.8f, 1.0f);;

			FParticleMaskEffectProperty tParticleMaskProperty;
			tParticleMaskProperty.m_bUseParticleMask = true;
			tParticleMaskProperty.m_wstrParticleMaskTextureName = L"";
			tParticleMaskProperty.m_iParticleMaskRowColume[0] = 1;
			tParticleMaskProperty.m_iParticleMaskRowColume[1] = 1;
			tParticleMaskProperty.m_vParticleMaskUVSpeed = Vector2(0.0f, 0.0f);
			tParticleMaskProperty.m_vParticleMaskMaxUV = Vector2(1.0f, 1.0f);

			FParticlePlayEffectProperty tParticlePlayProperty;
			tParticlePlayProperty.m_fStartPlaySeconds = 0.0f;
			tParticlePlayProperty.m_fFinishPlaySeconds = 3.0f;
			tParticlePlayProperty.m_fMinLifeSeconds = 1.0f;
			tParticlePlayProperty.m_fMaxLifeSeconds = 3.0f;
			tParticlePlayProperty.m_bLoop = false;

			FParticleSizeEffectProperty tParticleSizeProperty;
			tParticleSizeProperty.m_fMinSize = 1.0f;
			tParticleSizeProperty.m_fMaxSize = 2.0f;
			tParticleSizeProperty.m_fMinSpeed = 3.0f;
			tParticleSizeProperty.m_fMaxSpeed = 6.0f;

			FParticleTransformEffectProperty tParticleTransformProperty;
			tParticleTransformProperty.m_iNumInstances = 10;
			tParticleTransformProperty.m_iEffectShapeType = ;
			tParticleTransformProperty.m_vPivot;
			tParticleTransformProperty.m_vCenter;
			tParticleTransformProperty.m_vRange;

			m_wpFourthSkillEffectComponent.lock()->CreateParticleEffectDataGroup
			(
				L"FXHyunwooSkill04Particle01",
				tParticlePlayProperty,
				tParticleTransformProperty,
				tParticleSizeProperty,
				tParticleMaskProperty,
				tParticleColorProperty
			);

			m_wpFourthSkillEffectComponent.lock()->OffParticleEffect();
		}
		*/
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->Initialize();
	}
	return S_OK;
}

HRESULT Client::CHyunwoo::PostInitialize()
{
	if (FAILED(CSurvivor::PostInitialize())) { return E_FAIL; }

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->PostInitialize();
	}
	return S_OK;
}

HRESULT Client::CHyunwoo::BeginPlay()
{
	if (FAILED(CSurvivor::BeginPlay())) { return E_FAIL; }

	//m_wpController = CGameManager::GetInstance()->GetController();
	m_wpController.lock()->EnableInput();
	m_wpController.lock()->GetPawn()->SetOnAir(true);

	// 맵의 월드 행렬이 항등 행렬일 때만 유효합니다.
	SetActorLocalPosition(m_wpNavigationComponent.lock()->GetCentroidPosition(5757));// 100

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->BeginPlay();
	}
	return S_OK;
}

int32 Client::CHyunwoo::PreTick(float _fDeltaSeconds)
{
	if (!m_bPosessed) { return 0; }

	switch (CSurvivor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->PreTick(_fDeltaSeconds);
	}

	return 0;
}

int32 Client::CHyunwoo::Tick(float _fDeltaSeconds)
{
	if (!m_bPosessed) { return 0; }

	switch (CSurvivor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->Tick(_fDeltaSeconds);
	}

	if (m_bSecondSkillApply)
	{
		m_fSumSecondSkillDeltaSeconds += _fDeltaSeconds;

		if (m_fSumSecondSkillDeltaSeconds >= 3.0f)
		{
			m_fSumSecondSkillDeltaSeconds = 0.0f;
			m_bSecondSkillApply = false;
		}
	}
	return 0;
}

int32 Client::CHyunwoo::PostTick(float _fDeltaSeconds)
{
	if (!m_bPosessed) { return 0; }

	switch (CSurvivor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->PostTick(_fDeltaSeconds);
	}
	return 0;
}

HRESULT Client::CHyunwoo::EndPlay()
{
	if (FAILED(CSurvivor::EndPlay())) { return E_FAIL; }

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->EndPlay();
	}
	return S_OK;
}

void Client::CHyunwoo::Render()
{
	if (!m_bPosessed) { return; }

	CSurvivor::Render();

	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->Render();
	}
}

void Client::CHyunwoo::Release()
{	
	for (const auto& spSocket : m_arrSockets)
	{
		spSocket->Release();
	}

	CSurvivor::Release();
}

void Client::CHyunwoo::OnCollisionEnter(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionEnter(_spSrc, _spDst);
}

void Client::CHyunwoo::OnCollisionStay(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionStay(_spSrc, _spDst);
}

void Client::CHyunwoo::OnCollisionExit(std::shared_ptr<CShapeComponent>& _spSrc, std::shared_ptr<CShapeComponent>& _spDst)
{
	CSurvivor::OnCollisionExit(_spSrc, _spDst);
}

void Client::CHyunwoo::OnAnimEnter(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::REST_BEGIN:
	{
		m_wpSoundComponent.lock()->PlaySoundEx("Hyunwoo_rest_1_ko", ESoundType::TALK_01);
	}
	break;
		
	case ESurvivorAnimState::ATTACK_01:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(0, 2));
		m_wpSoundComponent.lock()->PlaySoundEx("attackGlove_in_r" + strIndex, ESoundType::EFFECT_02);
		m_wpLeftAttackEffectComponent.lock()->PlayMeshEffect();
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.6f);
		m_wpAttackSphereComponent.lock()->SetActive(true);
	}
	break;

	case ESurvivorAnimState::ATTACK_02:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(0, 2));
		m_wpSoundComponent.lock()->PlaySoundEx("attackGlove_in_r" + strIndex, ESoundType::EFFECT_02);
		m_wpRightAttackEffectComponent.lock()->PlayMeshEffect();
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.6f);
		m_wpAttackSphereComponent.lock()->SetActive(true);
	}
	break;
	
	case ESurvivorAnimState::SKILL_01:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));
		m_wpSoundComponent.lock()->PlaySoundEx("Hyunwoo_PlaySkill1007200Seq0_" + strIndex + "_ko", ESoundType::TALK_01);
		m_wpFirstSkillOBBComponent.lock()->SetActive(true);
	}
	break;

	case ESurvivorAnimState::SKILL_02:
	{
		m_wpSecondSkillEffectComponent.lock()->PlayMeshEffect();
		string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));
		m_wpSoundComponent.lock()->PlaySoundEx("Hyunwoo_PlaySkill1007300Seq0_" + strIndex + "_ko", ESoundType::TALK_01);
		m_wpSoundComponent.lock()->PlaySoundEx("hyunwoo_Skill02_Activation", ESoundType::EFFECT_01);
	}
	break;

	case ESurvivorAnimState::SKILL_03_BEGIN:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));
		m_wpSoundComponent.lock()->PlaySoundEx("Hyunwoo_PlaySkill1007400Seq0_" + strIndex + "_ko", ESoundType::TALK_01);
		m_wpSoundComponent.lock()->PlaySoundEx("hyunwoo_Skill03_Slide", ESoundType::EFFECT_01);
		m_wpThirdSkillEffectComponent.lock()->PlayMeshEffect();
		m_wpThirdSkillOBBComponent.lock()->SetActive(true);
	}
	break;
	
	case ESurvivorAnimState::SKILL_03_END:
	{
		std::unordered_set<std::shared_ptr<CShapeComponent>>& usetShapeComponents = m_wpThirdSkillOBBComponent.lock()->GetShapeComponents();
		for (const auto& spShapeComponent : usetShapeComponents)
		{
			if (spShapeComponent->GetCollisionLayer() == ECollisionLayer::MONSTER)
			{
				// shared_ptr<CWildAnimal> spWildAnimal = static_pointer_cast<CWildAnimal>(spShapeComponent->GetOwnerActor());

				// if (spWildAnimal->IsDead()) { continue; }

				m_wpSoundComponent.lock()->PlaySoundEx("hyunwoo_Skill03_Hit", ESoundType::EFFECT_01);

				float fDamage = m_fAdditionalAttackPower;
				spShapeComponent->GetOwnerActor()->TakeDamage(fDamage + m_arrSkillInfos[2].m_vecAdditionalDamages[m_arrCurSkillLevels[2]], nullptr, static_pointer_cast<CHyunwoo>(shared_from_this()));
			}
		}

	}
	break;

	case ESurvivorAnimState::SKILL_04_BEGIN:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));
		m_wpSoundComponent.lock()->PlaySoundEx("Hyunwoo_PlaySkill1007500Seq0_" + strIndex + "_ko", ESoundType::TALK_01);
		m_wpSoundComponent.lock()->PlaySoundEx("hyunwoo_Skill04_Charging", ESoundType::EFFECT_01);
		m_wpFourthSkillEffectComponent.lock()->PlayMeshEffect();
		m_wpFourthSkillOBBComponent.lock()->SetActive(true);
	}
	break;

	case ESurvivorAnimState::SKILL_04_END:
		m_wpSoundComponent.lock()->StopSoundEx(ESoundType::EFFECT_01);
		m_wpSoundComponent.lock()->PlaySoundEx("hyunwoo_Skill04_Hit", ESoundType::EFFECT_01);
		m_wpFourthSkillSlashEffectComponent.lock()->PlayMeshEffect();
		break;

	case ESurvivorAnimState::DEATH:
		m_wpFourthSkillEffectComponent.lock()->OffMeshEffect();
		break;

	default:
		break;
	}
}

void Client::CHyunwoo::OnAnimStay(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::ATTACK_01:
	case ESurvivorAnimState::ATTACK_02:
	{
		if (0.2f <= _fRatio && m_bAttackApply == false)
		{
			m_bAttackApply = true;

			std::unordered_set<std::shared_ptr<CShapeComponent>>& usetShapeComponents = m_wpAttackSphereComponent.lock()->GetShapeComponents();
			for (const auto& spShapeComponent : usetShapeComponents)
			{
				switch (spShapeComponent->GetCollisionLayer())
				{
				case ECollisionLayer::MONSTER:
					m_wpSoundComponent.lock()->PlaySoundEx("hit_punch", ESoundType::EFFECT_03);

					float fDamage = m_arrAttackPower[m_iCurSurvivorLevel] + m_fAdditionalAttackPower;
					spShapeComponent->GetOwnerActor()->TakeDamage(fDamage, nullptr, static_pointer_cast<CHyunwoo>(shared_from_this()));
					break;
				}
			}
		}
	}
	break;

	case ESurvivorAnimState::SKILL_01:
	{
		if (0.1f <= _fRatio && m_bFirstSkillApply == false)
		{
			m_wpFirstSkillEffectComponent.lock()->PlayMeshEffect();
			m_wpSoundComponent.lock()->PlaySoundEx("hyunwoo_Skill01_Hit", ESoundType::EFFECT_01);
			m_bFirstSkillApply = true;

			std::unordered_set<std::shared_ptr<CShapeComponent>>& usetShapeComponents = m_wpFirstSkillOBBComponent.lock()->GetShapeComponents();
			for (const auto& spShapeComponent : usetShapeComponents)
			{
				switch (spShapeComponent->GetCollisionLayer())
				{
				case ECollisionLayer::MONSTER:
				{
					float fDamage = m_fAdditionalAttackPower;
					spShapeComponent->GetOwnerActor()->TakeDamage(fDamage + m_arrSkillInfos[0].m_vecDamages[m_arrCurSkillLevels[0]], nullptr, static_pointer_cast<CHyunwoo>(shared_from_this()));
				}
				break;
				}
			}
		}
	}
	break;

	case ESurvivorAnimState::SKILL_02:
		break;

	case ESurvivorAnimState::SKILL_03_BEGIN:
	{
		m_wpCameraComponent.lock()->SetLerpFOVTo(50.0f);

		Vector3 vForward = GetActorWorldForwardVector().value();
		vForward.Normalize();

		Vector3 vLocalPosition = GetActorLocalPosition().value();
		vLocalPosition += vForward * m_fDeltaSeconds * m_fCurMoveSpeed * m_fThirdSkillSpeedOffset;

		Vector3 vOutWorldPosition = Vector3::Zero;
		if (!m_wpNavigationComponent.lock()->IsValidCell(vLocalPosition, vOutWorldPosition))
		{
			// 벽에 부딪힌 경우, 스킬을 중지합니다.
			m_wpSurvivorStateComponent.lock()->SetServivorState(ESurvivorState::SKILL_03_END);
			return;
		}

		SetActorLocalPosition(vOutWorldPosition);
		
		// 적과 충돌한 경우, 앞으로 밀어냅니다.
		std::unordered_set<std::shared_ptr<CShapeComponent>>& usetShapeComponents = m_wpThirdSkillOBBComponent.lock()->GetShapeComponents();
		for (const auto& spShapeComponent : usetShapeComponents)
		{
			if (spShapeComponent->GetCollisionLayer() != ECollisionLayer::MONSTER) { continue; }
			
			shared_ptr<CWildAnimal> spWildAnimal = dynamic_pointer_cast<CWildAnimal>(spShapeComponent->GetOwnerActor());
			if (spWildAnimal && spWildAnimal->IsDead()) { continue; }

			shared_ptr<CBoss> spBoss = dynamic_pointer_cast<CBoss>(spShapeComponent->GetOwnerActor());
			if (spBoss && spBoss->IsDead()) { continue; }

			if (spWildAnimal)
			{
				bool bFoundActor = false;
				for (const auto& wpActor : m_vecThirdSkillActors)
				{
					if (wpActor.lock() == spWildAnimal)
					{
						bFoundActor = true;
						break;
					}
				}

				if (!bFoundActor)
				{
					m_vecThirdSkillActors.push_back(spWildAnimal);
					spWildAnimal->TakeDamage(m_arrSkillInfos[2].m_vecDamages[m_arrCurSkillLevels[2]], nullptr, static_pointer_cast<CHyunwoo>(shared_from_this()));
				}

				Vector3 vEnemyLocalPosition = spWildAnimal->GetActorLocalPosition().value();
				vEnemyLocalPosition += vForward * m_fDeltaSeconds * m_fCurMoveSpeed * m_fThirdSkillSpeedOffset;

				std::shared_ptr<CNavigationComponent> spNavigationComponent = spWildAnimal->FindActorComponent<CNavigationComponent>(L"NavigationComponent");

				Vector3 vOutEnemyWorldPosition = Vector3::Zero;
				if (!spNavigationComponent->IsValidCell(vEnemyLocalPosition, vOutEnemyWorldPosition)) { continue; }

				spWildAnimal->SetActorLocalPosition(vOutEnemyWorldPosition);
			}

			if (spBoss)
			{
				bool bFoundActor = false;
				for (const auto& wpActor : m_vecThirdSkillActors)
				{
					if (wpActor.lock() == spBoss)
					{
						bFoundActor = true;
						break;
					}
				}

				if (!bFoundActor)
				{
					m_vecThirdSkillActors.push_back(spBoss);
					spBoss->TakeDamage(m_arrSkillInfos[2].m_vecDamages[m_arrCurSkillLevels[2]], nullptr, static_pointer_cast<CHyunwoo>(shared_from_this()));
				}

				Vector3 vEnemyLocalPosition = spBoss->GetActorLocalPosition().value();
				vEnemyLocalPosition += vForward * m_fDeltaSeconds * m_fCurMoveSpeed * m_fThirdSkillSpeedOffset;

				std::shared_ptr<CNavigationComponent> spNavigationComponent = spBoss->FindActorComponent<CNavigationComponent>(L"NavigationComponent");

				Vector3 vOutEnemyWorldPosition = Vector3::Zero;
				if (!spNavigationComponent->IsValidCell(vEnemyLocalPosition, vOutEnemyWorldPosition)) { continue; }

				spBoss->SetActorLocalPosition(vOutEnemyWorldPosition);
			}
		}
	}
	break;

	case ESurvivorAnimState::SKILL_03:
		break;

	case ESurvivorAnimState::SKILL_03_END:
	{
		m_wpThirdSkillEffectComponent.lock()->OffMeshEffect();
		Vector3 vBackward = -GetActorWorldForwardVector().value();
		vBackward.Normalize();

		Vector3 vLocalPosition = GetActorLocalPosition().value();
		vLocalPosition += vBackward * m_fDeltaSeconds * m_fCurMoveSpeed * 2.0f;

		Vector3 vOutWorldPosition = Vector3::Zero;
		if (!m_wpNavigationComponent.lock()->IsValidCell(vLocalPosition, vOutWorldPosition)) { break; }
		SetActorLocalPosition(vOutWorldPosition);
	}
	break;

	case ESurvivorAnimState::SKILL_04_BEGIN:
		m_fFourthSkillCurDepth += m_fDeltaSeconds;
		m_fFourthSkillCurDepth = clamp(m_fFourthSkillCurDepth, m_fFourthSkillMinDepth, m_fFourthSkillMaxDepth);
		m_wpFourthSkillOBBComponent.lock()->SetCenter({ 0.0f, 1.0f, m_fFourthSkillMinDepth + m_fFourthSkillCurDepth });
		m_wpFourthSkillOBBComponent.lock()->SetExtent({ 2.6f, 1.0f, m_fFourthSkillMinDepth + m_fFourthSkillCurDepth });
		break;


	case ESurvivorAnimState::SKILL_04_END:
	{
		if (0.1f <= _fRatio && !m_bFourthSkillApply)
		{
			m_wpFourthSkillEffectComponent.lock()->OffMeshEffect();
			m_bFourthSkillApply = true;

			std::unordered_set<std::shared_ptr<CShapeComponent>>& usetShapeComponents = m_wpFourthSkillOBBComponent.lock()->GetShapeComponents();
			for (const auto& spShapeComponent : usetShapeComponents)
			{
				switch (spShapeComponent->GetCollisionLayer())
				{
				case ECollisionLayer::MONSTER:
				{
					float fDamage = m_fAdditionalAttackPower;
					spShapeComponent->GetOwnerActor()->TakeDamage(fDamage + m_arrSkillInfos[3].m_vecDamages[m_arrCurSkillLevels[3]], nullptr, static_pointer_cast<CHyunwoo>(shared_from_this()));
				}
				break;
				}
			}
		}
	}
	break;

	case ESurvivorAnimState::CRAFT_METAL:
		break;

	case ESurvivorAnimState::DEATH:
		break;

	default:
		break;
	}
}

void Client::CHyunwoo::OnAnimExit(uint32 _iAnimState, uint32 _iAnimIndex, float _fRatio)
{
	switch (static_cast<ESurvivorAnimState>(_iAnimState))
	{
	case ESurvivorAnimState::WAIT:				break;
	case ESurvivorAnimState::RUN:				break;
	case ESurvivorAnimState::ATTACK_01:
	case ESurvivorAnimState::ATTACK_02:
		m_bAttackApply = false;
		m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
		m_wpAttackSphereComponent.lock()->SetActive(false);
		break;

	case ESurvivorAnimState::SKILL_01:
		m_bFirstSkillApply = false;
		m_wpFirstSkillOBBComponent.lock()->SetActive(false);
		break;

	case ESurvivorAnimState::SKILL_02:			break;

	case ESurvivorAnimState::SKILL_03_BEGIN:
		m_vecThirdSkillActors.clear();
		m_wpThirdSkillOBBComponent.lock()->SetActive(false);
		break;

	case ESurvivorAnimState::SKILL_03:			break;
	case ESurvivorAnimState::SKILL_03_END:
		m_vecThirdSkillActors.clear();
		m_wpThirdSkillOBBComponent.lock()->SetActive(false);
		m_wpCameraComponent.lock()->SetLerpFOVTo(60.0f);
		break;

	case ESurvivorAnimState::SKILL_04_BEGIN:	break;
	case ESurvivorAnimState::SKILL_04:			break;
	case ESurvivorAnimState::SKILL_04_END:
		m_wpFourthSkillEffectComponent.lock()->OffMeshEffect();
		m_bFourthSkillApply = false;
		m_fFourthSkillCurDepth = 0.0f;
		m_wpFourthSkillOBBComponent.lock()->SetCenter({ 0.0f, 1.0f, 0.1f });
		m_wpFourthSkillOBBComponent.lock()->SetExtent({ 2.6f, 1.0f, 0.1f });
		m_wpFourthSkillOBBComponent.lock()->SetActive(false);
		break;

	case ESurvivorAnimState::CRAFT_METAL:
	{
		string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));

		switch (_iAnimIndex)
		{
		case 2:
			m_wpSoundComponent.lock()->PlaySoundEx("Hyunwoo_craftUncommon_" + strIndex + "_ko", ESoundType::TALK_01);
			break;

		case 3:
			m_wpSoundComponent.lock()->PlaySoundEx("Hyunwoo_craftRare_" + strIndex + "_ko", ESoundType::TALK_01);
			break;

		case 4:
			m_wpSoundComponent.lock()->PlaySoundEx("Hyunwoo_craftEpic_" + strIndex + "_ko", ESoundType::TALK_01);
			break;

		default:
			break;
		}
	}
	break;

	case ESurvivorAnimState::CRAFT_FOOD:
		break;

	case ESurvivorAnimState::DEATH:
		m_wpBodySphereComponent.lock()->SetActive(false);
		m_wpSkeletalMeshComponent.lock()->StopAnimation();
		break;

	default:
		break;
	}

	m_wpSkeletalMeshComponent.lock()->SetPlayRate(1.0f);
}

void Client::CHyunwoo::MoveForward(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveForward(_iValue);
}

void Client::CHyunwoo::MoveBackward(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveBackward(_iValue);
}

void Client::CHyunwoo::MoveRight(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveRight(_iValue);
}

void Client::CHyunwoo::MoveLeft(int32 _iValue)
{
	if (m_wpSurvivorStateComponent.lock()->GetCurAnimState() != (uint32)ESurvivorState::RUN) { return; }

	CSurvivor::MoveLeft(_iValue);
}

float Client::CHyunwoo::TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn)
{
	if (m_bSecondSkillApply)
	{
		return 0.0f;
	}

	float fDamage = _fDamageAmount - (m_arrDefensePower[m_iCurSurvivorLevel] + m_fAdditionalDefensePower);
	if (fDamage <= 0.0f) { fDamage = 10.0f; }
	m_fCurHP -= fDamage;

	if (m_fCurHP <= 0.0f)
	{
		m_fCurHP = 0.0f;
		return 0.0f;
	}

	Vector3 vFrom = { 0.5f, 1.0f, -1.0f };
	Vector3 vTo = { 0.5f, 1.8f, -0.5f };

	Vector3 vPosition = CMathUtility::GetRandomDirection(vFrom, vTo);
	float fScale = static_cast<float>(CMathUtility::GetRandomInteger(7, 12)) / 10.0f;

	m_wpHitEffectComponent.lock()->SetComponentLocalPosition(vPosition);
	m_wpHitEffectComponent.lock()->SetComponentLocalScale({ fScale, fScale, fScale });
	m_wpHitEffectComponent.lock()->PlayMeshEffect();

	return 0.0f;
}
