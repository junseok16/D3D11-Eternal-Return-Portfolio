#include "pch.h"
#include "StateComponent.h"

#include "Actor.h"

HRESULT Engine::CStateComponent::PreInitializeComponent()
{
	if (FAILED(CActorComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CStateComponent::InitializeComponent()
{
	if (FAILED(CActorComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CStateComponent::PostInitializeComponent()
{
	if (FAILED(CActorComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CStateComponent::BeginPlay()
{
	if (FAILED(CActorComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CStateComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// 진입 조건을 확인합니다.
	for (const auto& pair : m_mapEnterConditions)
	{
		// 진입 조건을 만족한 경우
		if (pair.second() == true)
		{
			CHECK(m_stkAnimStates.size() > 0);

			while (m_stkAnimStates.top() > pair.first)
			{
				m_stkAnimStates.pop();
			}

			if (m_stkAnimStates.top() == pair.first) { break; }

			m_stkAnimStates.push(pair.first /* 상태 번호 */);
			break;
		}
	}

	// 진출 조건을 확인합니다.
	while (true)
	{
		CHECK(m_stkAnimStates.size() > 0);

		// 진출 조건을 만족한 경우
		if (m_mapExitConditions[m_stkAnimStates.top()]() == true)
		{
			m_stkAnimStates.pop();
		}
		// 진출 조건을 만족하지 않은 경우
		else
		{
			break;
		}
	}

	return 0;
}

int32 Engine::CStateComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CStateComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CStateComponent::EndPlay()
{
	if (FAILED(CActorComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CStateComponent::Render()
{
	CActorComponent::Render();
}

void Engine::CStateComponent::Release()
{
	for (auto& pair : m_mapEnterConditions)
	{
		pair.second = nullptr;
	}
	m_mapEnterConditions.clear();

	for (auto& pair : m_mapExitConditions)
	{
		pair.second = nullptr;
	}
	m_mapExitConditions.clear();

	CActorComponent::Release();
}

HRESULT Engine::CStateComponent::RemoveEnterCondition(uint32 _iAnimState, const std::function<bool(void)>& _fnEnterCondition)
{
	if (m_mapEnterConditions.find(_iAnimState) == m_mapEnterConditions.end()) { return E_FAIL; }

	m_mapEnterConditions.erase(_iAnimState);
	return S_OK;
}

HRESULT Engine::CStateComponent::RemoveExitCondition(uint32 _iAnimState, const std::function<bool(void)>& _fnExitCondition)
{
	if (m_mapExitConditions.find(_iAnimState) == m_mapExitConditions.end()) { return E_FAIL; }

	m_mapExitConditions.erase(_iAnimState);
	return S_OK;
}

void Engine::CStateComponent::ClearEnterCondition()
{
	m_mapEnterConditions.clear();
}

void Engine::CStateComponent::ClearExitCondition()
{
	m_mapExitConditions.clear();
}

void Engine::CStateComponent::PushAnimState(uint32 _iAnimState)
{
	m_stkAnimStates.push(_iAnimState);
}

void Engine::CStateComponent::PopAnimState()
{
	if (m_stkAnimStates.empty()) { return; }
	
	m_stkAnimStates.pop();
}

void Engine::CStateComponent::OnAnimEnter(uint32 _iAnimState, float _fRatio)
{
	return;
}

void Engine::CStateComponent::OnAnimStay(uint32 _iAnimState,  float _fRatio)
{
	return;
}

void Engine::CStateComponent::OnAnimExit(uint32 _iAnimState, float _fRatio)
{
	return;
}
