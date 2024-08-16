#include "pch.h"
#include "CollectibleGroup.h"

#include "StaticMeshComponent.h"

HRESULT Editor::CCollectibleGroup::PreInitialize()
{
	m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
	SetRootComponent(m_wpStaticMeshComponent.lock());

	return CActor::PreInitialize();
}

HRESULT Editor::CCollectibleGroup::Initialize()
{
	wstring wstrLocationName = L"";
	switch (m_eLocationType)
	{
	case Editor::ELocationType::ALLEY1x1:	wstrLocationName = L"Alley";		break;
	case Editor::ELocationType::ARCHERY1x1:	wstrLocationName = L"Archery";		break;
	case Editor::ELocationType::CEMETERY:	wstrLocationName = L"Cemetery";		break;
	case Editor::ELocationType::CHURCH:		wstrLocationName = L"Church";		break;
	case Editor::ELocationType::DOWNTOWN:	wstrLocationName = L"Downtown";		break;
	case Editor::ELocationType::FACTORY:	wstrLocationName = L"Factory";		break;
	case Editor::ELocationType::FOREST1x1:	wstrLocationName = L"Forest";		break;
	case Editor::ELocationType::HARBOR:		wstrLocationName = L"Harbor";		break;
	case Editor::ELocationType::HOSPITAL:	wstrLocationName = L"Hospital";		break;
	case Editor::ELocationType::HOTEL:		wstrLocationName = L"Hotel";		break;
	case Editor::ELocationType::LABORATORY:	wstrLocationName = L"Labatory";		break;
	case Editor::ELocationType::POND:		wstrLocationName = L"Pond";			break;
	case Editor::ELocationType::SANDY_BEACH:wstrLocationName = L"SandyBeach";	break;
	case Editor::ELocationType::SCHOOL1x1:	wstrLocationName = L"School";		break;
	case Editor::ELocationType::UPTOWN:		wstrLocationName = L"Uptown";		break;
	case Editor::ELocationType::ENUM_END:	break;
	default:								break;
	}

	wstring wstrCollectibleName = L"";
	switch (m_eCollectibleType)
	{
	case Editor::ECollectibleType::ITEM_SPOT:	wstrCollectibleName = L"ItemSpot";			break;
	case Editor::ECollectibleType::BRANCH:		wstrCollectibleName = L"CollectibleBranch";	break;
	case Editor::ECollectibleType::STONE:		wstrCollectibleName = L"CollectibleStone";	break;
	case Editor::ECollectibleType::POTATO:		wstrCollectibleName = L"CollectiblePotato"; break;
	case Editor::ECollectibleType::WATER:		wstrCollectibleName = L"CollectibleWater"; break;
	case Editor::ECollectibleType::ENUM_END:	break;
	default:									break;
	}

	wstring wstrModelDescName = wstrLocationName + wstrCollectibleName;
	m_wpStaticMeshComponent.lock()->SetModelDesc(wstrModelDescName);
	m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
	m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_StaticMesh");
	return CActor::Initialize();
}

HRESULT Editor::CCollectibleGroup::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CCollectibleGroup::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CCollectibleGroup::PreTick(float _fDeltaSeconds)
{
	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CCollectibleGroup::Tick(float _fDeltaSeconds)
{
	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Editor::CCollectibleGroup::PostTick(float _fDeltaSeconds)
{
	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Editor::CCollectibleGroup::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CCollectibleGroup::Render()
{
	return CActor::Render();
}

void Editor::CCollectibleGroup::Release()
{
	return CActor::Release();
}

void Editor::CCollectibleGroup::AddCollectible(const shared_ptr<CCollectible>& _spCollectible)
{
	m_vecCollectibles.push_back(_spCollectible);
}
