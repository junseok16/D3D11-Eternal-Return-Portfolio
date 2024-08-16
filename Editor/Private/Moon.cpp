#include "pch.h"
#include "Moon.h"

#include "LightComponent.h"

HRESULT Editor::CMoon::PreInitialize()
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

HRESULT Editor::CMoon::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CMoon::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CMoon::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CMoon::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CMoon::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CMoon::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Editor::CMoon::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CMoon::Render()
{
	CActor::Render();
}

void Editor::CMoon::Release()
{
	CActor::Release();
}
