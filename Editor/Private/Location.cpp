#include "pch.h"
#include "Location.h"

#include "StaticMeshComponent.h"

HRESULT Editor::CLocation::PreInitialize()
{
	m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
	SetRootComponent(m_wpStaticMeshComponent.lock());

	return CActor::PreInitialize();
}

HRESULT Editor::CLocation::Initialize()
{
	switch (m_eLocationType)
	{
	case Editor::ELocationType::ALLEY1x1:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"AlleyLocation1x1");	break;
	case Editor::ELocationType::ARCHERY1x1:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"ArcheryLocation1x1");break;
	case Editor::ELocationType::CEMETERY:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"CemeteryLocation");	break;
	case Editor::ELocationType::CHURCH:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"ChurchLocation");	break;
	case Editor::ELocationType::DOWNTOWN:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"DowntownLocation");	break;
	case Editor::ELocationType::FACTORY:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"FactoryLocation");	break;
	case Editor::ELocationType::FOREST1x1:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"ForestLocation1x1");	break;
	case Editor::ELocationType::HARBOR:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"HarborLocation");	break;
	case Editor::ELocationType::HOSPITAL:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"HospitalLocation");	break;
	case Editor::ELocationType::HOTEL:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"HotelLocation");		break;
	case Editor::ELocationType::LABORATORY:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"LaboratoryLocation");break;
	case Editor::ELocationType::POND:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"PondLocation");		break;
	case Editor::ELocationType::SANDY_BEACH:m_wpStaticMeshComponent.lock()->SetModelDesc(L"SandyBeachLocation");break;
	case Editor::ELocationType::SCHOOL1x1:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"SchoolLocation1x1");	break;
	case Editor::ELocationType::UPTOWN:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"UptownLocation");	break;
	case Editor::ELocationType::ENUM_END:	break;
	default:								break;
	}

	m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
	m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh");
	return CActor::Initialize();
}

HRESULT Editor::CLocation::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CLocation::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CLocation::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CLocation::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CLocation::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CLocation::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CLocation::Render()
{
	CActor::Render();
}

void Editor::CLocation::Release()
{
	CActor::Release();
}
