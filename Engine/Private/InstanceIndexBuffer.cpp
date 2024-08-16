#include "pch.h"
#include "InstanceIndexBuffer.h"

#include "ModelHandler.h"
#include "BufferHandler.h"
#include "EffectHandler.h"

HRESULT Engine::CInstanceIndexBuffer::Initialize(std::shared_ptr<FModelDesc> _spModelDesc, int32 _iNumInstances, EPrimitiveType _ePrimitiveType)
{
	if (FAILED(IBuffer::Initialize())) { return E_FAIL; }

	// 도형인 경우
	switch (_ePrimitiveType)
	{
	case Engine::EPrimitiveType::INSTANCE_POINT:
	{
		// 인덱스 버퍼 데이터
		m_eBufferType = EBufferType::INDEX;
		m_iNumIndices = _iNumInstances;

		// 메시 인덱스 매개 변수를 인스턴스의 개수로 활용합니다.
		m_iNumInstances = _iNumInstances;

		// 인덱스 버퍼를 생성합니다.
		m_wpBufferHandler.lock()->LoadInstanceIndex(L"InstancePoint" + to_wstring(_iNumInstances), _iNumInstances);
		m_wpBufferHandler.lock()->CreateInstanceIndexBuffer(L"InstancePoint" + to_wstring(_iNumInstances));
		
		m_cpBuffer = m_wpBufferHandler.lock()->FindInstanceIndexBuffer(L"InstancePoint" + to_wstring(_iNumInstances));
	}
	break;

	default:
		CHECKF(false, L"The primitive type of the instance buffer should be an instance rectangle.");
		break;
	}

	return S_OK;
}

void Engine::CInstanceIndexBuffer::Release()
{
	IBuffer::Release();
}

void Engine::CInstanceIndexBuffer::IASetIndexBuffer()
{
	m_wpBufferHandler.lock()->IASetIndexBuffer(m_cpBuffer.Get(), m_eIndexFormat, 0);
}

void Engine::CInstanceIndexBuffer::IASetPrimitiveTopology()
{
	m_wpBufferHandler.lock()->IASetPrimitiveTopology(m_ePrimitiveTopology);
}

void Engine::CInstanceIndexBuffer::DrawIndexedInstanced()
{
	m_wpBufferHandler.lock()->DrawIndexedInstanced(1, m_iNumInstances, 0, 0, 0);
}
