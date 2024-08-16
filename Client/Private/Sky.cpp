#include "pch.h"
#include "Sky.h"

#include "CubeComponent.h"

#include "Controller.h"

#include "World.h"
#include "Level.h"
#include "Pawn.h"

#include "LerpConstantBuffer.h"

#include "GameManager.h"

HRESULT Client::CSky::PreInitialize()
{
	{
		m_wpSkyboxCubeComponent = CreateActorComponent<CCubeComponent>(L"CubeComponent", EComponentType::CUBE);
		SetRootComponent(m_wpSkyboxCubeComponent.lock());

		m_wpSkyboxCubeComponent.lock()->SetPrimitiveDesc({ L"DaySkybox", L"NightSkybox" });
		m_wpSkyboxCubeComponent.lock()->SetVertexShaderDesc(L"VS_Cube");
		m_wpSkyboxCubeComponent.lock()->SetPixelShaderDesc(L"PS_Cube");
	}

	SetActorRenderType(ERenderType::PRE_RENDER);
	return CActor::PreInitialize();
}

HRESULT Client::CSky::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CSky::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CSky::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	m_wpPosessedPawn = CWorld::GetInstance()->GetCurLevel()->GetController()->GetPawn();
	SetActorLocalScale({ 500.0f, 500.0f, 500.0f });
	return S_OK;
}

int32 Client::CSky::PreTick(float _fDeltaSeconds)
{
	m_fDayTime = CGameManager::GetInstance()->GetDayTime();
	m_fNightTime = CGameManager::GetInstance()->GetNightTime();
	m_iDayNightType = (int32)CGameManager::GetInstance()->GetDayType();

	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CSky::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	
	return 0;
}

int32 Client::CSky::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	Vector3 vPosition = m_wpPosessedPawn.lock()->GetActorWorldPosition().value();
	SetActorLocalPosition(vPosition);
	return 0;
}

HRESULT Client::CSky::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CSky::Render()
{
	CActor::Render();
}

void Client::CSky::Release()
{
	CActor::Release();
}
