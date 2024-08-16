#include "pch.h"
#include "SkeletalMeshComponent.h"

#include "SkeletalMeshData.h"
#include "AnimData.h"

HRESULT Engine::CSkeletalMeshComponent::PreInitializeComponent()
{
	if (FAILED(CMeshComponent::PreInitializeComponent())) { return E_FAIL; }
	m_spSkeletalMeshData = CSkeletalMeshData::Create(static_pointer_cast<CSceneComponent>(shared_from_this()), m_wstrSkeletalModelDesc, m_wstrVertexShaderDesc, m_wstrPixelShaderDesc);
	m_spAnimData = CAnimData::Create(GetOwnerActor());

	m_spSkeletalMeshData->SetAnimData(m_spAnimData);
	m_spAnimData->SetSkeletalMeshData(m_spSkeletalMeshData);
	return S_OK;
}

HRESULT Engine::CSkeletalMeshComponent::InitializeComponent()
{
	if (FAILED(CMeshComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSkeletalMeshComponent::PostInitializeComponent()
{
	if (FAILED(CMeshComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSkeletalMeshComponent::BeginPlay()
{
	if (FAILED(CMeshComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CSkeletalMeshComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CSkeletalMeshComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_spAnimData->Tick(_fDeltaSeconds);
	return 0;
}

int32 Engine::CSkeletalMeshComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CMeshComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	m_spSkeletalMeshData->Tick(_fDeltaSeconds);
	return 0;
}

HRESULT Engine::CSkeletalMeshComponent::EndPlay()
{
	if (FAILED(CMeshComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CSkeletalMeshComponent::Render()
{
	CMeshComponent::Render();
	m_spSkeletalMeshData->Render();
}

void Engine::CSkeletalMeshComponent::RenderShadow()
{
	CActorComponent::RenderShadow();

	// m_spSkeletalMeshData->RenderShadow();
}

void Engine::CSkeletalMeshComponent::Release()
{
	m_spSkeletalMeshData->Release();
	m_spSkeletalMeshData = nullptr;

	m_spAnimData->Release();
	m_spAnimData = nullptr;

	CMeshComponent::Release();
}

HRESULT Engine::CSkeletalMeshComponent::AddAnimState(uint32 _iAnimState, const wstring& _wstrAnimStateName, const std::vector<std::string>& _vecAnimationNames, bool _bLoop)
{
	return m_spAnimData->AddAnimState(_iAnimState, _wstrAnimStateName, _vecAnimationNames, _bLoop);
}

std::shared_ptr<CBone> Engine::CSkeletalMeshComponent::FindBone(const std::string& _strBoneName)
{
	return m_spSkeletalMeshData->FindBone(_strBoneName);
}

void Engine::CSkeletalMeshComponent::SetPlayRate(float _fPlayRate)
{
	m_spSkeletalMeshData->SetPlayRate(_fPlayRate);
}

void Engine::CSkeletalMeshComponent::PlayAnimation()
{
	m_bPlayAnimation = true;
	m_spSkeletalMeshData->PlayAnimation();
}

void Engine::CSkeletalMeshComponent::StopAnimation()
{
	m_bPlayAnimation = false;
	m_spSkeletalMeshData->StopAnimation();
}
