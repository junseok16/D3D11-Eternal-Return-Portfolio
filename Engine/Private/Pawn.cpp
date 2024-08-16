// default;
#include "pch.h"
#include "Pawn.h"

// controller
#include "Controller.h"

// component
#include "CameraComponent.h"
#include "InputComponent.h"
#include "MeshComponent.h"

HRESULT Engine::CPawn::PreInitialize()
{
	return CActor::PreInitialize();
}

HRESULT Engine::CPawn::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CPawn::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CPawn::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CPawn::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

int32 Engine::CPawn::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

int32 Engine::CPawn::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

HRESULT Engine::CPawn::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CPawn::Render()
{
	CActor::Render();
}

void Engine::CPawn::Release()
{
	CActor::Release();
}
