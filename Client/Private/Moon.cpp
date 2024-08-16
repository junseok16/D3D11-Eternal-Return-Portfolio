#include "pch.h"
#include "Moon.h"

#include "LightComponent.h"

HRESULT Client::CMoon::PreInitialize()
{
	m_wpLightComponent = CreateActorComponent<CLightComponent>(L"Moon", EComponentType::DIRECTIONAL_LIGHT);
	SetRootComponent(m_wpLightComponent.lock());

	TLightDesc tLightDesc
	{
		ELightType::DIRECTIONAL,
		{ 0.6f, 0.6f, 0.6f },
		10.0f,
		Vector3::One,
		0.0f,
		Vector3::Zero,
		10.0f,
		{ 0.0f, 100.0f, 0.0f },
		1.0f,
		Vector3::Down,
		Vector3::One,
	};

	m_wpLightComponent.lock()->SetLightDesc(tLightDesc);

	SetActorRenderType(ERenderType::NOT_RENDER);
	return CActor::PreInitialize();
}

HRESULT Client::CMoon::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CMoon::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CMoon::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CMoon::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CMoon::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CMoon::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CMoon::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CMoon::Render()
{
	CActor::Render();
}

void Client::CMoon::Release()
{
	CActor::Release();
}
