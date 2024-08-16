#include "pch.h"
#include "Sun.h"

#include "LightComponent.h"

HRESULT Editor::CSun::PreInitialize()
{
	m_wpLightComponent = CreateActorComponent<CLightComponent>(L"SunLightComponent", EComponentType::DIRECTIONAL_LIGHT);
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

HRESULT Editor::CSun::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSun::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CSun::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CSun::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CSun::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CSun::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CSun::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CSun::Render()
{
	CActor::Render();
}

void Editor::CSun::Release()
{
	CActor::Release();
}
