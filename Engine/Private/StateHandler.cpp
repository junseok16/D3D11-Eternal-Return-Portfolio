#include "pch.h"
#include "StateHandler.h"

#include "DeviceManager.h"
#include "StateLoader.h"

IMPLEMENT_SINGLETON(CStateHandler)

HRESULT Engine::CStateHandler::Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager)
{
	m_wpDeviceManager = _spDeviceManager;
	m_spStateLoader = CStateLoader::Create();
	return S_OK;
}

void Engine::CStateHandler::Release()
{
	for (auto& pair : m_umapRasterizerStates) { pair.second = nullptr; }
	m_umapRasterizerStates.clear();

	for (auto& pair : m_umapDepthStencilStates) { pair.second = nullptr; }
	m_umapDepthStencilStates.clear();

	for (auto& pair : m_umapSamplerStates) { pair.second = nullptr; }
	m_umapSamplerStates.clear();
	
	m_spStateLoader->Release();
	m_spStateLoader = nullptr;

	m_spInstance.reset();
}

HRESULT Engine::CStateHandler::CreateRasterizerState(const std::wstring& _wstrRasterizerStateName, const D3D11_RASTERIZER_DESC* _pRasterizerDesc)
{
	if (m_umapRasterizerStates.find(_wstrRasterizerStateName) != m_umapRasterizerStates.end()) { return E_FAIL; }

	ComPtr<ID3D11RasterizerState> cpRasterizerState = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateRasterizerState(_pRasterizerDesc, cpRasterizerState.GetAddressOf()));
	m_umapRasterizerStates.insert({ _wstrRasterizerStateName, cpRasterizerState });
	return S_OK;
}

HRESULT Engine::CStateHandler::CreateDepthStencilState(const std::wstring& _wstrDepthStencilStateName, const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc)
{
	if (m_umapDepthStencilStates.find(_wstrDepthStencilStateName) != m_umapDepthStencilStates.end()) { return E_FAIL; }

	ComPtr<ID3D11DepthStencilState> cpDepthStencilState = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateDepthStencilState(_pDepthStencilDesc, cpDepthStencilState.GetAddressOf()));
	m_umapDepthStencilStates.insert({ _wstrDepthStencilStateName, cpDepthStencilState });
	return S_OK;
}

HRESULT Engine::CStateHandler::CreateSamplerState(const std::wstring& _wstrSamplerStateName, const D3D11_SAMPLER_DESC* _pSamplerDesc)
{
	if (m_umapSamplerStates.find(_wstrSamplerStateName) != m_umapSamplerStates.end()) { return E_FAIL; }

	ComPtr<ID3D11SamplerState> cpSamplerState = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateSamplerState(_pSamplerDesc, cpSamplerState.GetAddressOf()));
	m_umapSamplerStates.insert({ _wstrSamplerStateName, cpSamplerState });
	return S_OK;
}

HRESULT Engine::CStateHandler::CreateBlendState(const std::wstring& _wstrBlendStateName, const D3D11_BLEND_DESC* _pBlendDesc)
{
	if (m_umapBlendStates.find(_wstrBlendStateName) != m_umapBlendStates.end()) { return E_FAIL; }

	ComPtr<ID3D11BlendState> cpBlendState = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBlendState(_pBlendDesc, cpBlendState.GetAddressOf()));
	m_umapBlendStates.insert({ _wstrBlendStateName, cpBlendState });
	return S_OK;
}

ComPtr<ID3D11RasterizerState> Engine::CStateHandler::CreateRasterizerState(const D3D11_RASTERIZER_DESC* _pRasterizerDesc)
{
	ComPtr<ID3D11RasterizerState> cpRasterizerState = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateRasterizerState(_pRasterizerDesc, cpRasterizerState.GetAddressOf()));
	return cpRasterizerState;
}

ComPtr<ID3D11DepthStencilState> Engine::CStateHandler:: CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc)
{
	ComPtr<ID3D11DepthStencilState> cpDepthStencilState = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateDepthStencilState(_pDepthStencilDesc, cpDepthStencilState.GetAddressOf()));
	return cpDepthStencilState;
}

ComPtr<ID3D11SamplerState> Engine::CStateHandler::CreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc)
{
	ComPtr<ID3D11SamplerState> cpSamplerState = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateSamplerState(_pSamplerDesc, cpSamplerState.GetAddressOf()));
	return cpSamplerState;
}

ComPtr<ID3D11BlendState> Engine::CStateHandler::CreateBlendState(const D3D11_BLEND_DESC* _pBlendDesc)
{
	ComPtr<ID3D11BlendState> cpBlendState = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBlendState(_pBlendDesc, cpBlendState.GetAddressOf()));
	return cpBlendState;
}

ComPtr<ID3D11RasterizerState> Engine::CStateHandler::FindRasterizerState(const std::wstring& _wstrRasterizerStateName)
{
	if (m_umapRasterizerStates.find(_wstrRasterizerStateName) == m_umapRasterizerStates.end()) { return nullptr; }

	return m_umapRasterizerStates[_wstrRasterizerStateName];
}

ComPtr<ID3D11DepthStencilState> Engine::CStateHandler::FindDepthStencilState(const std::wstring& _wstrDepthStencilStateName)
{
	if (m_umapDepthStencilStates.find(_wstrDepthStencilStateName) == m_umapDepthStencilStates.end()) { return nullptr; }

	return m_umapDepthStencilStates[_wstrDepthStencilStateName];
}

ComPtr<ID3D11SamplerState> Engine::CStateHandler::FindSamplerState(const std::wstring& _wstrSamplerStateName)
{
	if (m_umapSamplerStates.find(_wstrSamplerStateName) == m_umapSamplerStates.end()) { return nullptr; }

	return m_umapSamplerStates[_wstrSamplerStateName];
}

ComPtr<ID3D11BlendState> Engine::CStateHandler::FindBlendState(const std::wstring& _wstrBlendStateName)
{
	if (m_umapBlendStates.find(_wstrBlendStateName) == m_umapBlendStates.end()) { return nullptr; }

	return m_umapBlendStates[_wstrBlendStateName];
}

void Engine::CStateHandler::OMSetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState, UINT _iStencilRef)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->OMSetDepthStencilState(_pDepthStencilState, _iStencilRef);
}

void Engine::CStateHandler::OMSetBlendState(ID3D11BlendState* _pBlendState, const FLOAT* _pBlendFactor, UINT _iSampleMask)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->OMSetBlendState(_pBlendState, _pBlendFactor, _iSampleMask);
}

void Engine::CStateHandler::RSSetState(ID3D11RasterizerState* _pRasterizerState)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->RSSetState(_pRasterizerState);
}

void Engine::CStateHandler::VSSetSamplers(UINT _iStartSlot, UINT _iNumSamplers, ID3D11SamplerState* const* _ppSamplers)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->VSSetSamplers(_iStartSlot, _iNumSamplers, _ppSamplers);
}

void Engine::CStateHandler::PSSetSamplers(UINT _iStartSlot, UINT _iNumSamplers, ID3D11SamplerState* const* _ppSamplers)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->PSSetSamplers(_iStartSlot, _iNumSamplers, _ppSamplers);
}

void Engine::CStateHandler::GSSetSamplers(UINT _iStartSlot, UINT _iNumSamplers, ID3D11SamplerState* const* _ppSamplers)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->GSSetSamplers(_iStartSlot, _iNumSamplers, _ppSamplers);
}
