#include "pch.h"
#include "InstanceVertexBuffer.h"

// manager
#include "DeviceManager.h"

// handler
#include "BufferHandler.h"

HRESULT Engine::CInstanceVertexBuffer::Initialize(std::shared_ptr<FModelDesc> _spModelDesc, int32 _iNumInstances, EPrimitiveType _ePrimitiveType)
{
	if (FAILED(IBuffer::Initialize())) { return E_FAIL; }

	// ������ ���
	switch (_ePrimitiveType)
	{
	case Engine::EPrimitiveType::INSTANCE_POINT:
	{
		// ���ؽ� ���� ������
		m_eBufferType = EBufferType::VERTEX;
		m_iStride = sizeof(TPositionSize);
		m_iNumVertices = 1;
		m_iNumVertexBuffers = 2;

		// �ν��Ͻ� ���� ������
		m_iInstanceStride = sizeof(TInstanceTransform);
		m_iNumInstances = _iNumInstances;

		// ���ؽ� ���۸� �����մϴ�.
		m_cpBuffer = m_wpBufferHandler.lock()->FindInstanceVertexBuffer(L"InstancePoint");
		
		// �ν��Ͻ� ���۸� �����մϴ�.
		m_wpBufferHandler.lock()->LoadInstanceTransform(L"InstancePoint" + to_wstring(_iNumInstances), _iNumInstances);
		m_wpBufferHandler.lock()->CreateInstanceTransformBuffer(L"InstancePoint" + to_wstring(_iNumInstances));
		m_cpInstanceBuffer = m_wpBufferHandler.lock()->FindInstanceTransformBuffer(L"InstancePoint" + to_wstring(_iNumInstances));
	}
	break;

	default:
		CHECKF(false, L"The primitive type of the instance buffer should be an instance rectangle.");
		break;
	}

	return S_OK;
}

void Engine::CInstanceVertexBuffer::Release()
{
	IBuffer::Release();
}

int32 Engine::CInstanceVertexBuffer::Tick(float _fDeltaSeconds)
{
	shared_ptr<CDeviceManager> spDeviceManger = m_wpBufferHandler.lock()->GetDeviceManager();

	D3D11_MAPPED_SUBRESOURCE tSubResource;
	ZeroMemory(&tSubResource, sizeof(tSubResource));

	spDeviceManger->GetDeviceContext()->Map(m_cpInstanceBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &tSubResource);

	for (uint32 iIndex = 0; iIndex < m_iNumInstances; ++iIndex)
	{
		reinterpret_cast<TInstanceTransform*>(tSubResource.pData)[iIndex].m_vPosition.y;
	}

	spDeviceManger->GetDeviceContext()->Unmap(m_cpInstanceBuffer.Get(), 0);
	return 0;
}

void Engine::CInstanceVertexBuffer::IASetVertexBuffer()
{
	vector<ComPtr<ID3D11Buffer>> vecVertexBuffers{ m_cpBuffer, m_cpInstanceBuffer };
	vector<uint32> vecStrides{ m_iStride, m_iInstanceStride };
	vector<uint32> vecOffsets{ m_iOffset, m_iInstanceOffset };

	m_wpBufferHandler.lock()->IASetVertexBuffers(0, static_cast<UINT>(vecVertexBuffers.size()), vecVertexBuffers.data()->GetAddressOf(), vecStrides.data(), vecOffsets.data());
}

void Engine::CInstanceVertexBuffer::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _ePrimitiveTopology)
{
	m_wpBufferHandler.lock()->IASetPrimitiveTopology(_ePrimitiveTopology);
}
