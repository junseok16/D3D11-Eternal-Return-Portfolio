#include "pch.h"
#include "Craft.h"

#include "StaticMeshComponent.h"
#include "SkeletalMeshComponent.h"
#include "CraftStateComponent.h"

HRESULT Client::CCraft::PreInitialize()
{
	{
		m_wpSkeletalMeshComponent = CreateActorComponent<CSkeletalMeshComponent>(L"SkeletalMeshComponent", EComponentType::SKELETAL_MESH);
		SetRootComponent(m_wpSkeletalMeshComponent.lock());

		wstring wstrCraftType = L"";
		switch (m_eCraftType)
		{
		case Client::ECraftType::METAL:	wstrCraftType = L"CraftMetal";	break;
		case Client::ECraftType::FOOD:	wstrCraftType = L"CraftFood";	break;
		default: CHECKF(false, L"Craft type is not designated.");		break;
		}

		m_wpSkeletalMeshComponent.lock()->SetModelDesc(wstrCraftType);
		m_wpSkeletalMeshComponent.lock()->SetVertexShaderDesc(L"VS_SkeletalMesh");
		m_wpSkeletalMeshComponent.lock()->SetPixelShaderDesc(L"PS_SkeletalMesh");
	}

	{
		m_wpCraftStateComponent = CreateActorComponent<CCraftStateComponent>(L"StateComponent", EComponentType::STATE);
	}

	return CSocket::PreInitialize();
}

HRESULT Client::CCraft::Initialize()
{
	if (FAILED(CSocket::Initialize())) { return E_FAIL; }

	switch (m_eCraftType)
	{
	case Client::ECraftType::METAL:
	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ECraftAnimState::CRAFT_METAL_BEGIN,
			L"CRAFT_METAL_BEGIN",
			{ "Craft_metal_appear" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ECraftAnimState::CRAFT_METAL,
			L"CRAFT_METAL",
			{ "Craft_metal_craft" },
			false
		);

		// SetActorLocalRotate(Vector3::UnitX, -5.0f);
		// SetActorLocalPosition({ 0.22f, -0.39f, 0.6f });
	}
	break;

	case Client::ECraftType::FOOD:
	{
		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ECraftAnimState::CRAFT_FOOD_BEGIN,
			L"CRAFT_FOOD_BEGIN",
			{ "Craft_food_appear" },
			false
		);

		m_wpSkeletalMeshComponent.lock()->AddAnimState
		(
			(uint32)ECraftAnimState::CRAFT_FOOD,
			L"CRAFT_FOOD",
			{ "Craft_food_craft" },
			false
		);

		// SetActorLocalRotate(Vector3::UnitX, -5.0f);
		// SetActorLocalPosition({ 0.22f, -0.39f, 0.6f });
	}
	break;

	default: CHECKF(false, L"Craft type is not designated."); break;
	}

	return S_OK;
}

HRESULT Client::CCraft::PostInitialize()
{
	if (FAILED(CSocket::PostInitialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CCraft::BeginPlay()
{
	if (FAILED(CSocket::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CCraft::PreTick(float _fDeltaSeconds)
{
	switch (CSocket::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CCraft::Tick(float _fDeltaSeconds)
{
	switch (CSocket::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CCraft::PostTick(float _fDeltaSeconds)
{
	switch (CSocket::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CCraft::EndPlay()
{
	if (FAILED(CSocket::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CCraft::Render()
{
	CSocket::Render();
}

void Client::CCraft::Release()
{
	CSocket::Release();
}
