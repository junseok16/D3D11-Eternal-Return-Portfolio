#include "pch.h"
#include "ConstantBuffer.h"

#include "ShaderHandler.h"

HRESULT Engine::CConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	m_wpOwnerActor = _spOwnerActor;
	m_wpShaderHandler = CShaderHandler::GetInstance();
	CHECK(!m_wpShaderHandler.expired());

	ComPtr<ID3D11Buffer> cpBuffer = m_wpShaderHandler.lock()->FindConstantBuffer(_wstrConstantBufferName);
	CHECK(cpBuffer != nullptr);

	m_cpBuffer = cpBuffer;
	m_eBufferType = EBufferType::CONSTANT;
	m_iBindPoint = _iBindPoint;
	m_wstrConstantBufferName = _wstrConstantBufferName;
	return S_OK;
}

void Engine::CConstantBuffer::Release()
{
	m_cpBuffer = nullptr;
}

void Engine::CConstantBuffer::VSSetConstantBuffers()
{
	if (!m_cpBuffer || m_iBindPoint < 0) { return; }
	m_wpShaderHandler.lock()->VSSetConstantBuffers(m_iBindPoint, 1, m_cpBuffer.GetAddressOf());
}

void Engine::CConstantBuffer::PSSetConstantBuffers()
{
	if (!m_cpBuffer || m_iBindPoint < 0) { return; }
	m_wpShaderHandler.lock()->PSSetConstantBuffers(m_iBindPoint, 1, m_cpBuffer.GetAddressOf());
}

void Engine::CConstantBuffer::GSSetConstantBuffers()
{
	if (!m_cpBuffer || m_iBindPoint < 0) { return; }
	m_wpShaderHandler.lock()->GSSetConstantBuffers(m_iBindPoint, 1, m_cpBuffer.GetAddressOf());
}

void Engine::CConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	return;
}

void Engine::CConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	return;
}
