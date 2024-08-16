#include "pch.h"
#include "Size2DConstantBuffer.h"

// manager
#include "DeviceManager.h"

#include "SceneComponent.h"

#include "UI.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CSize2DConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }
	m_wpUI = dynamic_pointer_cast<CUI>(_spOwnerActor);
	
	m_tSize2D.m_fWidth = m_wpUI.lock()->GetWidth();
	m_tSize2D.m_fHeight = m_wpUI.lock()->GetHeight();
	m_tSize2D.m_fMaxWidth = m_wpUI.lock()->GetMaxWidth();
	m_tSize2D.m_fMaxHeight = m_wpUI.lock()->GetMaxHeight();
	return S_OK;
}

void Engine::CSize2DConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CSize2DConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	m_tSize2D.m_fWidth = m_wpUI.lock()->GetWidth();
	m_tSize2D.m_fHeight = m_wpUI.lock()->GetHeight();
}

void Engine::CSize2DConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FSize2D>(m_cpBuffer, m_tSize2D);
}
