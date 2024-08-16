#include "pch.h"
#include "InputComponent.h"

#include "World.h"
#include "EngineModule.h"
#include "InputManager.h"

HRESULT Engine::CInputComponent::PreInitializeComponent()
{
	if (FAILED(CActorComponent::PreInitializeComponent())) { return E_FAIL; }
	m_wpInputManager = CWorld::GetInstance()->GetEngineModule()->GetInputManager();

	return S_OK;
}

HRESULT Engine::CInputComponent::InitializeComponent()
{
	if (FAILED(CActorComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CInputComponent::PostInitializeComponent()
{
	if (FAILED(CActorComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CInputComponent::BeginPlay()
{
	if (FAILED(CActorComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CInputComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::PreTickComponent(_fDeltaSeconds))
	{
	case 0:		break;
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CInputComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::TickComponent(_fDeltaSeconds))
	{
	case 0:		break;
	case -1:	return -1;
	default:	break;
	}

	if (!m_bInput) { return 0; }

	// 키보드 액시스 매핑을 업데이트합니다.
	for (const auto& pair : m_umapKeyAxisMaps)
	{
		// (axis name, <key, scale>)
		int32 iKey = pair.second.first;
		if (m_wpInputManager.lock()->IsKeyPressed(iKey))
		{
			m_umapKeyAxisCallbacks[pair.first](pair.second.second);
		}
	}

	// 키보드 액션 매핑을 업데이트합니다.
	for (const auto& pair : m_umapKeyActionMaps)
	{
		int32 iKey = pair.second;
		if (m_wpInputManager.lock()->IsKeyDown(iKey))
		{
			if (!m_umapKeyActionCallbacks[pair.first]())
			{
				break;
			}
		}
	}

	// 마우스 액시스 매핑을 업데이트합니다.
	for (const auto& pair : m_umapMouseAxisMaps)
	{
		int32 iKey = pair.second.first;
		if (int32 iDelta = m_wpInputManager.lock()->GetMouseDelta(static_cast<EMouseAxisType>(iKey)))
		{
			m_umapMouseAxisCallbacks[pair.first](iDelta);
		}
	}

	// 마우스 액션 매핑을 업데이트합니다.
	for (const auto& pair : m_umapMouseActionMaps)
	{
		int32 iKey = pair.second;
		if (m_wpInputManager.lock()->IsMouseDown(static_cast<EMouseActionType>(iKey)))
		{
			m_umapMouseActionCallbacks[pair.first]();
		}
	}

	return 0;
}

int32 Engine::CInputComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CActorComponent::PostTickComponent(_fDeltaSeconds))
	{
	case 0:		break;
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CInputComponent::EndPlay()
{
	if (FAILED(CActorComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CInputComponent::Render()
{
	CActorComponent::Render();
}

void Engine::CInputComponent::Release()
{
	for (auto& pair : m_umapKeyAxisCallbacks)
	{
		pair.second = nullptr;
	}
	m_umapKeyAxisCallbacks.clear();

	for (auto& pair : m_umapKeyActionCallbacks)
	{
		pair.second = nullptr;
	}
	m_umapKeyActionCallbacks.clear();
	
	for (auto& pair : m_umapMouseAxisCallbacks)
	{
		pair.second = nullptr;
	}
	m_umapMouseAxisCallbacks.clear();

	CActorComponent::Release();
}

HRESULT Engine::CInputComponent::MapKeyAxis(const std::wstring& _wstrKeyAxis, int32 _iKey, int32 _iScale)
{
	if (m_umapKeyAxisMaps.find(_wstrKeyAxis) != m_umapKeyAxisMaps.end()) { return E_FAIL; }

	m_umapKeyAxisMaps.insert({ _wstrKeyAxis, { _iKey, _iScale } });
	return S_OK;
}

HRESULT Engine::CInputComponent::MapKeyAction(const std::wstring& _wstrKeyAction, int32 _iKey)
{
	if (m_umapKeyActionMaps.find(_wstrKeyAction) != m_umapKeyActionMaps.end()) { return E_FAIL; }

	m_umapKeyActionMaps.insert({ _wstrKeyAction, _iKey });
	return S_OK;
}

HRESULT Engine::CInputComponent::MapMouseAxis(const std::wstring& _wstrMouseAxis, int32 _iKey, int32 _iScale)
{
	if (m_umapMouseAxisMaps.find(_wstrMouseAxis) != m_umapMouseAxisMaps.end()) { return E_FAIL; }

	m_umapMouseAxisMaps.insert({ _wstrMouseAxis, { _iKey, _iScale } });
	return S_OK;
}

HRESULT Engine::CInputComponent::MapMouseAction(const std::wstring& _wstrMouseAction, int32 _iKey)
{
	if (m_umapMouseActionMaps.find(_wstrMouseAction) != m_umapMouseActionMaps.end()) { return E_FAIL; }

	m_umapMouseActionMaps.insert({ _wstrMouseAction, _iKey });
	return S_OK;
}

void Engine::CInputComponent::ClearKeyAction()
{
	m_umapKeyActionMaps.clear();
	m_umapKeyActionCallbacks.clear();
}

void Engine::CInputComponent::ClearKeyAxis()
{
	m_umapKeyAxisMaps.clear();
	m_umapKeyAxisCallbacks.clear();
}

bool Engine::CInputComponent::IsKeyDown(int32 _iKey) const
{
	return m_wpInputManager.lock()->IsKeyDown(_iKey);
}

bool Engine::CInputComponent::IsKeyPressed(int32 _iKey) const
{
	return m_wpInputManager.lock()->IsKeyPressed(_iKey);
}

bool Engine::CInputComponent::IsKeyUp(int32 _iKey) const
{
	return m_wpInputManager.lock()->IsKeyUp(_iKey);
}

bool Engine::CInputComponent::IsMouseDown(EMouseActionType _eMouseActionType) const
{
	return m_wpInputManager.lock()->IsMouseDown(_eMouseActionType);
}

bool Engine::CInputComponent::IsMousePressed(EMouseActionType _eMouseActionType) const
{
	return m_wpInputManager.lock()->IsMousePressed(_eMouseActionType);
}

void Engine::CInputComponent::LockCursor(bool _bCursorLocked)
{
	m_wpInputManager.lock()->LockCursor(_bCursorLocked);
}
