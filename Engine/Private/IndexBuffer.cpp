#include "pch.h"
#include "IndexBuffer.h"

#include "ModelHandler.h"
#include "BufferHandler.h"
#include "EffectHandler.h"

HRESULT Engine::CIndexBuffer::Initialize(std::shared_ptr<FModelDesc> _spModelDesc, int32 _iMeshIndex, EPrimitiveType _ePrimitiveType)
{
	if (FAILED(IBuffer::Initialize())) { return E_FAIL; }

	// 도형인 경우
	switch (_ePrimitiveType)
	{
	case Engine::EPrimitiveType::RECT:
	{
		m_cpBuffer = m_wpBufferHandler.lock()->FindIndexBuffer(L"Rect");
		m_iNumIndices = 6;
		m_iStride = sizeof(uint32);
		m_eIndexFormat = DXGI_FORMAT_R32_UINT;
		m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_eBufferType = EBufferType::INDEX;
		m_wstrBufferName = L"Rect";
	}
	break;

	case Engine::EPrimitiveType::CUBE:
	{
		m_cpBuffer = m_wpBufferHandler.lock()->FindIndexBuffer(L"Cube");
		m_iNumIndices = 36;
		m_iStride = sizeof(uint32);
		m_eIndexFormat = DXGI_FORMAT_R32_UINT;
		m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_eBufferType = EBufferType::INDEX;
		m_wstrBufferName = L"Cube";
	}
	break;

	case Engine::EPrimitiveType::POINT:
	case Engine::EPrimitiveType::ENUM_END:
		break;

	default:
		break;
	}

	// 모델인 경우
	if (_spModelDesc)
	{
		wstring wstrBufferName = _spModelDesc->m_wstrModelName + to_wstring(_iMeshIndex);
		
		m_iNumIndices = _spModelDesc->m_vecNumIndices[_iMeshIndex];
		m_iStride = sizeof(uint32);
		m_eIndexFormat = DXGI_FORMAT_R32_UINT;
		m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_eBufferType = EBufferType::INDEX;
		m_wstrBufferName = wstrBufferName;

		switch (_spModelDesc->m_eModelType)
		{
		case EModelType::STATIC:
		case EModelType::SKELETAL:
			m_cpBuffer = m_wpModelHandler.lock()->FindIndexBuffer(wstrBufferName);
			break;

		case EModelType::EFFECT:
			m_cpBuffer = m_wpEffectHandler.lock()->FindIndexBuffer(wstrBufferName);
			break;

		default:
			CHECKF(false, L"Failed to initialize index buffer.");
			break;
		}
	}

	return S_OK;
}

void Engine::CIndexBuffer::Release()
{
	IBuffer::Release();
}

void Engine::CIndexBuffer::IASetIndexBuffer()
{
	m_wpModelHandler.lock()->IASetIndexBuffer(m_cpBuffer.Get(), m_eIndexFormat, 0);
}

void Engine::CIndexBuffer::IASetPrimitiveTopology()
{
	m_wpModelHandler.lock()->IASetPrimitiveTopology(m_ePrimitiveTopology);
}

void Engine::CIndexBuffer::DrawIndexed()
{
	m_wpModelHandler.lock()->DrawIndexed(m_iNumIndices, 0, 0);
}
