#include "pch.h"
#include "BoneConstantBuffer.h"

// manager
#include "DeviceManager.h"

//
#include "SkeletalMeshData.h"
#include "MeshBone.h"
#include "MeshBuffer.h"
#include "BoneOffset.h"
#include "Bone.h"

// handler
#include "ShaderHandler.h"

HRESULT Engine::CBoneConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	return S_OK;
}

void Engine::CBoneConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CBoneConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	auto& vecBones = m_wpSkeletalMeshData.lock()->GetMeshBone()->GetBones();

	auto& vecBoneOffsets = m_wpSkeletalMeshData.lock()->GetMeshBuffer()->GetBoneOffsets();
	
	// _iIndex번째 메시의 본의 수
	auto iNumBones = vecBoneOffsets[_iIndex]->GetNumBones();

	auto& vecBoneIndices = vecBoneOffsets[_iIndex]->GetBoneIndices();

	auto& vecOffsetMatrices = vecBoneOffsets[_iIndex]->GetOffsetMatrices();

	for (size_t iIndex = 0; iIndex < iNumBones; ++iIndex)
	{
		Matrix matA = vecOffsetMatrices[iIndex];
		Matrix matB = vecBones[vecBoneIndices[iIndex]]->GetWorldMatrix();
		Matrix matC = matA * matB;

		matC.Transpose(matC);
		m_tBoneConstantBuffer.m_matBone[iIndex] = matC;
	}
}

void Engine::CBoneConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FBoneConstantBuffer>(m_cpBuffer, m_tBoneConstantBuffer);
}
