#include "pch.h"
#include "Blend.h"

#include "StateHandler.h"

std::shared_ptr<CBlend> Engine::CBlend::Create(const std::wstring& _wstrBlendName)
{
	const shared_ptr<CBlend> spBlend = make_shared<CBlend>();
	ENSUREF(spBlend->Initialize(_wstrBlendName), L"Failed to initialize blend.");
	return spBlend;
}

HRESULT Engine::CBlend::Initialize(const std::wstring& _wstrBlendName)
{
	m_wpStateHandler = CStateHandler::GetInstance();
	CHECK(!m_wpStateHandler.expired());

	ComPtr<ID3D11BlendState> cpBlendState = m_wpStateHandler.lock()->FindBlendState(_wstrBlendName);
	if (!cpBlendState) { return E_FAIL; }

	m_cpBlendState = cpBlendState;
	m_wstrBlendName = _wstrBlendName;
	return S_OK;
}

void Engine::CBlend::Release()
{
	if (m_cpBlendState)
	{
		m_cpBlendState = nullptr;
	}
}

void Engine::CBlend::OMSetBlendState()
{
	float fBlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT iSampleMask = 0xffff'ffff;

	m_wpStateHandler.lock()->OMSetBlendState(m_cpBlendState.Get(), fBlendFactor, iSampleMask);
}
