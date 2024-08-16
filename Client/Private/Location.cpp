#include "pch.h"
#include "Location.h"

#include "StaticMeshComponent.h"

HRESULT Client::CLocation::PreInitialize()
{
	m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
	SetRootComponent(m_wpStaticMeshComponent.lock());

	return CActor::PreInitialize();
}

HRESULT Client::CLocation::Initialize()
{
	switch (m_eLocationType)
	{
	case Client::ELocationType::ALLEY1x1:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"AlleyLocation1x1");		break;
	case Client::ELocationType::ALLEY10x10:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"AlleyLocation10x10");	break;
	case Client::ELocationType::ARCHERY1x1:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"ArcheryLocation1x1");	break;
	case Client::ELocationType::ARCHERY10x10:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"ArcheryLocation10x10");	break;

	case Client::ELocationType::CEMETERY:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"CemeteryLocation");		break;
	case Client::ELocationType::CHURCH:			m_wpStaticMeshComponent.lock()->SetModelDesc(L"ChurchLocation");		break;
	case Client::ELocationType::DOWNTOWN:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"DowntownLocation");		break;
	case Client::ELocationType::FACTORY:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"FactoryLocation");		break;
	case Client::ELocationType::FOREST1x1:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"ForestLocation1x1");		break;
	case Client::ELocationType::FOREST10x10:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"ForestLocation10x10");	break;
	case Client::ELocationType::HARBOR:			m_wpStaticMeshComponent.lock()->SetModelDesc(L"HarborLocation");		break;
	case Client::ELocationType::HOSPITAL:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"HospitalLocation");		break;
	case Client::ELocationType::HOTEL:			m_wpStaticMeshComponent.lock()->SetModelDesc(L"HotelLocation");			break;
	case Client::ELocationType::LABORATORY:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"LaboratoryLocation");	break;
	case Client::ELocationType::POND:			m_wpStaticMeshComponent.lock()->SetModelDesc(L"PondLocation");			break;
	case Client::ELocationType::SANDY_BEACH:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"SandyBeachLocation");	break;
	case Client::ELocationType::SCHOOL1x1:		m_wpStaticMeshComponent.lock()->SetModelDesc(L"SchoolLocation1x1");		break;
	case Client::ELocationType::SCHOOL10x10:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"SchoolLocation10x10");	break;
	case Client::ELocationType::TEMPLE:			m_wpStaticMeshComponent.lock()->SetModelDesc(L"TempleLocation");		break;
	case Client::ELocationType::UPTOWN:			m_wpStaticMeshComponent.lock()->SetModelDesc(L"UptownLocation");		break;

	case Client::ELocationType::ALLEY_GREEN:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"AlleyGreen");			break;
	case Client::ELocationType::SCHOOL_GREEN:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"SchoolGreen");			break;
	case Client::ELocationType::HOTEL_GREEN:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"HotelGreen");			break;
	case Client::ELocationType::FOREST_GREEN:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"ForestGreen");			break;
	case Client::ELocationType::ARCHERY_GREEN:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"ArcheryGreen");			break;
	case Client::ELocationType::DOWNTOWN_GREEN:	m_wpStaticMeshComponent.lock()->SetModelDesc(L"DowntownGreen");			break;

	case Client::ELocationType::ENUM_END:		break;
	default:									break;
	}

	switch (m_eLocationType)
	{
	case Client::ELocationType::FOREST10x10:
	case Client::ELocationType::SCHOOL10x10:
	case Client::ELocationType::ARCHERY10x10:
		m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh10x10");
		break;

	default:
		m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh");
		break;
	}

	m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
	return CActor::Initialize();
}

HRESULT Client::CLocation::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CLocation::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CLocation::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CLocation::Tick(float _fDeltaSeconds)
{
	if (!m_bInitialized) { m_bInitialized = true; }
	else { return 0; }

	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CLocation::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CLocation::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CLocation::Render()
{
	CActor::Render();
}

void Client::CLocation::Release()
{
	CActor::Release();
}
