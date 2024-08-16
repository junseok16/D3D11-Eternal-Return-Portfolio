#include "pch.h"
#include "ViewHandler.h"

#include "DeviceManager.h"
#include "ViewLoader.h"

IMPLEMENT_SINGLETON(CViewHandler)

HRESULT Engine::CViewHandler::Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager)
{
	m_wpDeviceManager = _spDeviceManager;
	m_spViewLoader = CViewLoader::Create();
	return S_OK;
}

void Engine::CViewHandler::Release()
{
	for (auto& pair : m_umapRenderTargetViews) { pair.second = nullptr; }
	m_umapRenderTargetViews.clear();

	for (auto& pair : m_umapDepthStencilViews) { pair.second = nullptr; }
	m_umapDepthStencilViews.clear();

	for (auto& pair : m_umapShaderResourceViews) { pair.second = nullptr; }
	m_umapShaderResourceViews.clear();

	for (auto& pair : m_umapViews)
	{
		pair.second->m_cpRenderTargetView = nullptr;
		pair.second->m_cpShaderResourceView = nullptr;
		pair.second = nullptr;
	}
	m_umapViews.clear();

	m_spViewLoader->Release();
	m_spViewLoader = nullptr;

	m_spInstance.reset();
}

HRESULT Engine::CViewHandler::CreateRenderTargetView(const std::wstring& _wstrRenderTargetViewName, ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pRenderTargetViewDesc)
{
	if (m_umapRenderTargetViews.find(_wstrRenderTargetViewName) != m_umapRenderTargetViews.end()) { return E_FAIL; }

	ComPtr<ID3D11RenderTargetView> cpRenderTargetView = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateRenderTargetView(_pResource, _pRenderTargetViewDesc, cpRenderTargetView.GetAddressOf()));
	m_umapRenderTargetViews.insert({ _wstrRenderTargetViewName, cpRenderTargetView });
	return S_OK;
}

HRESULT Engine::CViewHandler::CreateDepthStencilView(const std::wstring& _wstrDepthStencilViewName, ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDepthStencilViewDesc)
{
	if (m_umapDepthStencilViews.find(_wstrDepthStencilViewName) != m_umapDepthStencilViews.end()) { return E_FAIL; }

	ComPtr<ID3D11DepthStencilView> cpDepthStencilView = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateDepthStencilView(_pResource, _pDepthStencilViewDesc, cpDepthStencilView.GetAddressOf()));
	m_umapDepthStencilViews.insert({ _wstrDepthStencilViewName, cpDepthStencilView });
	return S_OK;
}

HRESULT Engine::CViewHandler::CreateShaderResourceView(const std::wstring& _wstrShaderResourceViewName, ID3D11Resource* _pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* _pShaderResourceViewDesc)
{
	if (m_umapShaderResourceViews.find(_wstrShaderResourceViewName) != m_umapShaderResourceViews.end()) { return E_FAIL; }

	ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateShaderResourceView(_pResource, _pShaderResourceViewDesc, cpShaderResourceView.GetAddressOf()));
	m_umapShaderResourceViews.insert({ _wstrShaderResourceViewName, cpShaderResourceView });
	return S_OK;
}

shared_ptr<TView> Engine::CViewHandler::CreateView(const std::wstring& _wstrViewName)
{
	if (m_umapViews.find(_wstrViewName) != m_umapViews.end()) { return nullptr; }

	ComPtr<ID3D11RenderTargetView> cpRenderTargetView = FindRenderTargetView(_wstrViewName);
	ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = FindShaderResourceView(_wstrViewName);

	CHECKF(cpRenderTargetView != nullptr, L"RTV is nullptr.");
	CHECKF(cpShaderResourceView != nullptr, L"SRV is nullptr.");

	shared_ptr<TView> spView = make_shared<TView>();
	spView->m_cpRenderTargetView = cpRenderTargetView;
	spView->m_cpShaderResourceView = cpShaderResourceView;

	m_umapViews.emplace(_wstrViewName, spView);
	return spView;
}

HRESULT Engine::CViewHandler::CreateViewGroup(const std::wstring& _wstrViewGroupName)
{
	if (m_umapViewGroups.find(_wstrViewGroupName) != m_umapViewGroups.end()) { return E_FAIL; }

	m_umapViewGroups.insert({ _wstrViewGroupName, std::list<std::weak_ptr<TView>>() });
	return S_OK;
}

ComPtr<ID3D11RenderTargetView> Engine::CViewHandler::FindRenderTargetView(const std::wstring& _wstrRenderTargetViewName)
{
	if (m_umapRenderTargetViews.find(_wstrRenderTargetViewName) == m_umapRenderTargetViews.end()) { return nullptr; }

	return m_umapRenderTargetViews[_wstrRenderTargetViewName];
}

ComPtr<ID3D11DepthStencilView> Engine::CViewHandler::FindDepthStencilView(const std::wstring& _wstrDepthStencilViewName)
{
	if (m_umapDepthStencilViews.find(_wstrDepthStencilViewName) == m_umapDepthStencilViews.end()) { return nullptr; }

	return m_umapDepthStencilViews[_wstrDepthStencilViewName];
}

ComPtr<ID3D11ShaderResourceView> Engine::CViewHandler::FindShaderResourceView(const std::wstring& _wstrShaderResourceViewName)
{
	if (m_umapShaderResourceViews.find(_wstrShaderResourceViewName) == m_umapShaderResourceViews.end()) { return nullptr; }

	return m_umapShaderResourceViews[_wstrShaderResourceViewName];
}

shared_ptr<TView> Engine::CViewHandler::FindView(const std::wstring& _wstrViewName)
{
	if (m_umapViews.find(_wstrViewName) == m_umapViews.end()) { return nullptr; }

	return m_umapViews[_wstrViewName];
}

std::list<std::weak_ptr<TView>>* Engine::CViewHandler::FindViewGroup(const std::wstring& _wstrViewGroupName)
{
	if (m_umapViewGroups.find(_wstrViewGroupName) == m_umapViewGroups.end()) { return nullptr; }

	return &m_umapViewGroups[_wstrViewGroupName];
}

HRESULT Engine::CViewHandler::AddShaderResourceView(const std::wstring& _wstrShaderResourceViewName, const ComPtr<ID3D11ShaderResourceView>& _cpShaderResouceView)
{
	if (m_umapShaderResourceViews.find(_wstrShaderResourceViewName) != m_umapShaderResourceViews.end()) { return E_FAIL; }

	m_umapShaderResourceViews.insert({ _wstrShaderResourceViewName, _cpShaderResouceView });
	return S_OK;
}

HRESULT Engine::CViewHandler::AddViewGroup(const std::wstring& _wstrViewGroupName, const std::wstring& _wstrViewName)
{
	if (m_umapViewGroups.find(_wstrViewGroupName) == m_umapViewGroups.end()) { return E_FAIL; }

	std::list<std::weak_ptr<TView>>& lstViews = m_umapViewGroups[_wstrViewGroupName];
	
	shared_ptr<TView> spView = FindView(_wstrViewName);
	if (spView == nullptr) { return E_FAIL; }

	lstViews.push_back(spView);
	return S_OK;
}

void Engine::CViewHandler::ClearRenderTargetView(const std::wstring& _wstrRenderTargetViewName, const FLOAT* _pColorRGBA)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->ClearRenderTargetView(m_umapRenderTargetViews[_wstrRenderTargetViewName].Get(), _pColorRGBA);
}

void Engine::CViewHandler::ClearDepthStencilView(const std::wstring& _wstrDepthStencilViewName, UINT _iClearFlags, FLOAT _fDepth, UINT8 _iStencil)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->ClearDepthStencilView(m_umapDepthStencilViews[_wstrDepthStencilViewName].Get(), _iClearFlags, _fDepth, _iStencil);
}

HRESULT Engine::CViewHandler::BeginViewGroup(const std::wstring& _wstrViewGroupName, const ComPtr<ID3D11DepthStencilView>& _cpDepthStencilView)
{
	std::list<std::weak_ptr<TView>>* lstViewGroup = FindViewGroup(_wstrViewGroupName);
	if (lstViewGroup == nullptr) { return E_FAIL; }

	ComPtr<ID3D11RenderTargetView> cpCurRenderTargetView = nullptr;
	ComPtr<ID3D11DepthStencilView> cpDepthStencilView = nullptr;
	m_wpDeviceManager.lock()->GetDeviceContext()->OMGetRenderTargets(1, cpCurRenderTargetView.GetAddressOf(), cpDepthStencilView.GetAddressOf());

	array<ComPtr<ID3D11RenderTargetView>, 8> arrRenderTargetViews{ nullptr };

	uint32 iNumViews = 0;
	for (auto& wpView : *lstViewGroup)
	{
		wpView.lock()->ClearRenderTargetView(m_wpDeviceManager.lock()->GetDeviceContext());
		arrRenderTargetViews[iNumViews++] = wpView.lock()->m_cpRenderTargetView;
	}

	if (8 <= iNumViews) { CHECKF(false, L"The Number of render target is over 8."); }

	if (_cpDepthStencilView)
	{
		m_wpDeviceManager.lock()->GetDeviceContext()->ClearDepthStencilView(_cpDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		m_wpDeviceManager.lock()->GetDeviceContext()->OMSetRenderTargets(iNumViews, arrRenderTargetViews.data()->GetAddressOf(), _cpDepthStencilView.Get());
	}
	else
	{
		m_wpDeviceManager.lock()->GetDeviceContext()->OMSetRenderTargets(iNumViews, arrRenderTargetViews.data()->GetAddressOf(), cpDepthStencilView.Get());
	}
	
	return S_OK;
}

HRESULT Engine::CViewHandler::EndViewGroup()
{
	ComPtr<ID3D11RenderTargetView> cpRenderTargetView = FindRenderTargetView(L"RTV_BACK_BUFFER");
	ComPtr<ID3D11DepthStencilView> cpDepthStencilView = FindDepthStencilView(L"DSV_BACK_BUFFER");
	CHECK(cpRenderTargetView != nullptr);
	CHECK(cpDepthStencilView != nullptr);

	array<ComPtr<ID3D11RenderTargetView>, 1> arrRenderTargetViews{ cpRenderTargetView };
	OMSetRenderTargets(static_cast<UINT>(arrRenderTargetViews.size()), arrRenderTargetViews.data()->GetAddressOf(), cpDepthStencilView.Get());
	return S_OK;
}

void Engine::CViewHandler::RenderViewGroup(const std::wstring& _wstrViewGroupName)
{
	std::list<std::weak_ptr<TView>>* lstViewGroup = FindViewGroup(_wstrViewGroupName);
	if (lstViewGroup == nullptr) { return; }

	for (auto& wpView : *lstViewGroup)
	{

	}
}

void Engine::CViewHandler::OMSetRenderTargets(UINT _iNumViews, ID3D11RenderTargetView* const* _ppRenderTargetViews, ID3D11DepthStencilView* _pDepthStencilView)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->OMSetRenderTargets(_iNumViews, _ppRenderTargetViews, _pDepthStencilView);
}

void Engine::CViewHandler::VSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->VSSetShaderResources(_iStartSlot, _iNumViews, _ppShaderResourceViews);
}

void Engine::CViewHandler::PSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->PSSetShaderResources(_iStartSlot, _iNumViews, _ppShaderResourceViews);
}

void Engine::CViewHandler::GSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->GSSetShaderResources(_iStartSlot, _iNumViews, _ppShaderResourceViews);
}
