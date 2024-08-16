#include "pch.h"
#include "ShaderHandler.h"

#include "DeviceManager.h"
#include "ShaderLoader.h"

IMPLEMENT_SINGLETON(CShaderHandler)

HRESULT Engine::CShaderHandler::Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager)
{
	m_wpDeviceManager = _spDeviceManager;
	m_spShaderLoader = CShaderLoader::Create();
	return S_OK;
}

void Engine::CShaderHandler::Release()
{
	for (auto& pair : m_umapVertexShaders) { pair.second = nullptr; }
	m_umapVertexShaders.clear();

	for (auto& pair : m_umapGeometryShaders) { pair.second = nullptr; }
	m_umapGeometryShaders.clear();

	for (auto& pair : m_umapPixelShaders) { pair.second = nullptr; }
	m_umapPixelShaders.clear();

	for (auto& pair : m_umapConstantBuffers) { pair.second = nullptr; }
	m_umapConstantBuffers.clear();

	for (auto& pair : m_umapInputLayouts) { pair.second = nullptr; }
	m_umapInputLayouts.clear();

	m_spPrimitiveBatch = nullptr;
	m_spBasicEffect = nullptr;

	m_spShaderLoader->Release();
	m_spShaderLoader = nullptr;

	m_spInstance.reset();
}

ComPtr<ID3D11VertexShader> Engine::CShaderHandler::FindVertexShader(const std::wstring& _wstrVertexShaderName)
{
	if (m_umapVertexShaders.find(_wstrVertexShaderName) == m_umapVertexShaders.end()) { return nullptr; }

	return m_umapVertexShaders[_wstrVertexShaderName];
}

ComPtr<ID3D11GeometryShader> Engine::CShaderHandler::FindGeometryShader(const std::wstring& _wstrGeometryShaderName)
{
	if (m_umapGeometryShaders.find(_wstrGeometryShaderName) == m_umapGeometryShaders.end()) { return nullptr; }

	return m_umapGeometryShaders[_wstrGeometryShaderName];
}

ComPtr<ID3D11PixelShader> Engine::CShaderHandler::FindPixelShader(const std::wstring& _wstrPixelShaderName)
{
	if (m_umapPixelShaders.find(_wstrPixelShaderName) == m_umapPixelShaders.end()) { return nullptr; }

	return m_umapPixelShaders[_wstrPixelShaderName];
}

ComPtr<ID3D11InputLayout> Engine::CShaderHandler::FindInputLayout(const std::wstring& _wstrInputLayoutName)
{
	if (m_umapInputLayouts.find(_wstrInputLayoutName) == m_umapInputLayouts.end()) { return nullptr; }

	return m_umapInputLayouts[_wstrInputLayoutName];
}

ComPtr<ID3D11Buffer> Engine::CShaderHandler::FindConstantBuffer(const std::wstring& _wstrConstantBufferName)
{
	if (m_umapConstantBuffers.find(_wstrConstantBufferName) == m_umapConstantBuffers.end()) { return nullptr; }

	return m_umapConstantBuffers[_wstrConstantBufferName];
}

HRESULT Engine::CShaderHandler::AddVertexShader(const std::wstring& _wstrVertexShaderName, const ComPtr<ID3D11VertexShader>& _cpVertexShader)
{
	if (m_umapVertexShaders.find(_wstrVertexShaderName) != m_umapVertexShaders.end()) { return E_FAIL; }

	m_umapVertexShaders.insert({ _wstrVertexShaderName, _cpVertexShader });
	return S_OK;
}

HRESULT Engine::CShaderHandler::AddGeometryShader(const std::wstring& _wstrGeometryShaderName, const ComPtr<ID3D11GeometryShader>& _cpGeometryShader)
{
	if (m_umapGeometryShaders.find(_wstrGeometryShaderName) != m_umapGeometryShaders.end()) { return E_FAIL; }

	m_umapGeometryShaders.insert({ _wstrGeometryShaderName, _cpGeometryShader });
	return S_OK;
}

HRESULT Engine::CShaderHandler::AddPixelShader(const std::wstring& _wstrPixelShaderName, const ComPtr<ID3D11PixelShader>& _cpPixelShader)
{
	if (m_umapPixelShaders.find(_wstrPixelShaderName) != m_umapPixelShaders.end()) { return E_FAIL; }

	m_umapPixelShaders.insert({ _wstrPixelShaderName, _cpPixelShader });
	return S_OK;
}

HRESULT Engine::CShaderHandler::AddInputLayout(const std::wstring& _wstrInputLayoutName, const ComPtr<ID3D11InputLayout>& _cpInputLayout)
{
	if (m_umapInputLayouts.find(_wstrInputLayoutName) != m_umapInputLayouts.end()) { return E_FAIL; }

	m_umapInputLayouts.insert({ _wstrInputLayoutName, _cpInputLayout });
	return S_OK;
}

HRESULT Engine::CShaderHandler::AddConstantBuffer(const std::wstring& _wstrConstantBufferName, const ComPtr<ID3D11Buffer>& _cpConstantBuffer)
{
	if (m_umapConstantBuffers.find(_wstrConstantBufferName) != m_umapConstantBuffers.end()) { return E_FAIL; }

	m_umapConstantBuffers.insert({ _wstrConstantBufferName, _cpConstantBuffer });
	return S_OK;
}

void Engine::CShaderHandler::VSSetShader(ID3D11VertexShader* _pVertexShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _iNumClassInstances)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->VSSetShader(_pVertexShader, _ppClassInstances, _iNumClassInstances);
}

void Engine::CShaderHandler::GSSetShader(ID3D11GeometryShader* _pGeometryShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _iNumClassInstances)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->GSSetShader(_pGeometryShader, _ppClassInstances, _iNumClassInstances);
}

void Engine::CShaderHandler::PSSetShader(ID3D11PixelShader* _pPixelShader, ID3D11ClassInstance* const* _ppClassInstances, UINT _iNumClassInstances)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->PSSetShader(_pPixelShader, _ppClassInstances, _iNumClassInstances);
}

void Engine::CShaderHandler::IASetInputLayout(ID3D11InputLayout* _pInputLayout)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetInputLayout(_pInputLayout);
}

void Engine::CShaderHandler::VSSetConstantBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppConstantBuffers)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->VSSetConstantBuffers(_iStartSlot, _iNumBuffers, _ppConstantBuffers);
}

void Engine::CShaderHandler::GSSetConstantBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppConstantBuffers)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->GSSetConstantBuffers(_iStartSlot, _iNumBuffers, _ppConstantBuffers);
}

void Engine::CShaderHandler::PSSetConstantBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppConstantBuffers)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->PSSetConstantBuffers(_iStartSlot, _iNumBuffers, _ppConstantBuffers);
}

HRESULT Engine::CShaderHandler::AddVertexShaderDesc(const std::wstring& _wstrVertexShaderName, std::shared_ptr<FVertexShaderDesc> _spVertexShaderDesc)
{
	if (m_umapVertexShaderDescs.find(_wstrVertexShaderName) != m_umapVertexShaderDescs.end()) { return E_FAIL; }

	m_umapVertexShaderDescs.insert({ _wstrVertexShaderName, _spVertexShaderDesc });
	return S_OK;
}

HRESULT Engine::CShaderHandler::AddGeometryShaderDesc(const std::wstring& _wstrGeometryShaderName, std::shared_ptr<FGeometryShaderDesc> _spGeometryShaderDesc)
{
	if (m_umapGeometryShaderDescs.find(_wstrGeometryShaderName) != m_umapGeometryShaderDescs.end()) { return E_FAIL; }

	m_umapGeometryShaderDescs.insert({ _wstrGeometryShaderName, _spGeometryShaderDesc });
	return S_OK;
}

HRESULT Engine::CShaderHandler::AddPixelShaderDesc(const std::wstring& _wstrPixelShaderName, std::shared_ptr<FPixelShaderDesc> _spPixelShaderDesc)
{
	if (m_umapPixelShaderDescs.find(_wstrPixelShaderName) != m_umapPixelShaderDescs.end()) { return E_FAIL; }

	m_umapPixelShaderDescs.insert({ _wstrPixelShaderName, _spPixelShaderDesc });
	return S_OK;
}

std::shared_ptr<FVertexShaderDesc> Engine::CShaderHandler::FindVertexShaderDesc(const std::wstring& _wstrVertexShaderName)
{
	if (m_umapVertexShaderDescs.find(_wstrVertexShaderName) == m_umapVertexShaderDescs.end()) { return nullptr; }

	return m_umapVertexShaderDescs[_wstrVertexShaderName];
}

std::shared_ptr<FGeometryShaderDesc> Engine::CShaderHandler::FindGeometryShaderDesc(const std::wstring& _wstrGeometryShaderName)
{
	if (m_umapGeometryShaderDescs.find(_wstrGeometryShaderName) == m_umapGeometryShaderDescs.end()) { return nullptr; }

	return m_umapGeometryShaderDescs[_wstrGeometryShaderName];
}

std::shared_ptr<FPixelShaderDesc> Engine::CShaderHandler::FindPixelShaderDesc(const std::wstring& _wstrPixelShaderName)
{
	if (m_umapPixelShaderDescs.find(_wstrPixelShaderName) == m_umapPixelShaderDescs.end()) { return nullptr; }

	return m_umapPixelShaderDescs[_wstrPixelShaderName];
}
