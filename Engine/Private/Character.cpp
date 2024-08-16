// default
#include "pch.h"
#include "Character.h"

// controller
#include "Controller.h"

// component
#include "CameraComponent.h"
#include "InputComponent.h"
#include "StaticMeshComponent.h"

HRESULT Engine::CCharacter::PreInitialize()
{
	return S_OK;
}

HRESULT Engine::CCharacter::Initialize()
{
	if (FAILED(CPawn::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CCharacter::PostInitialize()
{
	if (FAILED(CPawn::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CCharacter::BeginPlay()
{
	if (FAILED(CPawn::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CCharacter::PreTick(float _fDeltaSeconds)
{
	switch (CPawn::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

int32 Engine::CCharacter::Tick(float _fDeltaSeconds)
{
	switch (CPawn::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

int32 Engine::CCharacter::PostTick(float _fDeltaSeconds)
{
	switch (CPawn::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return S_OK;
}

HRESULT Engine::CCharacter::EndPlay()
{
	CPawn::EndPlay();

	return S_OK;
}

void Engine::CCharacter::Render()
{
	CPawn::Render();
}

void Engine::CCharacter::Release()
{
	CPawn::Release();
}
