#include "pch.h"
#include "BillboardProjectile.h"

#include "GeometryComponent.h"

HRESULT Editor::CBillboardProjectile::PreInitialize()
{
	m_wpGeometryComponent = CreateActorComponent<CGeometryComponent>(L"GeometryComponent", EComponentType::GEOMETRY);
	SetRootComponent(m_wpGeometryComponent.lock());

	m_wpGeometryComponent.lock()->SetPrimitiveType(EPrimitiveType::POINT);
	m_wpGeometryComponent.lock()->SetTextureNames({ L"FireBall" });
	m_wpGeometryComponent.lock()->SetVertexShaderDesc(L"VS_BillboardProjectile");
	m_wpGeometryComponent.lock()->SetPixelShaderDesc(L"PS_BillboardProjectile");
	m_wpGeometryComponent.lock()->SetGeometryShaderDesc(L"GS_BillboardProjectile");

	return CProjectile::PreInitialize();
}

HRESULT Editor::CBillboardProjectile::Initialize()
{
	if (FAILED(CProjectile::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CBillboardProjectile::PostInitialize()
{
	if (FAILED(CProjectile::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CBillboardProjectile::BeginPlay()
{
	if (FAILED(CProjectile::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CBillboardProjectile::PreTick(float _fDeltaSeconds)
{
	switch (CProjectile::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CBillboardProjectile::Tick(float _fDeltaSeconds)
{
	switch (CProjectile::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CBillboardProjectile::PostTick(float _fDeltaSeconds)
{
	switch (CProjectile::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CBillboardProjectile::EndPlay()
{
	if (FAILED(CProjectile::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CBillboardProjectile::Render()
{
	CProjectile::Render();
}

void Editor::CBillboardProjectile::Release()
{
	CProjectile::Release();
}
