#include "pch.h"
#include "EffectHandler.h"

#include "DeviceManager.h"
#include "EffectLoader.h"

IMPLEMENT_SINGLETON(CEffectHandler);

HRESULT Engine::CEffectHandler::Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager)
{
	m_wpDeviceManager = _spDeviceManager;
	m_spEffectLoader = CEffectLoader::Create();
	return S_OK;
}

void Engine::CEffectHandler::Release()
{
	for (auto& pair : m_umapVertexBuffers) { pair.second = nullptr; }
	m_umapVertexBuffers.clear();

	for (auto& pair : m_umapIndexBuffers) { pair.second = nullptr; }
	m_umapIndexBuffers.clear();

	for (auto& pair : m_umapMaskShaderResourceViews) { pair.second = nullptr; }
	m_umapMaskShaderResourceViews.clear();

	for (auto& pair : m_umapNoiseShaderResourceViews) { pair.second = nullptr; }
	m_umapNoiseShaderResourceViews.clear();

	for (auto& pair : m_umapMeshEffectDataGroup) { pair.second = nullptr; }
	m_umapMeshEffectDataGroup.clear();

	m_spEffectLoader->Release();
	m_spEffectLoader = nullptr;

	m_spInstance.reset();
}

HRESULT Engine::CEffectHandler::AddVertexBuffer(const std::wstring& _wstrVertexBufferName, const ComPtr<ID3D11Buffer>& _spVertexBuffer)
{
	if (m_umapVertexBuffers.find(_wstrVertexBufferName) != m_umapVertexBuffers.end()) { return E_FAIL; }

	m_umapVertexBuffers.insert({ _wstrVertexBufferName, _spVertexBuffer });
	return S_OK;
}

HRESULT Engine::CEffectHandler::AddIndexBuffer(const std::wstring& _wstrIndexBufferName, const ComPtr<ID3D11Buffer>& _spIndexBuffer)
{
	if (m_umapIndexBuffers.find(_wstrIndexBufferName) != m_umapIndexBuffers.end()) { return E_FAIL; }

	m_umapIndexBuffers.insert({ _wstrIndexBufferName, _spIndexBuffer });
	return S_OK;
}

HRESULT Engine::CEffectHandler::AddMaskShaderResourceView(const std::wstring& _wstrShaderResourceViewName, const ComPtr<ID3D11ShaderResourceView>& _cpShaderResouceView)
{
	if (m_umapMaskShaderResourceViews.find(_wstrShaderResourceViewName) != m_umapMaskShaderResourceViews.end()) { return E_FAIL; }

	m_umapMaskShaderResourceViews.insert({ _wstrShaderResourceViewName, _cpShaderResouceView });
	return S_OK;
}

HRESULT Engine::CEffectHandler::AddNoiseShaderResourceView(const std::wstring& _wstrShaderResourceViewName, const ComPtr<ID3D11ShaderResourceView>& _cpShaderResouceView)
{
	if (m_umapNoiseShaderResourceViews.find(_wstrShaderResourceViewName) != m_umapNoiseShaderResourceViews.end()) { return E_FAIL; }

	m_umapNoiseShaderResourceViews.insert({ _wstrShaderResourceViewName, _cpShaderResouceView });
	return S_OK;
}

HRESULT Engine::CEffectHandler::AddModelDesc(const std::wstring& _wstrModelDescName, const std::shared_ptr<FModelDesc>& _spModelDesc)
{
	if (m_umapEffectModelDescs.find(_wstrModelDescName) != m_umapEffectModelDescs.end()) { return E_FAIL; }

	m_umapEffectModelDescs.insert({ _wstrModelDescName, _spModelDesc });
	return S_OK;
}

HRESULT Engine::CEffectHandler::AddEffectMeshDataGroup(const std::wstring& _wstrMeshEffectDataGroupName, const std::shared_ptr<FMeshEffectDataGroupProperty>& _spMeshEffectGroupProperty)
{
	if (m_umapMeshEffectDataGroup.find(_wstrMeshEffectDataGroupName) != m_umapMeshEffectDataGroup.end()) { return E_FAIL; }

	m_umapMeshEffectDataGroup.insert({ _wstrMeshEffectDataGroupName, _spMeshEffectGroupProperty });
	return S_OK;
}

ComPtr<ID3D11Buffer> Engine::CEffectHandler::FindVertexBuffer(const std::wstring& _wstrVertexBufferName)
{
	if (m_umapVertexBuffers.find(_wstrVertexBufferName) == m_umapVertexBuffers.end()) { return nullptr; }

	return m_umapVertexBuffers[_wstrVertexBufferName];
}

ComPtr<ID3D11Buffer> Engine::CEffectHandler::FindIndexBuffer(const std::wstring& _wstrIndexBufferName)
{
	if (m_umapIndexBuffers.find(_wstrIndexBufferName) == m_umapIndexBuffers.end()) { return nullptr; }

	return m_umapIndexBuffers[_wstrIndexBufferName];
}

ComPtr<ID3D11ShaderResourceView> Engine::CEffectHandler::FindMaskShaderResourceView(const std::wstring& _wstrShaderResourceViewName)
{
	if (m_umapMaskShaderResourceViews.find(_wstrShaderResourceViewName) == m_umapMaskShaderResourceViews.end()) { return nullptr; }

	return m_umapMaskShaderResourceViews[_wstrShaderResourceViewName];
}

ComPtr<ID3D11ShaderResourceView> Engine::CEffectHandler::FindNoiseShaderResourceView(const std::wstring& _wstrShaderResourceViewName)
{
	if (m_umapNoiseShaderResourceViews.find(_wstrShaderResourceViewName) == m_umapNoiseShaderResourceViews.end()) { return nullptr; }

	return m_umapNoiseShaderResourceViews[_wstrShaderResourceViewName];
}

std::shared_ptr<FModelDesc> Engine::CEffectHandler::FindModelDesc(const std::wstring& _wstrModelDescName)
{
	if (m_umapEffectModelDescs.find(_wstrModelDescName) == m_umapEffectModelDescs.end()) { return nullptr; }

	return m_umapEffectModelDescs[_wstrModelDescName];
}

std::shared_ptr<FMeshEffectDataGroupProperty> Engine::CEffectHandler::FindEffectMeshDataGroup(const std::wstring& _wstrMeshEffectDataGroupName)
{
	if (m_umapMeshEffectDataGroup.find(_wstrMeshEffectDataGroupName) == m_umapMeshEffectDataGroup.end()) { return nullptr; }

	return m_umapMeshEffectDataGroup[_wstrMeshEffectDataGroupName];
}

void Engine::CEffectHandler::IASetVertexBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetVertexBuffers(_iStartSlot, _iNumBuffers, _ppVertexBuffers, _pStrides, _pOffsets);
}

void Engine::CEffectHandler::IASetIndexBuffer(ID3D11Buffer* _pIndexBuffer, DXGI_FORMAT _tFormat, UINT _iOffset)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetIndexBuffer(_pIndexBuffer, _tFormat, _iOffset);
}

void Engine::CEffectHandler::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _tPrimitiveTopology)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetPrimitiveTopology(_tPrimitiveTopology);
}

void Engine::CEffectHandler::DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, UINT _iBaseVertexLocation)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->DrawIndexed(_iIndexCount, _iStartIndexLocation, _iBaseVertexLocation);
}

void Engine::CEffectHandler::VSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->VSSetShaderResources(_iStartSlot, _iNumViews, _ppShaderResourceViews);
}

void Engine::CEffectHandler::PSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->PSSetShaderResources(_iStartSlot, _iNumViews, _ppShaderResourceViews);
}

int32 Engine::CEffectHandler::GetNumVertice(EModelType _eModelType, const std::wstring& _wstrVertexBufferName) const
{
	return m_spEffectLoader->GetNumVertices(_eModelType, _wstrVertexBufferName);
}

int32 Engine::CEffectHandler::GetNumIndices(const std::wstring& _wstrIndexBufferName) const
{
	return m_spEffectLoader->GetNumIndices(_wstrIndexBufferName);
}
