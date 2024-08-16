#include "pch.h"
#include "BoneOffset.h"

std::shared_ptr<CBoneOffset> Engine::CBoneOffset::Create(uint32 _iNumBones, const vector<uint32>& _vecBoneIndices, const vector<Matrix>& _vecOffsetMatrices)
{
	const shared_ptr<CBoneOffset> spBoneOffset = make_shared<CBoneOffset>();
	spBoneOffset->Initialize(_iNumBones, _vecBoneIndices, _vecOffsetMatrices);
	return spBoneOffset;
}

HRESULT Engine::CBoneOffset::Initialize(uint32 _iNumBones, const vector<uint32>& _vecBoneIndices, const vector<Matrix>& _vecOffsetMatrices)
{
	m_iNumBones = _iNumBones;
	m_vecBoneIndices = _vecBoneIndices;
	m_vecOffsetMatrices = _vecOffsetMatrices;
	return S_OK;
}

void Engine::CBoneOffset::Release()
{
}
