#include "pch.h"
#include "ItemBox.h"

// component
#include "StaticMeshComponent.h"
#include "SphereComponent.h"
#include "SoundComponent.h"

// handler
#include "ModelHandler.h"

// item
#include "ItemBoxPanel.h"
#include "InItemBoxPanel.h"
#include "Item.h"

#include "GameManager.h"

#include "Survivor.h"

#include "MathUtility.h"

HRESULT Client::CItemBox::PreInitialize()
{
	m_vActorColor = { 0.0f, 1.0f, 0.0f, 1.0f };
	m_vSrcColor = { 0.0f, 1.0f, 0.0f, 1.0f };
	m_vDstColor = { 1.0f, 0.0f, 0.0f, 1.0f };

	m_wpStaticMeshComponent = CreateActorComponent<CStaticMeshComponent>(L"StaticMeshComponent", EComponentType::STATIC_MESH);
	SetRootComponent(m_wpStaticMeshComponent.lock());

	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent", EComponentType::SOUND);
	m_wpSoundComponent.lock()->SetOwnerComponent(m_wpStaticMeshComponent.lock());

	m_wpSphereComponent = CreateActorComponent<CSphereComponent>(L"SphereComponent", EComponentType::SPHERE);
	m_wpSphereComponent.lock()->SetOwnerComponent(m_wpStaticMeshComponent.lock());

	m_wpStaticMeshComponent.lock()->SetModelDesc(GetActorName());
	m_wpStaticMeshComponent.lock()->SetVertexShaderDesc(L"VS_StaticMesh");
	m_wpStaticMeshComponent.lock()->SetPixelShaderDesc(L"PS_RimStaticMesh");

	return CActor::PreInitialize();
}

HRESULT Client::CItemBox::Initialize()
{
	if (FAILED(CActor::Initialize())) { return E_FAIL; }

	Vector3 vPosition = CModelHandler::GetInstance()->GetAverageWorldPosition(EModelType::STATIC, GetActorName() + L"0");
	
	m_wpSphereComponent.lock()->SetCollisionLayer(ECollisionLayer::ITEM);
	m_wpSphereComponent.lock()->AddCollisionFlag(ECollisionLayer::PLAYER);
	m_wpSphereComponent.lock()->SetComponentLocalPosition(vPosition);
	m_wpSphereComponent.lock()->SetRadius(0.8f);

	return S_OK;
}

HRESULT Client::CItemBox::PostInitialize()
{
	if (FAILED(CActor::PostInitialize())) { return E_FAIL; }

	uint32 iWeaponSize = CMathUtility::GetRandomInteger(0, 1);
	uint32 iArmorSize = CMathUtility::GetRandomInteger(0, 1);
	uint32 iHeadSize = CMathUtility::GetRandomInteger(0, 1);
	uint32 iArmSize = CMathUtility::GetRandomInteger(0, 1);
	uint32 iLegSize = CMathUtility::GetRandomInteger(0, 1);
	uint32 iFoodSize = CMathUtility::GetRandomInteger(0, 1);
	uint32 iDrinkSize = CMathUtility::GetRandomInteger(0, 1);

	uint32 iMaterialSize = CMathUtility::GetRandomInteger(1, 8 - (iWeaponSize + iArmorSize + iHeadSize + iArmSize + iLegSize + iFoodSize + iDrinkSize));

	uint32 iItemIndex = 0;

	for (uint32 iIndex = 0; iIndex < iMaterialSize; ++iIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::SCISSORS, (int32)EItemType::PIANO_WIRE));
		m_arrItems[iItemIndex++] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::ITEM_BOX,
			EItemCategoryType::MATERIAL,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
	}

	for (uint32 jIndex = 0; jIndex < iWeaponSize; ++jIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::COTTON_GLOVE, (int32)EItemType::HAMMER));
		m_arrItems[iItemIndex++] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::ITEM_BOX,
			EItemCategoryType::WEAPON,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
	}

	for (uint32 jIndex = 0; jIndex < iArmorSize; ++jIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::WINDBREAKER, (int32)EItemType::FABRIC_ARMOR));
		m_arrItems[iItemIndex++] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::ITEM_BOX,
			EItemCategoryType::ARMOR,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
	}

	for (uint32 jIndex = 0; jIndex < iHeadSize; ++jIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::HAIR_BAND, (int32)EItemType::BIKE_HELMET));
		m_arrItems[iItemIndex++] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::ITEM_BOX,
			EItemCategoryType::HEAD,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
	}

	for (uint32 jIndex = 0; jIndex < iArmSize; ++jIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::WATCH, (int32)EItemType::BRACELET));
		m_arrItems[iItemIndex++] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::ITEM_BOX,
			EItemCategoryType::ARM,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
	}

	for (uint32 jIndex = 0; jIndex < iLegSize; ++jIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::SLIPPER, (int32)EItemType::TIGHTS));
		m_arrItems[iItemIndex++] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::ITEM_BOX,
			EItemCategoryType::LEG,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
	}

	for (uint32 jIndex = 0; jIndex < iFoodSize; ++jIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::BREAD, (int32)EItemType::CHOCOLATE));
		m_arrItems[iItemIndex++] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::ITEM_BOX,
			EItemCategoryType::FOOD,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
	}

	for (uint32 jIndex = 0; jIndex < iDrinkSize; ++jIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::HONEY, (int32)EItemType::CARBONATED_WATER));
		m_arrItems[iItemIndex++] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::ITEM_BOX,
			EItemCategoryType::DRINK,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
	}
	return S_OK;
}

HRESULT Client::CItemBox::BeginPlay()
{
	if (FAILED(CActor::BeginPlay())) { return E_FAIL; }

	m_vItemBoxWorldPosition = Vector4(m_wpSphereComponent.lock()->GetComponentLocalPosition());
	return S_OK;
}

int32 Client::CItemBox::PreTick(float _fDeltaSeconds)
{
	m_bIsInFrustum = true;

	if (!IsInFrustum(m_vItemBoxWorldPosition, 1.0f))
	{
		m_bIsInFrustum = false;
		return 0;
	}

	shared_ptr<CSurvivor> spSurvivor = CGameManager::GetInstance()->GetSurvivor();
	Vector3 vItemBoxPosition = { m_vItemBoxWorldPosition.x, m_vItemBoxWorldPosition.y, m_vItemBoxWorldPosition.z };
	Vector3 vSurvivorPosition = spSurvivor->GetActorWorldPosition().value();
	float fDistance = Vector3::Distance(vSurvivorPosition, vItemBoxPosition);

	m_bIsInRange = true;

	if (50.0f <= fDistance)
	{
		m_bIsInRange = false;
		return 0;
	}

	switch (CActor::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

int32 Client::CItemBox::Tick(float _fDeltaSeconds)
{
	if (!m_bIsInFrustum || !m_bIsInRange) { return 0; }

	switch (CActor::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	if (!m_bFirstOpened && !m_bLerped)
	{
		m_fCurLerpSeconds += _fDeltaSeconds;

		if (m_fMaxLerpSeconds <= m_fCurLerpSeconds)
		{
			m_bLerped = true;
			m_fCurLerpSeconds = 0.0f;
			m_vActorColor = m_vDstColor;
			return 0;
		}

		m_vActorColor = Vector4::Lerp(m_vSrcColor, m_vDstColor, m_fCurLerpSeconds / m_fMaxLerpSeconds);
	}

	return 0;
}

int32 Client::CItemBox::PostTick(float _fDeltaSeconds)
{
	if (!m_bIsInFrustum || !m_bIsInRange) { return 0; }

	switch (CActor::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}
	return 0;
}

HRESULT Client::CItemBox::EndPlay()
{
	if (FAILED(CActor::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CItemBox::Render()
{
	if (!m_bIsInFrustum || !m_bIsInRange) { return; }

	CActor::Render();
}

void Client::CItemBox::Release()
{
	for (auto& spItem : m_arrItems)
	{
		if (spItem) { spItem = nullptr; }
	}

	CActor::Release();
}

void Client::CItemBox::OpenItemBox()
{
	if (m_bOpened) { return; }

	if (m_bFirstOpened)
	{
		m_bFirstOpened = false;
	}

	int32 iRandomIndex = CMathUtility::GetRandomInteger(0, 9);
	m_wpSoundComponent.lock()->PlaySoundEx(m_arrOpenSounds[iRandomIndex], ESoundType::EFFECT_04);

	m_bOpened = true;

	for (int32 iIndex = 0; iIndex < 8; ++iIndex)
	{
		m_wpItemBoxPanel.lock()->SetItem(m_arrItems[iIndex], iIndex);
	}
	m_wpItemBoxPanel.lock()->SetActive(true);
}

void Client::CItemBox::CloseItemBox()
{
	if (!m_bOpened) { return; }
	m_bOpened = false;

	for (int32 iIndex = 0; iIndex < 8; ++iIndex)
	{
		m_wpItemBoxPanel.lock()->SetItem(nullptr, iIndex);
	}
	m_wpItemBoxPanel.lock()->SetActive(false);
}

void Client::CItemBox::RemoveItem(EItemSlotType _eItemSlotType)
{
	m_wpItemBoxPanel.lock()->SetItem(nullptr, (int32)_eItemSlotType);
	m_arrItems[(int32)_eItemSlotType] = nullptr;
}
