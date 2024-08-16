#include "pch.h"
#include "CraftStateComponent.h"

#include "Survivor.h"

HRESULT Client::CCraftStateComponent::PreInitializeComponent()
{
	if (FAILED(CStateComponent::PreInitializeComponent())) { return E_FAIL; }
	m_eCraftState = ECraftState::CRAFT_NONE;
	return S_OK;
}

HRESULT Client::CCraftStateComponent::InitializeComponent()
{
	if (FAILED(CStateComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CCraftStateComponent::PostInitializeComponent()
{
	if (FAILED(CStateComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CCraftStateComponent::BeginPlay()
{
	if (FAILED(CStateComponent::BeginPlay())) { return E_FAIL; }

	PushAnimState((uint32)ECraftAnimState::CRAFT_NONE);

	// craft metal
	AddEnterCondition<CCraftStateComponent>
		(
			static_cast<uint32>(ECraftAnimState::CRAFT_METAL_BEGIN),
			static_pointer_cast<CCraftStateComponent>(shared_from_this()),
			&CCraftStateComponent::IsCraftMetalBeginEnterCondition
		);

	AddEnterCondition<CCraftStateComponent>
		(
			static_cast<uint32>(ECraftAnimState::CRAFT_METAL),
			static_pointer_cast<CCraftStateComponent>(shared_from_this()),
			&CCraftStateComponent::IsCraftMetalEnterCondition
		);

	AddExitCondition<CCraftStateComponent>
		(
			static_cast<uint32>(ECraftAnimState::CRAFT_METAL_BEGIN),
			static_pointer_cast<CCraftStateComponent>(shared_from_this()),
			&CCraftStateComponent::IsCraftMetalBeginExitCondition
		);

	AddExitCondition<CCraftStateComponent>
		(
			static_cast<uint32>(ECraftAnimState::CRAFT_METAL),
			static_pointer_cast<CCraftStateComponent>(shared_from_this()),
			&CCraftStateComponent::IsCraftMetalExitCondition
		);

	// craft food
	AddEnterCondition<CCraftStateComponent>
		(
			static_cast<uint32>(ECraftAnimState::CRAFT_FOOD_BEGIN),
			static_pointer_cast<CCraftStateComponent>(shared_from_this()),
			&CCraftStateComponent::IsCraftFoodBeginEnterCondition
		);

	AddEnterCondition<CCraftStateComponent>
		(
			static_cast<uint32>(ECraftAnimState::CRAFT_FOOD),
			static_pointer_cast<CCraftStateComponent>(shared_from_this()),
			&CCraftStateComponent::IsCraftFoodEnterCondition
		);

	AddExitCondition<CCraftStateComponent>
		(
			static_cast<uint32>(ECraftAnimState::CRAFT_FOOD_BEGIN),
			static_pointer_cast<CCraftStateComponent>(shared_from_this()),
			&CCraftStateComponent::IsCraftFoodBeginExitCondition
		);

	AddExitCondition<CCraftStateComponent>
		(
			static_cast<uint32>(ECraftAnimState::CRAFT_FOOD),
			static_pointer_cast<CCraftStateComponent>(shared_from_this()),
			&CCraftStateComponent::IsCraftFoodExitCondition
		);

	return S_OK;
}

int32 Client::CCraftStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	UpdateCraftState(_fDeltaSeconds);

	switch (CStateComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CCraftStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CCraftStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CStateComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CCraftStateComponent::EndPlay()
{
	if (FAILED(CStateComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CCraftStateComponent::Render()
{
	CStateComponent::Render();
}

void Client::CCraftStateComponent::Release()
{
	CStateComponent::Release();
}

bool Client::CCraftStateComponent::IsCraftNoneEnterCondition()
{
	return true;
}

bool Client::CCraftStateComponent::IsCraftMetalBeginEnterCondition()
{
	return m_eCraftState == ECraftState::CRAFT_METAL_BEGIN ? true : false;
}

bool Client::CCraftStateComponent::IsCraftMetalEnterCondition()
{
	return m_eCraftState == ECraftState::CRAFT_METAL ? true : false;
}

bool Client::CCraftStateComponent::IsCraftMetalBeginExitCondition()
{
	return m_eCraftState != ECraftState::CRAFT_METAL_BEGIN ? true : false;
}

bool Client::CCraftStateComponent::IsCraftMetalExitCondition()
{
	return m_eCraftState != ECraftState::CRAFT_METAL ? true : false;
}

bool Client::CCraftStateComponent::IsCraftNoneExitCondition()
{
	return false;
}

bool Client::CCraftStateComponent::IsCraftFoodBeginEnterCondition()
{
	return m_eCraftState == ECraftState::CRAFT_FOOD_BEGIN ? true : false;
}

bool Client::CCraftStateComponent::IsCraftFoodEnterCondition()
{
	return m_eCraftState == ECraftState::CRAFT_FOOD ? true : false;
}

bool Client::CCraftStateComponent::IsCraftFoodBeginExitCondition()
{
	return m_eCraftState != ECraftState::CRAFT_FOOD_BEGIN ? true : false;
}

bool Client::CCraftStateComponent::IsCraftFoodExitCondition()
{
	return m_eCraftState != ECraftState::CRAFT_FOOD ? true : false;
}

void Client::CCraftStateComponent::UpdateCraftState(float _fDeltaSeconds)
{
	switch (m_eCraftState)
	{
	case Client::ECraftState::CRAFT_NONE:
	{
		// 생존자의 상태가 CRAFT_METAL인 경우
		if (m_wpSurvivor.lock()->GetSurvivorState() == ESurvivorState::CRAFT_METAL)
		{
			m_eCraftState = ECraftState::CRAFT_METAL_BEGIN;
			break;
		}

		// 생존자의 상태가 CRAFT_FOOD인 경우
		if (m_wpSurvivor.lock()->GetSurvivorState() == ESurvivorState::CRAFT_FOOD)
		{
			m_eCraftState = ECraftState::CRAFT_FOOD_BEGIN;
			break;
		}
	}
	break;

	case Client::ECraftState::CRAFT_METAL_BEGIN:
	case Client::ECraftState::CRAFT_METAL:
	{
		// 생존자의 상태가 CRAFT_METAL이 아닌 경우
		if (m_wpSurvivor.lock()->GetSurvivorState() != ESurvivorState::CRAFT_METAL)
		{
			m_eCraftState = ECraftState::CRAFT_NONE;
			break;
		}
	}
	break;

	case Client::ECraftState::CRAFT_FOOD_BEGIN:
	case Client::ECraftState::CRAFT_FOOD:
	{
		// 생존자의 상태가 CRAFT_FOOD가 아닌 경우
		if (m_wpSurvivor.lock()->GetSurvivorState() != ESurvivorState::CRAFT_FOOD)
		{
			m_eCraftState = ECraftState::CRAFT_NONE;
			break;
		}
	}
	break;
	}
}

void Client::CCraftStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
}

void Client::CCraftStateComponent::OnAnimStay(uint32 _iAnimState, float _fRatio)
{
}

void Client::CCraftStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
{
	switch (static_cast<ECraftAnimState>(_iAnimState))
	{
	case ECraftAnimState::CRAFT_NONE:
		break;

	case ECraftAnimState::CRAFT_METAL_BEGIN:
		m_eCraftState = ECraftState::CRAFT_METAL;
		break;

	case ECraftAnimState::CRAFT_METAL:
		m_eCraftState = ECraftState::CRAFT_NONE;
		break;

	case ECraftAnimState::CRAFT_FOOD_BEGIN:
		m_eCraftState = ECraftState::CRAFT_FOOD;
		break;

	case ECraftAnimState::CRAFT_FOOD:
		m_eCraftState = ECraftState::CRAFT_NONE;
		break;

	default:
		break;
	}
}
