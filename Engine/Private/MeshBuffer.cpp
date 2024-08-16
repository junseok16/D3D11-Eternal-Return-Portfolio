#include "pch.h"
#include "MeshBuffer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BoneOffset.h"

#include "ModelHandler.h"
#include "EffectHandler.h"

std::shared_ptr<CMeshBuffer> Engine::CMeshBuffer::Create(const std::wstring& _wstrModelDesc)
{
	const shared_ptr<CMeshBuffer> spMeshBuffer = make_shared<CMeshBuffer>();
	ENSUREF(spMeshBuffer->Initialize(_wstrModelDesc), L"Failed to initialize mesh buffer.");
	return spMeshBuffer;
}

HRESULT Engine::CMeshBuffer::Initialize(const std::wstring& _wstrModelDesc)
{
	if (_wstrModelDesc.empty()) { return S_OK; }

	shared_ptr<FModelDesc> spModelDesc = CModelHandler::GetInstance()->FindModelDesc(_wstrModelDesc);
	
	if (!spModelDesc)
	{
		spModelDesc = CEffectHandler::GetInstance()->FindModelDesc(_wstrModelDesc);
	}

	uint32 iNumMeshes = spModelDesc->m_iNumMeshes;
	switch (spModelDesc->m_eModelType)
	{
	case EModelType::STATIC:
	case EModelType::EFFECT:
		m_vecVertexBuffers.reserve(iNumMeshes);
		m_vecVertexBuffers.resize(iNumMeshes);
		m_vecIndexBuffers.reserve(iNumMeshes);
		m_vecIndexBuffers.resize(iNumMeshes);
		
		for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
		{
			m_vecVertexBuffers[iIndex] = CVertexBuffer::Create<CVertexBuffer>(spModelDesc, iIndex);
			m_vecIndexBuffers[iIndex] = CIndexBuffer::Create<CIndexBuffer>(spModelDesc, iIndex);
		}
		break;

	case EModelType::SKELETAL:
		m_vecVertexBuffers.reserve(iNumMeshes);
		m_vecVertexBuffers.resize(iNumMeshes);
		m_vecIndexBuffers.reserve(iNumMeshes);
		m_vecIndexBuffers.resize(iNumMeshes);
		m_vecBoneOffsets.reserve(iNumMeshes);
		m_vecBoneOffsets.resize(iNumMeshes);

		for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
		{
			m_vecBoneOffsets[iIndex] = CModelHandler::GetInstance()->FindBoneOffset(spModelDesc->m_wstrModelName + to_wstring(iIndex));
			m_vecVertexBuffers[iIndex] = CVertexBuffer::Create<CVertexBuffer>(spModelDesc, iIndex);
			m_vecIndexBuffers[iIndex] = CIndexBuffer::Create<CIndexBuffer>(spModelDesc, iIndex);
		}
		break;

	default:
		break;
	}
	return S_OK;
}

void Engine::CMeshBuffer::Release()
{
	if (!m_vecBoneOffsets.empty())
	{
		for (auto& spBoneOffset : m_vecBoneOffsets)
		{
			spBoneOffset->Release();
			spBoneOffset = nullptr;
		}
		m_vecBoneOffsets.clear();
	}

	for (auto& spVertexBuffer : m_vecVertexBuffers)
	{
		spVertexBuffer->Release();
		spVertexBuffer = nullptr;
	}
	m_vecVertexBuffers.clear();

	for (auto& spIndexBuffer : m_vecIndexBuffers)
	{
		spIndexBuffer->Release();
		spIndexBuffer = nullptr;
	}
	m_vecIndexBuffers.clear();
}

void Engine::CMeshBuffer::SetVertexBuffer(uint16 _iMeshIndex, std::shared_ptr<CVertexBuffer> _spVertexBuffer)
{
	// 메모리 공간을 확보합니다.
	if (m_vecVertexBuffers.size() < _iMeshIndex)
	{
		m_vecVertexBuffers.reserve(_iMeshIndex);
		m_vecVertexBuffers.resize(_iMeshIndex);
	}
	m_vecVertexBuffers[_iMeshIndex] = _spVertexBuffer;
}

void Engine::CMeshBuffer::SetIndexBuffer(uint16 _iMeshIndex, std::shared_ptr<CIndexBuffer> _spIndexBuffer)
{
	// 메모리 공간을 확보합니다.
	if (m_vecIndexBuffers.size() < _iMeshIndex)
	{
		m_vecIndexBuffers.reserve(_iMeshIndex);
		m_vecIndexBuffers.resize(_iMeshIndex);
	}
	m_vecIndexBuffers[_iMeshIndex] = _spIndexBuffer;
}

void Engine::CMeshBuffer::IASetVertexBuffer(uint16 _iMeshIndex)
{
	m_vecVertexBuffers[_iMeshIndex]->IASetVertexBuffer();
}

void Engine::CMeshBuffer::IASetIndexBuffer(uint16 _iMeshIndex)
{
	m_vecIndexBuffers[_iMeshIndex]->IASetIndexBuffer();
}

void Engine::CMeshBuffer::IASetPrimitiveTopology(uint16 _iMeshIndex)
{
	m_vecIndexBuffers[_iMeshIndex]->IASetPrimitiveTopology();
}

void Engine::CMeshBuffer::DrawIndexed(uint16 _iMeshIndex)
{
	m_vecIndexBuffers[_iMeshIndex]->DrawIndexed();
}
