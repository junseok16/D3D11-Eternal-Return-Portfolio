#include "pch.h"
#include "DepthStencil.h"

#include "StateHandler.h"

std::shared_ptr<CDepthStencil> Engine::CDepthStencil::Create(const std::wstring& _wstrDepthStencilName)
{
	const shared_ptr<CDepthStencil> spDepthStencil = make_shared<CDepthStencil>();
	ENSUREF(spDepthStencil->Initialize(_wstrDepthStencilName), L"Failed to initialize depth stencil.");
	return spDepthStencil;
}

HRESULT Engine::CDepthStencil::Initialize(const std::wstring& _wstrDepthStencilName)
{
	m_wpStateHandler = CStateHandler::GetInstance();
	CHECK(!m_wpStateHandler.expired());

	ComPtr<ID3D11DepthStencilState> cpDepthStencilState = m_wpStateHandler.lock()->FindDepthStencilState(_wstrDepthStencilName);
	if (!cpDepthStencilState) { return E_FAIL; }

	m_cpDepthStencilState = cpDepthStencilState;
	m_wstrDepthStencilName = _wstrDepthStencilName;
	return S_OK;
}

void Engine::CDepthStencil::Release()
{
	if (m_cpDepthStencilState)
	{
		m_cpDepthStencilState = nullptr;
	}
}

void Engine::CDepthStencil::OMSetDepthStencilState()
{
	if (!m_cpDepthStencilState) { return; }
	m_wpStateHandler.lock()->OMSetDepthStencilState(m_cpDepthStencilState.Get(), 0);
}
