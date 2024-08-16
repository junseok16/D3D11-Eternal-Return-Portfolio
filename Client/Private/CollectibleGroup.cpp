#include "pch.h"
#include "CollectibleGroup.h"

#include "StaticMeshComponent.h"

HRESULT Client::CCollectibleGroup::PreInitialize()
{
	m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
	SetRootComponent(m_wpStaticMeshComponent.lock());

	return CActor::PreInitialize();
}

HRESULT Client::CCollectibleGroup::Initialize()
{
	wstring wstrLocationName = L"";
	switch (m_eLocationType)
	{
	case Client::ELocationType::ALLEY1x1:	wstrLocationName = L"Alley";		break;
	case Client::ELocationType::ARCHERY1x1:	wstrLocationName = L"Archery";		break;
	case Client::ELocationType::CEMETERY:	wstrLocationName = L"Cemetery";		break;
	case Client::ELocationType::CHURCH:		wstrLocationName = L"Church";		break;
	case Client::ELocationType::DOWNTOWN:	wstrLocationName = L"Downtown";		break;
	case Client::ELocationType::FACTORY:	wstrLocationName = L"Factory";		break;
	case Client::ELocationType::FOREST1x1:	wstrLocationName = L"Forest";		break;
	case Client::ELocationType::HARBOR:		wstrLocationName = L"Harbor";		break;
	case Client::ELocationType::HOSPITAL:	wstrLocationName = L"Hospital";		break;
	case Client::ELocationType::HOTEL:		wstrLocationName = L"Hotel";		break;
	case Client::ELocationType::LABORATORY:	wstrLocationName = L"Labatory";		break;
	case Client::ELocationType::POND:		wstrLocationName = L"Pond";			break;
	case Client::ELocationType::SANDY_BEACH:wstrLocationName = L"SandyBeach";	break;
	case Client::ELocationType::SCHOOL1x1:	wstrLocationName = L"School";		break;
	case Client::ELocationType::UPTOWN:		wstrLocationName = L"Uptown";		break;
	case Client::ELocationType::ENUM_END:	break;
	default:								break;
	}

	wstring wstrCollectibleName = L"";
	switch (m_eCollectibleType)
	{
	case Client::ECollectibleType::ITEM_SPOT:	wstrCollectibleName = L"ItemSpot";			break;
	case Client::ECollectibleType::BRANCH:		wstrCollectibleName = L"CollectibleBranch";	break;
	case Client::ECollectibleType::STONE:		wstrCollectibleName = L"CollectibleStone";	break;
	case Client::ECollectibleType::POTATO:		wstrCollectibleName = L"CollectiblePotato"; break;
	case Client::ECollectibleType::WATER:		wstrCollectibleName = L"CollectibleWater"; break;
	case Client::ECollectibleType::ENUM_END:	break;
	default:									break;
	}

	wstring wstrModelDescName = wstrLocationName + wstrCollectibleName;
	m_wpStaticMeshComponent.lock()->SetModelDesc(wstrModelDescName);
	m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
	m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh");
	return CActor::Initialize();
}

HRESULT Client::CCollectibleGroup::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CCollectibleGroup::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CCollectibleGroup::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CCollectibleGroup::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CCollectibleGroup::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CCollectibleGroup::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CCollectibleGroup::Render()
{
	return CActor::Render();
}

void Client::CCollectibleGroup::Release()
{
	return CActor::Release();
}

void Client::CCollectibleGroup::AddCollectible(const shared_ptr<CCollectible>& _spCollectible)
{
	m_vecCollectibles.push_back(_spCollectible);
}
