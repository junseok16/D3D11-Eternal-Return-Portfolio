#include "pch.h"
#include "SurvivorStateComponent.h"

#include "Survivor.h"
#include "Controller.h"

#include "InputComponent.h"
#include "CameraComponent.h"
#include "SoundComponent.h"

HRESULT Client::CSurvivorStateComponent::PreInitializeComponent()
{
	if (FAILED(CStateComponent::PreInitializeComponent())) { return E_FAIL; }
	m_eSurvivorState = ESurvivorState::WAIT;
	return S_OK;
}

HRESULT Client::CSurvivorStateComponent::InitializeComponent()
{
	if (FAILED(CStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CSurvivorStateComponent::PostInitializeComponent()
{
	if (FAILED(CStateComponent::PostInitializeComponent())) { return E_FAIL; }

	m_wpSurvivor = dynamic_pointer_cast<CSurvivor>(m_wpOwnerActor.lock());
	return S_OK;
}

HRESULT Client::CSurvivorStateComponent::BeginPlay()
{
	if (FAILED(CStateComponent::BeginPlay())) { return E_FAIL; }

	shared_ptr<CController> spController = m_wpSurvivor.lock()->GetController();
	if (spController)
	{
		m_wpInputComponent = spController->GetInputComponent();
		m_wpCameraComponent = m_wpSurvivor.lock()->FindActorComponent<CCameraComponent>(L"CameraComponent");
		m_wpSoundComponent = m_wpSurvivor.lock()->FindActorComponent<CSoundComponent>(L"SoundComponent");
	}

	// 마우스 커서를 잠급니다.
	m_wpInputComponent.lock()->LockCursor(true);

	PushAnimState((uint32)ESurvivorAnimState::WAIT);

	// wait
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::WAIT),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsWaitEnterCondition
		);

	// arrive
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::ARRIVE),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsArriveEnterCondition
		);

	// run
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::RUN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsRunEnterCondition
		);

	// attack
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::ATTACK_01),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFirstAttackEnterCondition
		);

	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::ATTACK_02),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsSecondAttackEnterCondition
		);

	// 1st skill
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_01),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFirstSkillEnterCondition
		);

	// 2nd skill begin
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_02_BEGIN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsSecondSkillBeginEnterCondition
		);

	// 2nd skill
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_02),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsSecondSkillEnterCondition
		);

	// 2nd skill end
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_02_END),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsSecondSkillEndEnterCondition
		);

	// 3rd skill begin
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_03_BEGIN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsThirdSkillBeginEnterCondition
		);

	// 3rd skill
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_03),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsThirdSkillEnterCondition
		);

	// 3rd skill end
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_03_END),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsThirdSkillEndEnterCondition
		);

	// 4th skill begin
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_04_BEGIN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFourthSkillBeginEnterCondition
		);

	// 4th skill
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_04),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFourthSkillEnterCondition
		);

	// 4th skill end
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_04_END),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFourthSkillEndEnterCondition
		);

	// box open

	// collect stone
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::COLLECT_STONE),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCollectStoneEnterCondition
		);

	// collect water
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::COLLECT_WATER),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCollectWaterEnterCondition
		);

	// collect wood
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::COLLECT_WOOD),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCollectWoodEnterCondition
		);

	// craft food
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::CRAFT_FOOD),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCraftFoodEnterCondition
		);

	// craft metal
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::CRAFT_METAL),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCraftMetalEnterCondition
		);

	// fishing

	// install trap

	// rest begin
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::REST_BEGIN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsRestBeginEnterCondition
		);

	// rest 
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::REST),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsRestEnterCondition
		);

	// rest end
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::REST_END),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsRestEndEnterCondition
		);

	// operate
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::OPERATE),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsOperateEnterCondition
		);

	// death
	AddEnterCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::DEATH),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsDeathEnterCondition
		);




	// wait
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::WAIT),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsWaitExitCondition
		);

	// arrive
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::ARRIVE),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsArriveExitCondition
		);

	// run
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::RUN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsRunExitCondition
		);

	// attack
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::ATTACK_01),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFirstAttackExitCondition
		);

	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::ATTACK_02),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsSecondAttackExitCondition
		);

	// skill 01
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_01),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFirstSkillExitCondition
		);


	// 2nd skill begin
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_02_BEGIN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsSecondSkillBeginExitCondition
		);

	// 2nd skill 02
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_02),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsSecondSkillExitCondition
		);

	// 2nd skill end
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_02_END),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsSecondSkillEndExitCondition
		);

	// 3rd skill
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_03_BEGIN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsThirdSkillBeginExitCondition
		);

	// 3rd skill
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_03),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsThirdSkillExitCondition
		);

	// 3rd skill
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_03_END),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsThirdSkillEndExitCondition
		);

	// 4th skill begin
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_04_BEGIN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFourthSkillBeginExitCondition
		);

	// 4th skill
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_04),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFourthSkillExitCondition
		);

	// 4th skill end
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::SKILL_04_END),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsFourthSkillEndExitCondition
		);

	// box open

	// collect stone
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::COLLECT_STONE),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCollectStoneExitCondition
		);

	// collect water
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::COLLECT_WATER),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCollectWaterExitCondition
		);

	// collect wood
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::COLLECT_WOOD),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCollectWoodExitCondition
		);

	// craft food
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::CRAFT_FOOD),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCraftFoodExitCondition
		);

	// craft metal
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::CRAFT_METAL),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsCraftMetalExitCondition
		);

	// fishing

	// install trap

	// rest begin
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::REST_BEGIN),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsRestBeginExitCondition
		);

	// rest 
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::REST),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsRestExitCondition
		);

	// rest end
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::REST_END),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsRestEndExitCondition
		);

	// operate
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::OPERATE),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsOperateExitCondition
		);

	// death
	AddExitCondition<CSurvivorStateComponent>
		(
			static_cast<uint32>(ESurvivorAnimState::DEATH),
			static_pointer_cast<CSurvivorStateComponent>(shared_from_this()),
			&CSurvivorStateComponent::IsDeathExitCondition
		);

	return S_OK;
}

int32 Client::CSurvivorStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CSurvivorStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CSurvivorStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CSurvivorStateComponent::EndPlay()
{
	if (FAILED(CStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CSurvivorStateComponent::Render()
{
	CStateComponent::Render();
}

void Client::CSurvivorStateComponent::Release()
{
	CStateComponent::Release();
}

bool Client::CSurvivorStateComponent::IsWaitEnterCondition()
{
	return true;
}

bool Client::CSurvivorStateComponent::IsRunEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::RUN ? true : false;
}

bool Client::CSurvivorStateComponent::IsArriveEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::ARRIVE ? true : false;
}

bool Client::CSurvivorStateComponent::IsFirstAttackEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::ATTACK_01 ? true : false;
}

bool Client::CSurvivorStateComponent::IsSecondAttackEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::ATTACK_02 ? true : false;
}

bool Client::CSurvivorStateComponent::IsFirstSkillEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_01 ? true : false;
}

bool Client::CSurvivorStateComponent::IsSecondSkillBeginEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_02_BEGIN ? true : false;
}

bool Client::CSurvivorStateComponent::IsSecondSkillEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_02 ? true : false;
}

bool Client::CSurvivorStateComponent::IsSecondSkillEndEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_02_END ? true : false;
}

bool Client::CSurvivorStateComponent::IsThirdSkillBeginEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_03_BEGIN ? true : false;
}

bool Client::CSurvivorStateComponent::IsThirdSkillEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_03 ? true : false;
}

bool Client::CSurvivorStateComponent::IsThirdSkillEndEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_03_END ? true : false;
}

bool Client::CSurvivorStateComponent::IsFourthSkillBeginEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_04_BEGIN ? true : false;
}

bool Client::CSurvivorStateComponent::IsFourthSkillEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_04 ? true : false;
}

bool Client::CSurvivorStateComponent::IsFourthSkillEndEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::SKILL_04_END ? true : false;
}

bool Client::CSurvivorStateComponent::IsCollectStoneEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::COLLECT_STONE ? true : false;
}

bool Client::CSurvivorStateComponent::IsCollectWaterEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::COLLECT_WATER ? true : false;
}

bool Client::CSurvivorStateComponent::IsCollectWoodEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::COLLECT_WOOD ? true : false;
}

bool Client::CSurvivorStateComponent::IsCraftFoodEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::CRAFT_FOOD ? true : false;
}

bool Client::CSurvivorStateComponent::IsCraftMetalEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::CRAFT_METAL ? true : false;
}

bool Client::CSurvivorStateComponent::IsRestBeginEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::REST_BEGIN ? true : false;
}

bool Client::CSurvivorStateComponent::IsRestEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::REST ? true : false;
}

bool Client::CSurvivorStateComponent::IsRestEndEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::REST_END ? true : false;
}

bool Client::CSurvivorStateComponent::IsOperateEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::OPERATE ? true : false;
}

bool Client::CSurvivorStateComponent::IsDeathEnterCondition()
{
	return m_eSurvivorState == ESurvivorState::DEATH ? true : false;
}

bool Client::CSurvivorStateComponent::IsWaitExitCondition()
{
	return false;
}

bool Client::CSurvivorStateComponent::IsRunExitCondition()
{
	return m_eSurvivorState != ESurvivorState::RUN ? true : false;
}

bool Client::CSurvivorStateComponent::IsArriveExitCondition()
{
	return m_eSurvivorState != ESurvivorState::ARRIVE ? true : false;
}

bool Client::CSurvivorStateComponent::IsFirstAttackExitCondition()
{
	return m_eSurvivorState != ESurvivorState::ATTACK_01 ? true : false;
}

bool Client::CSurvivorStateComponent::IsSecondAttackExitCondition()
{
	return m_eSurvivorState != ESurvivorState::ATTACK_02 ? true : false;
}

bool Client::CSurvivorStateComponent::IsFirstSkillExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_01 ? true : false;
}

bool Client::CSurvivorStateComponent::IsSecondSkillBeginExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_02_BEGIN ? true : false;
}

bool Client::CSurvivorStateComponent::IsSecondSkillExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_02 ? true : false;
}

bool Client::CSurvivorStateComponent::IsSecondSkillEndExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_02_END ? true : false;
}

bool Client::CSurvivorStateComponent::IsThirdSkillBeginExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_03_BEGIN ? true : false;
}

bool Client::CSurvivorStateComponent::IsThirdSkillExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_03 ? true : false;
}

bool Client::CSurvivorStateComponent::IsThirdSkillEndExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_03_END ? true : false;
}

bool Client::CSurvivorStateComponent::IsFourthSkillBeginExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_04_BEGIN ? true : false;
}

bool Client::CSurvivorStateComponent::IsFourthSkillExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_04 ? true : false;
}

bool Client::CSurvivorStateComponent::IsFourthSkillEndExitCondition()
{
	return m_eSurvivorState != ESurvivorState::SKILL_04_END ? true : false;
}

bool Client::CSurvivorStateComponent::IsCollectStoneExitCondition()
{
	if (m_fSumCollectStoneSeconds > m_wpSurvivor.lock()->GetCollectSeconds())
	{
		m_eSurvivorState = ESurvivorState::WAIT;
		m_fSumCollectStoneSeconds = 0.0f;
		return true;
	}

	return false;
}

bool Client::CSurvivorStateComponent::IsCollectWaterExitCondition()
{
	if (m_fSumCollectWaterSeconds > m_wpSurvivor.lock()->GetCollectSeconds())
	{
		m_eSurvivorState = ESurvivorState::WAIT;
		m_fSumCollectWaterSeconds = 0.0f;
		return true;
	}

	return false;
}

bool Client::CSurvivorStateComponent::IsCollectWoodExitCondition()
{
	if (m_fSumCollectBranchSeconds > m_wpSurvivor.lock()->GetCollectSeconds())
	{
		m_eSurvivorState = ESurvivorState::WAIT;
		m_fSumCollectBranchSeconds = 0.0f;
		return true;
	}

	return false;
}

bool Client::CSurvivorStateComponent::IsCraftFoodExitCondition()
{
	return m_eSurvivorState != ESurvivorState::CRAFT_FOOD ? true : false;
}

bool Client::CSurvivorStateComponent::IsCraftMetalExitCondition()
{
	return m_eSurvivorState != ESurvivorState::CRAFT_METAL ? true : false;
}

bool Client::CSurvivorStateComponent::IsRestBeginExitCondition()
{
	return m_eSurvivorState != ESurvivorState::REST_BEGIN ? true : false;
}

bool Client::CSurvivorStateComponent::IsRestExitCondition()
{
	return m_eSurvivorState != ESurvivorState::REST ? true : false;
}

bool Client::CSurvivorStateComponent::IsRestEndExitCondition()
{
	return m_eSurvivorState != ESurvivorState::REST_END ? true : false;
}

bool Client::CSurvivorStateComponent::IsOperateExitCondition()
{
	if (m_fSumOperateSeconds > m_wpSurvivor.lock()->GetConsoleSeconds())
	{
		m_eSurvivorState = ESurvivorState::WAIT;
		m_fSumOperateSeconds = 0.0f;
		return true;
	}

	return false;
}

bool Client::CSurvivorStateComponent::IsDeathExitCondition()
{
	return false;
}

void Client::CSurvivorStateComponent::UpdateSurvivorState(float _fDeltaSeconds)
{
	return;
}
