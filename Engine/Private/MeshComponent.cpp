// default
#include "pch.h"
#include "MeshComponent.h"

HRESULT Engine::CMeshComponent::PreInitializeComponent()
{
	if (FAILED(CPrimitiveComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CMeshComponent::InitializeComponent()
{
	if (FAILED(CPrimitiveComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CMeshComponent::PostInitializeComponent()
{
	if (FAILED(CPrimitiveComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CMeshComponent::BeginPlay()
{
	if (FAILED(CPrimitiveComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CMeshComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CPrimitiveComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CMeshComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CPrimitiveComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CMeshComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CPrimitiveComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CMeshComponent::EndPlay()
{
	if (FAILED(CPrimitiveComponent::EndPlay())) { return E_FAIL; }

	return 0;
}

void Engine::CMeshComponent::Render()
{
	CPrimitiveComponent::Render();
}

void Engine::CMeshComponent::Release()
{
	CPrimitiveComponent::Release();
}
