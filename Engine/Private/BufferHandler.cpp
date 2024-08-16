#include "pch.h"
#include "BufferHandler.h"

#include "DeviceManager.h"
#include "BufferLoader.h"

IMPLEMENT_SINGLETON(CBufferHandler)

HRESULT Engine::CBufferHandler::Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager)
{
	m_wpDeviceManager = _spDeviceManager;
	m_spBufferLoader = CBufferLoader::Create();
	return S_OK;
}

void Engine::CBufferHandler::Release()
{
	for (auto& pair : m_umapVertexBuffers) { pair.second = nullptr; }
	m_umapVertexBuffers.clear();

	for (auto& pair : m_umapIndexBuffers) { pair.second = nullptr; }
	m_umapIndexBuffers.clear();

	for (auto& pair : m_umapInstanceTranformBuffers) { pair.second = nullptr; }
	m_umapInstanceTranformBuffers.clear();

	m_spBufferLoader->Release();
	m_spBufferLoader = nullptr;

	m_spInstance.reset();
}

void Engine::CBufferHandler::AddVertexBuffer(const std::wstring& _wstrVertexBufferName, const ComPtr<ID3D11Buffer>& _cpVertexBuffer)
{
	if (m_umapVertexBuffers.find(_wstrVertexBufferName) != m_umapVertexBuffers.end()) { return; }

	m_umapVertexBuffers.insert({ _wstrVertexBufferName, _cpVertexBuffer });
}

void Engine::CBufferHandler::AddIndexBuffer(const std::wstring& _wstrIndexBufferName, const ComPtr<ID3D11Buffer>& _cpIndexBuffer)
{
	if (m_umapIndexBuffers.find(_wstrIndexBufferName) != m_umapIndexBuffers.end()) { return; }

	m_umapIndexBuffers.insert({ _wstrIndexBufferName, _cpIndexBuffer });
}

ComPtr<ID3D11Buffer> Engine::CBufferHandler::FindVertexBuffer(const std::wstring& _wstrVertexBufferName)
{
	if (m_umapVertexBuffers.find(_wstrVertexBufferName) == m_umapVertexBuffers.end()) { return nullptr; }

	return m_umapVertexBuffers[_wstrVertexBufferName];
}

ComPtr<ID3D11Buffer> Engine::CBufferHandler::FindIndexBuffer(const std::wstring& _wstrIndexBufferName)
{
	if (m_umapIndexBuffers.find(_wstrIndexBufferName) == m_umapIndexBuffers.end()) { return nullptr; }

	return m_umapIndexBuffers[_wstrIndexBufferName];
}

void Engine::CBufferHandler::AddInstanceVertexBuffer(const std::wstring& _wstrInstanceVertexBufferName, const ComPtr<ID3D11Buffer>& _cpVertexBuffer)
{
	if (m_umapInstanceVertexBuffers.find(_wstrInstanceVertexBufferName) != m_umapInstanceVertexBuffers.end()) { return; }

	m_umapInstanceVertexBuffers.insert({ _wstrInstanceVertexBufferName, _cpVertexBuffer });
}

void Engine::CBufferHandler::AddInstanceIndexBuffer(const std::wstring& _wstrInstanceIndexBufferName, const ComPtr<ID3D11Buffer>& _cpIndexBuffer)
{
	if (m_umapInstanceIndexBuffers.find(_wstrInstanceIndexBufferName) != m_umapInstanceIndexBuffers.end()) { CHECK(false); return; }

	m_umapInstanceIndexBuffers.insert({ _wstrInstanceIndexBufferName, _cpIndexBuffer });
}

void Engine::CBufferHandler::AddInstanceTransformBuffer(const std::wstring& _wstrInstanceTransformBufferName, const ComPtr<ID3D11Buffer>& _cpTransformBuffer)
{
	if (m_umapInstanceTranformBuffers.find(_wstrInstanceTransformBufferName) != m_umapInstanceTranformBuffers.end()) { CHECK(false); return; }

	m_umapInstanceTranformBuffers.insert({ _wstrInstanceTransformBufferName, _cpTransformBuffer });
}

ComPtr<ID3D11Buffer> Engine::CBufferHandler::FindInstanceVertexBuffer(const std::wstring& _wstrInstanceVertexBufferName)
{
	if (m_umapInstanceVertexBuffers.find(_wstrInstanceVertexBufferName) == m_umapInstanceVertexBuffers.end()) { return nullptr; }

	return m_umapInstanceVertexBuffers[_wstrInstanceVertexBufferName];
}

ComPtr<ID3D11Buffer> Engine::CBufferHandler::FindInstanceIndexBuffer(const std::wstring& _wstrInstanceIndexBufferName)
{
	if (m_umapInstanceIndexBuffers.find(_wstrInstanceIndexBufferName) == m_umapInstanceIndexBuffers.end()) { return nullptr; }

	return m_umapInstanceIndexBuffers[_wstrInstanceIndexBufferName];
}

ComPtr<ID3D11Buffer> Engine::CBufferHandler::FindInstanceTransformBuffer(const std::wstring& _wstrInstanceTransformBufferName)
{
	if (m_umapInstanceTranformBuffers.find(_wstrInstanceTransformBufferName) == m_umapInstanceTranformBuffers.end()) { return nullptr; }

	return m_umapInstanceTranformBuffers[_wstrInstanceTransformBufferName];
}

void Engine::CBufferHandler::IASetVertexBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetVertexBuffers(_iStartSlot, _iNumBuffers, _ppVertexBuffers, _pStrides, _pOffsets);
}

void Engine::CBufferHandler::IASetIndexBuffer(ID3D11Buffer* _pIndexBuffer, DXGI_FORMAT _tFormat, UINT _iOffset)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetIndexBuffer(_pIndexBuffer, _tFormat, _iOffset);
}

void Engine::CBufferHandler::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _tPrimitiveTopology)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetPrimitiveTopology(_tPrimitiveTopology);
}

void Engine::CBufferHandler::DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, UINT _iBaseVertexLocation)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->DrawIndexed(_iIndexCount, _iStartIndexLocation, _iBaseVertexLocation);
}

void Engine::CBufferHandler::Draw(UINT _iVertexCount, UINT _iStartVertexLocation)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->Draw(_iVertexCount, _iStartVertexLocation);
}

void Engine::CBufferHandler::DrawIndexedInstanced(UINT _iIndexCountPerInstance, UINT _iInstanceCount, UINT _iStartIndexLocation, UINT _iBaseVertexLocation, UINT _iStartInstanceLocation)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->DrawIndexedInstanced(_iIndexCountPerInstance, _iInstanceCount, _iStartIndexLocation, _iBaseVertexLocation, _iStartInstanceLocation);
}

HRESULT Engine::CBufferHandler::LoadInstanceIndex(const std::wstring& _wstrInstanceIndexDataName, int32 _iNumInstances)
{
	return m_spBufferLoader->LoadInstanceIndex(_wstrInstanceIndexDataName, _iNumInstances);
}

HRESULT Engine::CBufferHandler::CreateInstanceIndexBuffer(const std::wstring& _wstrInstanceIndexDataName)
{
	return m_spBufferLoader->CreateInstanceIndexBuffer(_wstrInstanceIndexDataName);
}

HRESULT Engine::CBufferHandler::LoadInstanceTransform(const std::wstring& _wstrInstanceTransformDataName, int32 _iNumInstances)
{
	return m_spBufferLoader->LoadInstanceTransform(_wstrInstanceTransformDataName, _iNumInstances);
}

HRESULT Engine::CBufferHandler::CreateInstanceTransformBuffer(const std::wstring& _wstrInstanceTransformDataName)
{
	return m_spBufferLoader->CreateInstanceTransformBuffer(_wstrInstanceTransformDataName);
}
