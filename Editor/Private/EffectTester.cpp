#include "pch.h"
#include "EffectTester.h"

#include "EffectComponent.h"
#include "StaticMeshComponent.h"

HRESULT Editor::CEffectTester::PreInitialize()
{
	{
		m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticComponent", EComponentType::STATIC_MESH);
		SetRootComponent(m_wpStaticMeshComponent.lock());

		m_wpEffectComponent = CreateActorComponent<CEffectComponent>(L"EffectComponent", EComponentType::EFFECT);
		m_wpEffectComponent.lock()->SetOwnerComponent(m_wpStaticMeshComponent.lock());
	}

	{
		m_wpStaticMeshComponent.lock()->SetModelDesc(L"EffectTest");
		m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
		m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_EffectTester");
	}
	return CActor::PreInitialize();
}

HRESULT Editor::CEffectTester::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }
	
	return S_OK;
}

HRESULT Editor::CEffectTester::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CEffectTester::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CEffectTester::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CEffectTester::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CEffectTester::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CEffectTester::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CEffectTester::Render()
{
	CActor::Render();
}

void Editor::CEffectTester::Release()
{
	CActor::Release();
}
