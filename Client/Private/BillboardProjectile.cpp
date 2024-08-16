#include "pch.h"
#include "BillboardProjectile.h"

#include "GeometryComponent.h"

#include "SphereComponent.h"
#include "EffectComponent.h"

HRESULT Client::CBillboardProjectile::PreInitialize()
{
	m_wpGeometryComponent = CreateActorComponent<CGeometryComponent>(L"GeometryComponent", EComponentType::GEOMETRY);
	SetRootComponent(m_wpGeometryComponent.lock());

	m_wpGeometryComponent.lock()->SetPrimitiveType(EPrimitiveType::POINT);
	m_wpGeometryComponent.lock()->SetTextureNames({ L"FireBall" });
	m_wpGeometryComponent.lock()->SetVertexShaderDesc(L"VS_BillboardProjectile");
	m_wpGeometryComponent.lock()->SetPixelShaderDesc(L"PS_BillboardProjectile");
	m_wpGeometryComponent.lock()->SetGeometryShaderDesc(L"GS_BillboardProjectile");

	m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
	m_wpSphereComponent.lock()->SetOwnerComponent(m_wpGeometryComponent.lock());

	wstring strName = L"WicklineProjectile" + to_wstring(m_iProjectileIndex);
	m_wpEffectComponent = CreateActorComponent<CEffectComponent>(strName + L"EffectComponent", EComponentType::EFFECT);
	m_wpEffectComponent.lock()->SetOwnerComponent(m_wpGeometryComponent.lock());

	return CProjectile::PreInitialize();
}

HRESULT Client::CBillboardProjectile::Initialize()
{
	if (FAILED(CProjectile::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBillboardProjectile::PostInitialize()
{
	if (FAILED(CProjectile::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CBillboardProjectile::BeginPlay()
{
	if (FAILED(CProjectile::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CBillboardProjectile::PreTick(float _fDeltaSeconds)
{
	switch (CProjectile::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBillboardProjectile::Tick(float _fDeltaSeconds)
{
	switch (CProjectile::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CBillboardProjectile::PostTick(float _fDeltaSeconds)
{
	switch (CProjectile::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CBillboardProjectile::EndPlay()
{
	if (FAILED(CProjectile::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CBillboardProjectile::Render()
{
	CProjectile::Render();
}

void Client::CBillboardProjectile::Release()
{
	CProjectile::Release();
}
