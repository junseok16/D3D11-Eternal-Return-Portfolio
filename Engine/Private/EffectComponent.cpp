#include "pch.h"
#include "EffectComponent.h"

// effect
#include "EffectMeshData.h"
#include "EffectParticleData.h"

// handler
#include "StateHandler.h"
#include "EffectHandler.h"

HRESULT Engine::CEffectComponent::PreInitializeComponent()
{
	if (FAILED(CMeshComponent::PreInitializeComponent())) { return E_FAIL; }

	m_wpStateHandler = CStateHandler::GetInstance();
	m_cpCullBackState = m_wpStateHandler.lock()->FindRasterizerState(L"RS_FILL_SOLID_CULL_BACK");
	m_cpCullNoneState = m_wpStateHandler.lock()->FindRasterizerState(L"RS_FILL_SOLID_CULL_NONE");
	m_cpBlendEnableState = m_wpStateHandler.lock()->FindBlendState(L"BS_BLEND_ENABLE");
	m_cpBlendDisableState = m_wpStateHandler.lock()->FindBlendState(L"BS_BLEND_DISABLE");
	return S_OK;
}

HRESULT Engine::CEffectComponent::InitializeComponent()
{
	if (FAILED(CMeshComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CEffectComponent::PostInitializeComponent()
{
	if (FAILED(CMeshComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CEffectComponent::BeginPlay()
{
	if (FAILED(CMeshComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CEffectComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CEffectComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CEffectComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	for (const auto& pair : m_umapEffectMeshData)
	{
		pair.second->Tick(_fDeltaSeconds);
	}

	for (const auto& pair : m_umapEffectParticleData)
	{
		pair.second->Tick(_fDeltaSeconds);
	}

	return 0;
}

HRESULT Engine::CEffectComponent::EndPlay()
{
	if (FAILED(CMeshComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CEffectComponent::Render()
{
	CMeshComponent::Render();

	// float fBlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// UINT iSampleMask = 0xffff'ffff;
	// 
	// m_wpStateHandler.lock()->RSSetState(m_cpCullNoneState.Get());
	// m_wpStateHandler.lock()->OMSetBlendState(m_cpBlendEnableState.Get(), fBlendFactor, iSampleMask);

	for (const auto& pair : m_umapEffectMeshData)
	{
		pair.second->Render();
	}

	for (const auto& pair : m_umapEffectParticleData)
	{
		pair.second->Render();
	}

	// m_wpStateHandler.lock()->RSSetState(m_cpCullBackState.Get());
	// m_wpStateHandler.lock()->OMSetBlendState(m_cpBlendDisableState.Get(), fBlendFactor, iSampleMask);
}

void Engine::CEffectComponent::Release()
{
	for (auto& pair : m_umapEffectMeshData)
	{
		pair.second->Release();
		pair.second = nullptr;
	}

	for (auto& pair : m_umapEffectParticleData)
	{
		pair.second->Release();
		pair.second = nullptr;
	}

	m_cpCullNoneState = nullptr;
	m_cpCullBackState = nullptr;
	m_cpBlendEnableState = nullptr;
	m_cpBlendDisableState = nullptr;

	CMeshComponent::Release();
}

HRESULT Engine::CEffectComponent::AddMeshEffect(const std::wstring& _wstrMeshEffectDataName, const std::shared_ptr<CEffectMeshData>& _spEffectMeshData)
{
	if (m_umapEffectMeshData.find(_wstrMeshEffectDataName) != m_umapEffectMeshData.end()) { return E_FAIL; }

	m_umapEffectMeshData.insert({ _wstrMeshEffectDataName, _spEffectMeshData });
	return S_OK;
}

HRESULT Engine::CEffectComponent::RemoveMeshEffect(const std::wstring& _wstrMeshEffectDataName)
{
	if (m_umapEffectMeshData.find(_wstrMeshEffectDataName) == m_umapEffectMeshData.end()) { return E_FAIL; }

	m_umapEffectMeshData.erase(_wstrMeshEffectDataName);
	return S_OK;
}

HRESULT Engine::CEffectComponent::CreateMeshEffectDataGroup(const std::wstring& _wstrMeshEffectDataGroupName)
{
	std::shared_ptr<FMeshEffectDataGroupProperty> spMeshEffectDataGroup = CEffectHandler::GetInstance()->FindEffectMeshDataGroup(_wstrMeshEffectDataGroupName);
	if (!spMeshEffectDataGroup) { return E_FAIL; }

	spMeshEffectDataGroup->m_wstrMeshEffectGroupName;

	for (size_t iIndex = 0; iIndex < spMeshEffectDataGroup->m_vecMeshEffectDataNames.size(); ++iIndex)
	{
		shared_ptr<CEffectMeshData> spEffectMeshData = CEffectMeshData::Create(dynamic_pointer_cast<CSceneComponent>(shared_from_this()));
		
		spEffectMeshData->SetPlayProperty
		(
			spMeshEffectDataGroup->m_vecPlayProperties[iIndex].m_fStartPlaySeconds,
			spMeshEffectDataGroup->m_vecPlayProperties[iIndex].m_fFinishPlaySeconds,
			spMeshEffectDataGroup->m_vecPlayProperties[iIndex].m_bLoop
		);

		spEffectMeshData->SetMaskProperty
		(
			spMeshEffectDataGroup->m_vecMaskProperties[iIndex].m_bUseMask,
			spMeshEffectDataGroup->m_vecMaskProperties[iIndex].m_bUseColorMask,
			spMeshEffectDataGroup->m_vecMaskProperties[iIndex].m_iMaskRowColume[0],
			spMeshEffectDataGroup->m_vecMaskProperties[iIndex].m_iMaskRowColume[1],
			spMeshEffectDataGroup->m_vecMaskProperties[iIndex].m_vMaskUVSpeed,
			spMeshEffectDataGroup->m_vecMaskProperties[iIndex].m_vMaskMaxUV
		);

		spEffectMeshData->SetNoiseProperty
		(
			spMeshEffectDataGroup->m_vecNoiseProperties[iIndex].m_bUseNoise,
			spMeshEffectDataGroup->m_vecNoiseProperties[iIndex].m_iNoiseRowColume[0],
			spMeshEffectDataGroup->m_vecNoiseProperties[iIndex].m_iNoiseRowColume[1],
			spMeshEffectDataGroup->m_vecNoiseProperties[iIndex].m_vNoiseUVSpeed,
			spMeshEffectDataGroup->m_vecNoiseProperties[iIndex].m_vNoiseMaxUV
		);

		spEffectMeshData->SetColorProperty
		(
			spMeshEffectDataGroup->m_vecColorProperties[iIndex].m_vStartColor,
			spMeshEffectDataGroup->m_vecColorProperties[iIndex].m_vFinishColor
		);

		spEffectMeshData->SetTransformProperty
		(
			spMeshEffectDataGroup->m_vecTransformProperties[iIndex].m_vStartScale,
			spMeshEffectDataGroup->m_vecTransformProperties[iIndex].m_vStartRotate,
			spMeshEffectDataGroup->m_vecTransformProperties[iIndex].m_vStartTranslate,
			spMeshEffectDataGroup->m_vecTransformProperties[iIndex].m_vFinishScale,
			spMeshEffectDataGroup->m_vecTransformProperties[iIndex].m_vFinishRotate,
			spMeshEffectDataGroup->m_vecTransformProperties[iIndex].m_vFinishTranslate
		);

		spEffectMeshData->SetUVProperty
		(
			spMeshEffectDataGroup->m_vecUVProperties[iIndex].m_bUseEffectUV,
			spMeshEffectDataGroup->m_vecUVProperties[iIndex].m_vEffectStartUV,
			spMeshEffectDataGroup->m_vecUVProperties[iIndex].m_vEffectFinishUV
		);
		
		spEffectMeshData->ChangeEffectModelDesc(spMeshEffectDataGroup->m_vecEffectModelDescNames[iIndex]);

		wstring wstrVSDescName = spMeshEffectDataGroup->m_vecVSDescNames[iIndex];
		wstring wstrPSDescName = spMeshEffectDataGroup->m_vecPSDescNames[iIndex];

		spEffectMeshData->ChangeShaders(dynamic_pointer_cast<CSceneComponent>(shared_from_this()), wstrVSDescName, wstrPSDescName);

		if (spMeshEffectDataGroup->m_vecMaskProperties[iIndex].m_bUseMask)
		{
			spEffectMeshData->ModifyPixelShaderTexture(0, 0, spMeshEffectDataGroup->m_vecMaskProperties[iIndex].m_wstrMaskTextureName);
		}
		if (spMeshEffectDataGroup->m_vecNoiseProperties[iIndex].m_bUseNoise)
		{
			spEffectMeshData->ModifyPixelShaderTexture(0, 1, spMeshEffectDataGroup->m_vecNoiseProperties[iIndex].m_wstrNoiseTextureName);
		}
	
		AddMeshEffect(spMeshEffectDataGroup->m_vecMeshEffectDataNames[iIndex], spEffectMeshData);
	}

	return S_OK;
}

void Engine::CEffectComponent::PlayMeshEffect()
{
	for (const auto& pair : m_umapEffectMeshData)
	{
		pair.second->SetEffectMeshDataState(EEffectMeshDataState::PLAY);
	}
}

void Engine::CEffectComponent::StopMeshEffect()
{
	for (const auto& pair : m_umapEffectMeshData)
	{
		pair.second->SetEffectMeshDataState(EEffectMeshDataState::STOP);
	}
}

void Engine::CEffectComponent::ResetMeshEffect()
{
	for (const auto& pair : m_umapEffectMeshData)
	{
		pair.second->SetEffectMeshDataState(EEffectMeshDataState::RESET);
	}
}

void Engine::CEffectComponent::OffMeshEffect()
{
	for (const auto& pair : m_umapEffectMeshData)
	{
		pair.second->SetEffectMeshDataState(EEffectMeshDataState::OFF);
	}
}

HRESULT Engine::CEffectComponent::AddParticleEffect(const std::wstring& _wstrParticleEffectName, const std::shared_ptr<CEffectParticleData>& _spEffectParticleData)
{
	if (m_umapEffectParticleData.find(_wstrParticleEffectName) != m_umapEffectParticleData.end()) { return E_FAIL; }

	m_umapEffectParticleData.insert({ _wstrParticleEffectName, _spEffectParticleData });
	return S_OK;
}

HRESULT Engine::CEffectComponent::RemoveParticleEffect(const std::wstring& _wstrParticleEffectName)
{
	if (m_umapEffectParticleData.find(_wstrParticleEffectName) == m_umapEffectParticleData.end()) { return E_FAIL; }

	m_umapEffectParticleData.erase(_wstrParticleEffectName);
	return S_OK;
}

HRESULT Engine::CEffectComponent::CreateParticleEffectDataGroup
(
	const std::wstring& _wstrParticleEffectGroupName,
	FParticlePlayEffectProperty _tParticlePlayProperty,
	FParticleTransformEffectProperty _tParticleTransformProperty,
	FParticleSizeEffectProperty _tParticleSizeProperty,
	FParticleMaskEffectProperty _tParticleMaskProperty,
	FParticleColorEffectProperty _tParticleColorProperty
)
{
	shared_ptr<CEffectParticleData> spEffectParticleData = CEffectParticleData::Create
	(
		dynamic_pointer_cast<CSceneComponent>(shared_from_this()),
		_tParticleTransformProperty.m_iNumInstances,
		{ _tParticleMaskProperty.m_wstrParticleMaskTextureName },
		L"InstancePoint",
		L"VS_InstancePoint",
		L"PS_InstancePoint",
		L"GS_InstancePoint"
	);

	spEffectParticleData->SetPlayProperty(_tParticlePlayProperty);
	spEffectParticleData->SetTransformProperty(_tParticleTransformProperty);
	spEffectParticleData->SetSizeProperty(_tParticleSizeProperty);
	spEffectParticleData->SetMaskProperty(_tParticleMaskProperty);
	spEffectParticleData->SetColorProperty(_tParticleColorProperty);

	// 그룹으로 전달해야 하나, 시간이 없어서 한 파티클 이펙트만 생성합니다.
	return AddParticleEffect(_wstrParticleEffectGroupName, spEffectParticleData);
}

void Engine::CEffectComponent::PlayParticleEffect()
{
	for (const auto& pair : m_umapEffectParticleData)
	{
		pair.second->SetEffectParticleDataState(EEffectParticleDataState::PLAY);
	}
}

void Engine::CEffectComponent::StopParticleEffect()
{
	for (const auto& pair : m_umapEffectParticleData)
	{
		pair.second->SetEffectParticleDataState(EEffectParticleDataState::STOP);
	}
}

void Engine::CEffectComponent::ResetParticleEffect()
{
	for (const auto& pair : m_umapEffectParticleData)
	{
		pair.second->SetEffectParticleDataState(EEffectParticleDataState::RESET);
	}
}

void Engine::CEffectComponent::OffParticleEffect()
{
	for (const auto& pair : m_umapEffectParticleData)
	{
		pair.second->SetEffectParticleDataState(EEffectParticleDataState::OFF);
	}
}
