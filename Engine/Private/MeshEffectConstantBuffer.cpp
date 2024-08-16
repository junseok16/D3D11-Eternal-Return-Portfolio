#include "pch.h"
#include "MeshEffectConstantBuffer.h"

// manager
#include "DeviceManager.h"

// handler
#include "ShaderHandler.h"

// effect
#include "EffectMeshData.h"

HRESULT Engine::CMeshEffectConstantBuffer::Initialize(const std::shared_ptr<CActor>& _spOwnerActor, const std::wstring& _wstrConstantBufferName, uint8 _iBindPoint)
{
	if (FAILED(CConstantBuffer::Initialize(_spOwnerActor, _wstrConstantBufferName, _iBindPoint))) { return E_FAIL; }

	return S_OK;
}

void Engine::CMeshEffectConstantBuffer::Release()
{
	CConstantBuffer::Release();
}

void Engine::CMeshEffectConstantBuffer::TickConstantBuffer(uint32 _iIndex)
{
	FUVEffectProperty tUVProperty = m_wpEffectMeshData.lock()->GetUVProperty();
	m_tMeshEffectConstantBuffer.m_iUseEffectUV = tUVProperty.m_bUseEffectUV;
	m_tMeshEffectConstantBuffer.m_vCurEffectUV = m_wpEffectMeshData.lock()->GetCurEffectUV();

	FMaskEffectProperty tMaskEffectProperty = m_wpEffectMeshData.lock()->GetMaskProperty();
	m_tMeshEffectConstantBuffer.m_iUseMask = (int32)tMaskEffectProperty.m_bUseMask;
	m_tMeshEffectConstantBuffer.m_iUseColorMask = (int32)tMaskEffectProperty.m_bUseColorMask;
	m_tMeshEffectConstantBuffer.m_iMaskNumRow = tMaskEffectProperty.m_iMaskRowColume[0];
	m_tMeshEffectConstantBuffer.m_iMaskNumColumn = tMaskEffectProperty.m_iMaskRowColume[1];
	m_tMeshEffectConstantBuffer.m_vCurMaskUV = m_wpEffectMeshData.lock()->GetCurMaskUV();
	m_tMeshEffectConstantBuffer.m_iCurMaskIndex = m_wpEffectMeshData.lock()->GetCurMaskIndex();

	FNoiseEffectProperty tNoiseEffecProperty = m_wpEffectMeshData.lock()->GetNoiseProperty();
	m_tMeshEffectConstantBuffer.m_iUseNoise = (int32)tNoiseEffecProperty.m_bUseNoise;
	m_tMeshEffectConstantBuffer.m_iNoiseNumRow = tNoiseEffecProperty.m_iNoiseRowColume[0];
	m_tMeshEffectConstantBuffer.m_iNoiseNumColumn = tNoiseEffecProperty.m_iNoiseRowColume[1];
	m_tMeshEffectConstantBuffer.m_vCurNoiseUV = m_wpEffectMeshData.lock()->GetCurNoiseUV();

	m_tMeshEffectConstantBuffer.m_fRatio = m_wpEffectMeshData.lock()->GetCurRatio();
	m_tMeshEffectConstantBuffer.m_vCurColor = m_wpEffectMeshData.lock()->GetCurColor();
}

void Engine::CMeshEffectConstantBuffer::CopyConstantBuffer(uint32 _iIndex)
{
	m_wpShaderHandler.lock()->CopyConstantBuffer<FMeshEffectConstantBuffer>(m_cpBuffer, m_tMeshEffectConstantBuffer);
}
