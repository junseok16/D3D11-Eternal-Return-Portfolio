#include "pch.h"
#include "Button.h"

#include "GeometryComponent.h"

#include "World.h"
#include "EngineModule.h"
#include "DeviceManager.h"
#include "InputManager.h"

HRESULT Engine::CButton::PreInitialize()
{
	if (FAILED(CUI::PreInitialize())) { return E_FAIL; }

	m_wpButtonComponent = CreateActorComponent<CGeometryComponent>(L"GeometryComponent", EComponentType::GEOMETRY);
	SetRootComponent(m_wpButtonComponent.lock());

	switch (m_ePrimitiveType)
	{
	case Engine::EPrimitiveType::POINT:
		m_wpButtonComponent.lock()->SetPrimitiveType(EPrimitiveType::POINT);
		m_wpButtonComponent.lock()->SetTextureNames(m_vecButtonNames);
		m_wpButtonComponent.lock()->SetVertexShaderDesc(L"VS_Point2Rect");
		m_wpButtonComponent.lock()->SetPixelShaderDesc(L"PS_Point2Rect");
		m_wpButtonComponent.lock()->SetGeometryShaderDesc(L"GS_Point2Rect");
		break;

	case Engine::EPrimitiveType::RECT:
	case Engine::EPrimitiveType::CUBE:
		m_wpButtonComponent.lock()->SetPrimitiveType(m_ePrimitiveType);
		m_wpButtonComponent.lock()->SetTextureNames(m_vecButtonNames);
		m_wpButtonComponent.lock()->SetVertexShaderDesc(m_wstrVertexShaderName);
		m_wpButtonComponent.lock()->SetPixelShaderDesc(m_wstrPixelShaderName);
		m_wpButtonComponent.lock()->SetGeometryShaderDesc(m_wstrGeometryShaderName);
		break;

	default:
		CHECKF(false, L"Image's primitive type is not designated.")
		break;
	}

	shared_ptr<CDeviceManager> spDeviceManager = CWorld::GetInstance()->GetEngineModule()->GetDeviceManager();
	m_hWnd = spDeviceManager->GetWindowHandle();

	m_wpInputManager = CWorld::GetInstance()->GetEngineModule()->GetInputManager();

	return S_OK;
}

HRESULT Engine::CButton::Initialize()
{
	if (FAILED(CUI::Initialize())) { return E_FAIL; }

	m_tButtonRect =
	{
		static_cast<LONG>(m_vPivot.x),
		static_cast<LONG>(m_vPivot.y),
		static_cast<LONG>(m_vPivot.x + m_fWidth),
		static_cast<LONG>(m_vPivot.y + m_fHeight)
	};

	return S_OK;
}

HRESULT Engine::CButton::PostInitialize()
{
	if (FAILED(CUI::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CButton::BeginPlay()
{
	if (FAILED(CUI::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CButton::PreTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CButton::Tick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	TickButtonState(_fDeltaSeconds);
	return 0;
}

int32 Engine::CButton::PostTick(float _fDeltaSeconds)
{
	if (!m_bActive) { return 0; }

	switch (CUI::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CButton::EndPlay()
{
	if (FAILED(CUI::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CButton::Render()
{
	if (!m_bActive) { return; }

	if (m_eButtonState == EButtonState::INACTIVE) { return; }

	CUI::Render();
}

void Engine::CButton::Release()
{
	m_fnOnButtonUpInDelegate = nullptr;
	m_fnOnButtonUpOutDelegate = nullptr;
	CUI::Release();
}

void Engine::CButton::TickButtonState(float _fDeltaSeconds)
{
	if (m_eButtonState == EButtonState::INACTIVE) { return; }

	if (m_eButtonState == EButtonState::DISABLE) { return; }

	if (m_eButtonMouseState == EButtonMouseState::PRESS_OUT)
	{
		if (IsMouseInButton())
		{
			SetButtonMouseState(EButtonMouseState::PRESS_IN);
			return;
		}

		if (m_wpInputManager.lock()->IsMouseUp(EMouseActionType::LEFT_BUTTON))
		{
			SetButtonMouseState(EButtonMouseState::UP_OUT);
			if (m_fnOnButtonUpOutDelegate) { m_fnOnButtonUpOutDelegate(); }
		}
		return;
	}

	if (m_eButtonMouseState == EButtonMouseState::PRESS_IN)
	{
		if (!IsMouseInButton())
		{
			SetButtonMouseState(EButtonMouseState::PRESS_OUT);
		}
	}

	if (m_eButtonMouseState == EButtonMouseState::UP_IN)
	{
		m_fSumDeltaSeconds += _fDeltaSeconds;
		if (m_fSumDeltaSeconds >= 0.1f)
		{
			m_fSumDeltaSeconds = 0.0f;
			SetButtonMouseState(EButtonMouseState::RELEASE);
		}
		return;
	}

	if (IsMouseInButton())
	{
		if (m_wpInputManager.lock()->IsMousePressed(EMouseActionType::LEFT_BUTTON))
		{
			SetButtonMouseState(EButtonMouseState::PRESS_IN);
		}
		else
		{
			if (m_eButtonMouseState == EButtonMouseState::PRESS_IN)
			{
				SetButtonMouseState(EButtonMouseState::UP_IN);
				if (m_fnOnButtonUpInDelegate) { m_fnOnButtonUpInDelegate(); }
			}
			else
			{
				SetButtonMouseState(EButtonMouseState::HOVER);
			}
		}
	}
	else if (m_eButtonMouseState == EButtonMouseState::PRESS_OUT)
	{
		return;
	}
	else
	{
		SetButtonMouseState(EButtonMouseState::RELEASE);
	}
}

void Engine::CButton::SetTextureIndex(uint32 _iTextureIndex)
{
	m_wpButtonComponent.lock()->SetTextureIndex(_iTextureIndex);
}

void Engine::CButton::OnButtonUpIn()
{
}

void Engine::CButton::OnButtonUpOut()
{
}

bool Engine::CButton::IsMouseInButton()
{
	// 마우스 스크린 좌표를 구합니다.
	::GetCursorPos(&m_tMousePosition);
	::ScreenToClient(m_hWnd, &m_tMousePosition);

	return PtInRect(&m_tButtonRect, m_tMousePosition);
}
