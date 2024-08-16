#include "pch.h"
#include "RatioConstantBuffer.h"

// manager
#include "DeviceManager.h"

#include "Image.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CRatioConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }
	m_wpImage = dynamic_pointer_cast<CImage>(_spOwnerActor);

	m_tRatio.m_fRatio = 0.0f;
	return S_OK;
}

void Engine::CRatioConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CRatioConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tRatio.m_fRatio = m_wpImage.lock()->GetCurRatio();
}

void Engine::CRatioConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FRatioConstantBuffer>(m_cpBuffer, m_tRatio);
}
