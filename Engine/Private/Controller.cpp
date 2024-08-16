#include "pch.h"
#include "Controller.h"

#include "Pawn.h"
#include "InputComponent.h"
#include "CameraComponent.h"

HRESULT Engine::CController::PreInitialize()
{
	if (FAILED(CActor::PreInitialize())) { return E_FAIL; }
	m_wpInputComponent = CreateActorComponent<CInputComponent>(L"InputComponent", EComponentType::INPUT);

	return S_OK;
}

HRESULT Engine::CController::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CController::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CController::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CController::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	case 0:		break;
	default:	break;
	}

	return 0;
}

int32 Engine::CController::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	case 0:		break;
	default:	break;
	}


	return 0;
}

int32 Engine::CController::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	case 0:		break;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CController::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CController::Render()
{
	CActor::Render();
}

void Engine::CController::Release()
{
	CActor::Release();
}

void Engine::CController::AddPitchInput(float _fValue)
{
}

void Engine::CController::AddRollInput(float _fValue)
{
}

void Engine::CController::AddYawInput(float _fValue)
{
}

bool Engine::CController::Possess(const shared_ptr<CPawn> _spPawn)
{
	if (!_spPawn) { return false; }

	m_wpPawn = _spPawn;
	_spPawn->GetCameraComponent()->SetThisCameraOnAir();
	_spPawn->SetController(static_pointer_cast<CController>(shared_from_this()));
	_spPawn->SetPossessed(true);
	return true;
}

bool Engine::CController::UnPossess()
{
	if (m_wpPawn.expired()) { return false; }
	m_wpPawn.lock()->SetController(nullptr);
	m_wpPawn.lock()->SetPossessed(false);
	m_wpPawn.reset();

	m_wpInputComponent.lock()->ClearKeyAction();
	m_wpInputComponent.lock()->ClearKeyAxis();
	return true;
}

void Engine::CController::EnableInput()
{
	m_wpInputComponent.lock()->EnableInput();
}

void Engine::CController::DisableInput()
{
	m_wpInputComponent.lock()->DisableInput();
}