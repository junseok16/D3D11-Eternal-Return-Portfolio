#include "pch.h"
#include "Sampler.h"

#include "StateHandler.h"

std::shared_ptr<CSampler> Engine::CSampler::Create(const std::wstring& _wstrSamplerName, uint8 _iBindPoint)
{
	const shared_ptr<CSampler> spSampler = make_shared<CSampler>();
	ENSUREF(spSampler->Initialize(_wstrSamplerName, _iBindPoint), L"Failed to initialize Sampler.");
	return spSampler;
}

HRESULT Engine::CSampler::Initialize(const std::wstring& _wstrSamplerName, uint8 _iBindPoint)
{
	m_wpStateHandler = CStateHandler::GetInstance();
	CHECK(!m_wpStateHandler.expired());

	ComPtr<ID3D11SamplerState> cpSamplerState = m_wpStateHandler.lock()->FindSamplerState(_wstrSamplerName);
	if (!cpSamplerState) { return E_FAIL; }

	m_iBindPoint = _iBindPoint;
	m_cpSamplerState = cpSamplerState;
	m_wstrSamplerName = _wstrSamplerName;
	return S_OK;
}

void Engine::CSampler::Release()
{
	if (m_cpSamplerState)
	{
		m_cpSamplerState = nullptr;
	}
}

void Engine::CSampler::PSSetSamplers()
{
	if (!m_cpSamplerState || m_iBindPoint < 0) { return; }
	m_wpStateHandler.lock()->PSSetSamplers(m_iBindPoint, 1, m_cpSamplerState.GetAddressOf());
}

void Engine::CSampler::VSSetSamplers()
{
	if (!m_cpSamplerState || m_iBindPoint < 0) { return; }
	m_wpStateHandler.lock()->VSSetSamplers(m_iBindPoint, 1, m_cpSamplerState.GetAddressOf());
}

void Engine::CSampler::GSSetSamplers()
{
	if (!m_cpSamplerState || m_iBindPoint < 0) { return; }
	m_wpStateHandler.lock()->GSSetSamplers(m_iBindPoint, 1, m_cpSamplerState.GetAddressOf());
}
