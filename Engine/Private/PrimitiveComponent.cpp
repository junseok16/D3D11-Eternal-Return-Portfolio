// default
#include "pch.h"
#include "PrimitiveComponent.h"

HRESULT Engine::CPrimitiveComponent::PreInitializeComponent()
{
	if (FAILED(CSceneComponent::PreInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CPrimitiveComponent::InitializeComponent()
{
	if (FAILED(CSceneComponent::InitializeComponent())) { return E_FAIL; }
	return S_OK;
}

HRESULT Engine::CPrimitiveComponent::PostInitializeComponent()
{
	if (FAILED(CSceneComponent::PostInitializeComponent())) { return E_FAIL; }
	return S_OK;
}

HRESULT Engine::CPrimitiveComponent::BeginPlay()
{
	if (FAILED(CSceneComponent::BeginPlay())) { return E_FAIL; }
	return S_OK;
}

int32 Engine::CPrimitiveComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CPrimitiveComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CPrimitiveComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CPrimitiveComponent::EndPlay()
{
	if (FAILED(CSceneComponent::EndPlay())) { return E_FAIL; }
	return S_OK;
}

void Engine::CPrimitiveComponent::Render()
{
	CSceneComponent::Render();
}

void Engine::CPrimitiveComponent::Release()
{
	CSceneComponent::Release();
}
