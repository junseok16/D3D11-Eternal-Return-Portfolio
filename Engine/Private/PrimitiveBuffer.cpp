// default
#include "pch.h"
#include "PrimitiveBuffer.h"

// buffer
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InstanceVertexBuffer.h"
#include "InstanceIndexBuffer.h"

// handler
#include "BufferHandler.h"

std::shared_ptr<CPrimitiveBuffer> Engine::CPrimitiveBuffer::Create(EPrimitiveType _ePrimitiveType, uint32 _iNumInstances)
{
	const std::shared_ptr<CPrimitiveBuffer> spPrimitiveBuffer = make_shared<CPrimitiveBuffer>();
	ENSUREF(spPrimitiveBuffer->Initialize(_ePrimitiveType, _iNumInstances), L"Failed to initialize primitive buffer");
	return spPrimitiveBuffer;
}

HRESULT Engine::CPrimitiveBuffer::Initialize(EPrimitiveType _ePrimitiveType, uint32 _iNumInstances)
{
	m_ePrimitiveType = _ePrimitiveType;

	switch (_ePrimitiveType)
	{
	case Engine::EPrimitiveType::POINT:
		m_spVertexBuffer = CVertexBuffer::Create<CVertexBuffer>(nullptr, -1, EPrimitiveType::POINT);
		break;

	case Engine::EPrimitiveType::RECT:
		m_spVertexBuffer = CVertexBuffer::Create<CVertexBuffer>(nullptr, -1, EPrimitiveType::RECT);
		m_spIndexBuffer = CIndexBuffer::Create<CIndexBuffer>(nullptr, -1, EPrimitiveType::RECT);
		break;

	case Engine::EPrimitiveType::CUBE:
		m_spVertexBuffer = CVertexBuffer::Create<CVertexBuffer>(nullptr, -1, EPrimitiveType::CUBE);
		m_spIndexBuffer = CIndexBuffer::Create<CIndexBuffer>(nullptr, -1, EPrimitiveType::CUBE);
		break;

	case Engine::EPrimitiveType::INSTANCE_POINT:
		m_spInstanceVertexBuffer = CInstanceVertexBuffer::Create<CInstanceVertexBuffer>(nullptr, _iNumInstances, EPrimitiveType::INSTANCE_POINT);
		m_spInstanceIndexBuffer = CInstanceIndexBuffer::Create<CInstanceIndexBuffer>(nullptr, _iNumInstances, EPrimitiveType::INSTANCE_POINT);
		break;

	default:
		CHECKF(false, L"primitive type is not designated.");
		break;
	}

	return S_OK;
}

int32 Engine::CPrimitiveBuffer::Tick(EEffectShapeType _eEffectShapeType, float _fDeltaSeconds)
{
	if (m_spInstanceVertexBuffer)
	{
		switch (_eEffectShapeType)
		{
		case Engine::EEffectShapeType::SPREAD:
			m_spInstanceVertexBuffer->Tick(_fDeltaSeconds);
			break;

		case Engine::EEffectShapeType::SPOT:
			break;

		case Engine::EEffectShapeType::FALL_DOWN:
			break;

		default:
			break;
		}

	}
	return 0;
}

void Engine::CPrimitiveBuffer::Release()
{
	if (m_spVertexBuffer)
	{
		m_spVertexBuffer->Release();
		m_spVertexBuffer = nullptr;
	}

	if (m_spIndexBuffer)
	{
		m_spIndexBuffer->Release();
		m_spIndexBuffer = nullptr;
	}

	if (m_spInstanceVertexBuffer)
	{
		m_spInstanceVertexBuffer->Release();
		m_spInstanceVertexBuffer = nullptr;
	}

	if (m_spInstanceIndexBuffer)
	{
		m_spInstanceIndexBuffer->Release();
		m_spInstanceIndexBuffer = nullptr;
	}
}

void Engine::CPrimitiveBuffer::SetVertexBuffer(std::shared_ptr<CVertexBuffer> _spVertexBuffer)
{
	m_spVertexBuffer = _spVertexBuffer;
}

void Engine::CPrimitiveBuffer::SetIndexBuffer(std::shared_ptr<CIndexBuffer> _spIndexBuffer)
{
	m_spIndexBuffer = _spIndexBuffer;
}

void Engine::CPrimitiveBuffer::IASetVertexBuffer()
{
	m_spVertexBuffer->IASetVertexBuffer();
}

void Engine::CPrimitiveBuffer::IASetIndexBuffer()
{
	m_spIndexBuffer->IASetIndexBuffer();
}

void Engine::CPrimitiveBuffer::IASetPrimitiveTopology()
{
	m_spIndexBuffer->IASetPrimitiveTopology();
}

void Engine::CPrimitiveBuffer::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _ePrimitiveTopology)
{
	m_spVertexBuffer->IASetPrimitiveTopology(_ePrimitiveTopology);
}

void Engine::CPrimitiveBuffer::DrawIndexed()
{
	m_spIndexBuffer->DrawIndexed();
}

void Engine::CPrimitiveBuffer::Draw()
{
	m_spVertexBuffer->Draw();
}

void Engine::CPrimitiveBuffer::DrawIndexedInstanced()
{
	m_spInstanceIndexBuffer->DrawIndexedInstanced();
}
