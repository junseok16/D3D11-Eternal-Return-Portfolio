#include "pch.h"
#include "VertexBuffer.h"

#include "ModelHandler.h"
#include "BufferHandler.h"
#include "EffectHandler.h"

HRESULT Engine::CVertexBuffer::Initialize(std::shared_ptr<FModelDesc> _spModelDesc, int32 _iMeshIndex, EPrimitiveType _ePrimitiveType)
{
	if (FAILED(IBuffer::Initialize())) { return E_FAIL; }

	// 도형인 경우
	switch (_ePrimitiveType)
	{
	case Engine::EPrimitiveType::POINT:
	{
		m_cpBuffer = m_wpBufferHandler.lock()->FindVertexBuffer(L"Point");
		m_iNumVertices = 1;
		m_eBufferType = EBufferType::VERTEX;
		m_wstrBufferName = L"Point";
		m_iStride = sizeof(TPosition);
	}
	break;

	case Engine::EPrimitiveType::RECT:
	{
		m_cpBuffer = m_wpBufferHandler.lock()->FindVertexBuffer(L"Rect");
		m_iNumVertices = 4;
		m_eBufferType = EBufferType::VERTEX;
		m_wstrBufferName = L"Rect";
		m_iStride = sizeof(TPositionTexCoord2);
	}
	break;

	case Engine::EPrimitiveType::CUBE:
	{
		m_cpBuffer = m_wpBufferHandler.lock()->FindVertexBuffer(L"Cube");
		m_iNumVertices = 8;
		m_eBufferType = EBufferType::VERTEX;
		m_wstrBufferName = L"Cube";
		m_iStride = sizeof(TPositionTexCoord3);
	}
	break;

	case Engine::EPrimitiveType::ENUM_END:
		break;

	default:
		break;
	}

	// 모델인 경우
	if (_spModelDesc)
	{
		wstring wstrBufferName = _spModelDesc->m_wstrModelName + to_wstring(_iMeshIndex);
		m_iNumVertices = _spModelDesc->m_vecNumVertices[_iMeshIndex];
		m_eBufferType = EBufferType::VERTEX;
		m_wstrBufferName = wstrBufferName;

		switch (_spModelDesc->m_eModelType)
		{
		case EModelType::STATIC:
			m_cpBuffer = m_wpModelHandler.lock()->FindVertexBuffer(wstrBufferName);
			m_iStride = sizeof(TPositionNormalTexCoordTangent);
			break;

		case EModelType::EFFECT:
			m_cpBuffer = m_wpEffectHandler.lock()->FindVertexBuffer(wstrBufferName);
			m_iStride = sizeof(TPositionNormalTexCoordTangent);
			break;

		case EModelType::SKELETAL:
			m_cpBuffer = m_wpModelHandler.lock()->FindVertexBuffer(wstrBufferName);
			m_iStride = sizeof(TPositionNormalTexCoordTangentBlend);
			break;

		default:
			CHECKF(false, L"Failed to initialize vertex buffer.");
			break;
		}
	}

	return S_OK;
}

void Engine::CVertexBuffer::Release()
{
	IBuffer::Release();
}

void Engine::CVertexBuffer::IASetVertexBuffer()
{
	vector<ComPtr<ID3D11Buffer>> vecVertexBuffers{ m_cpBuffer };
	vector<uint32> vecStrides{ m_iStride };
	vector<uint32> vecOffsets{ m_iOffset };

	m_wpModelHandler.lock()->IASetVertexBuffers(0, 1, vecVertexBuffers.data()->GetAddressOf(), vecStrides.data(), vecOffsets.data());
}

void Engine::CVertexBuffer::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _ePrimitiveTopology)
{
	m_wpBufferHandler.lock()->IASetPrimitiveTopology(_ePrimitiveTopology);
}

void Engine::CVertexBuffer::Draw()
{
	m_wpBufferHandler.lock()->Draw(1, 0);
}
