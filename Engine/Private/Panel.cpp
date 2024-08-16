#include "pch.h"
#include "Panel.h"

#include "UI.h"

HRESULT Engine::CPanel::PreInitialize()
{
	if (FAILED(CActor::PreInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CPanel::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CPanel::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CPanel::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CPanel::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CPanel::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CPanel::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CPanel::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CPanel::Render()
{
	CActor::Render();
}

void Engine::CPanel::Release()
{
	CActor::Release();
}

void Engine::CPanel::SetActive(bool _bActive)
{
	m_bActive = _bActive;

	for (auto& wpUI : m_umapUIs)
	{
		wpUI.second.lock()->SetActive(_bActive);
	}
}

HRESULT Engine::CPanel::AddUI(const std::wstring& _wstrUIName, const std::shared_ptr<CUI>& _spUI)
{
	if (m_umapUIs.find(_wstrUIName) != m_umapUIs.end()) { return E_FAIL; }
	
	m_umapUIs.insert({ _wstrUIName, _spUI });
	return S_OK;
}

HRESULT Engine::CPanel::RemoveUI(const std::wstring& _wstrUIName)
{
	if (m_umapUIs.find(_wstrUIName) == m_umapUIs.end()) { return E_FAIL; }

	m_umapUIs.erase(_wstrUIName);
	return S_OK;
}
