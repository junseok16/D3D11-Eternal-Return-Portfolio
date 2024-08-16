// default
#include "pch.h"
#include "WildAnimal.h"

// component
#include "WildAnimalStateComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"

// survivor
#include "Survivor.h"

// item
#include "Item.h"
#include "ItemBoxPanel.h"

// utility
#include "MathUtility.h"

#include "GameManager.h"

HRESULT Client::CWildAnimal::PreInitialize()
{
	return CCharacter::PreInitialize();
}

HRESULT Client::CWildAnimal::Initialize()
{
	if (FAILED(CCharacter::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Client::CWildAnimal::PostInitialize()
{
	if (FAILED(CCharacter::PostInitialize())) { return E_FAIL; }

	uint32 iFoodSize = CMathUtility::GetRandomInteger(1, 1);
	uint32 iMaterialSize = CMathUtility::GetRandomInteger(1, 2);

	uint32 iItemIndex = 0;

	for (uint32 iIndex = 0; iIndex < iFoodSize; ++iIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::MEAT, (int32)EItemType::MEAT));
		m_arrItems[iItemIndex] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::WILD_ANIMAL,
			EItemCategoryType::FOOD,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
		iItemIndex++;
	}

	for (uint32 iIndex = 0; iIndex < iMaterialSize; ++iIndex)
	{
		EItemType eItemType = static_cast<EItemType>(CMathUtility::GetRandomInteger((int32)EItemType::LEATHER, (int32)EItemType::LEATHER));

		CHECKF(iItemIndex < 8, L"Item index is over 8.");
		m_arrItems[iItemIndex] = CItem::Create
		(
			static_pointer_cast<CActor>(shared_from_this()),
			EItemBelongType::WILD_ANIMAL,
			EItemCategoryType::MATERIAL,
			EItemLevel::NORMAL,
			eItemType,
			1
		);
		iItemIndex++;
	}

	return S_OK;
}

HRESULT Client::CWildAnimal::BeginPlay()
{
	if (FAILED(CCharacter::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Client::CWildAnimal::PreTick(float _fDeltaSeconds)
{
	m_wpSurvivor = CGameManager::GetInstance()->GetSurvivor();

	m_bIsInFrustum = true;

	if (!m_bAttacked)
	{
		if (!IsInFrustum(1.0f))
		{
			m_bIsInFrustum = false;
			return 0;
		}
	}

	Vector3 vSurvivorPosition = m_wpSurvivor.lock()->GetActorWorldPosition().value();
	Vector3 vWildAnimalPosition = GetActorWorldPosition().value();
	float fDistance = Vector3::Distance(vSurvivorPosition, vWildAnimalPosition);

	m_bIsInRange = true;
	if (70.0f <= fDistance) { m_bIsInRange = false; return 0; }

	switch (CCharacter::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// 델타 타임을 갱신합니다.
	m_fDeltaSeconds = _fDeltaSeconds;

	return 0;
}

int32 Client::CWildAnimal::Tick(float _fDeltaSeconds)
{
	if (!m_bIsInFrustum) { return 0; }

	switch (CCharacter::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Client::CWildAnimal::PostTick(float _fDeltaSeconds)
{
	if (!m_bIsInFrustum) { return 0; }

	switch (CCharacter::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Client::CWildAnimal::EndPlay()
{
	if (FAILED(CCharacter::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Client::CWildAnimal::Render()
{
	if (!m_bIsInFrustum) { return; }

	CCharacter::Render();
}

void Client::CWildAnimal::Release()
{
	CCharacter::Release();
}

float Client::CWildAnimal::GetMaxChaseSeconds() const
{
	if (m_wpWildAnimalStateComponent.expired()) { return 0.0f; }

	return m_wpWildAnimalStateComponent.lock()->GetMaxChaseSeconds();
}

float Client::CWildAnimal::GetCurChaseSeconds() const
{
	if (m_wpWildAnimalStateComponent.expired()) { return 0.0f; }

	return m_wpWildAnimalStateComponent.lock()->GetCurChaseSeconds();
}

float Client::CWildAnimal::TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn)
{
	if (m_bDead) { return 0.0f; }

	m_bAttacked = true;
	m_fCurHP -= _fDamageAmount;

	if ((m_fCurHP <= 0.0f) && !m_bDead)
	{
		m_bDead = true;
		shared_ptr<CSurvivor> spSurvivor = dynamic_pointer_cast<CSurvivor>(_spInstigatorPawn);
		spSurvivor->AddCurExp(m_fExp);

		if (spSurvivor->GetSurvivorType() == ESurvivorType::HYUNWOO)
		{
			string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));
			spSurvivor->PlaySoundEx("Hyunwoo_killMonster_"+ strIndex +"_ko", ESoundType::TALK_02);
		}
		else if (spSurvivor->GetSurvivorType() == ESurvivorType::AYA)
		{
			string strIndex = to_string(CMathUtility::GetRandomInteger(1, 3));
			spSurvivor->PlaySoundEx("Aya_killMonster_" + strIndex + "_ko", ESoundType::TALK_02);
		}

		Vector3 vFrom = { -1.0f, 0.9f, -1.0f };
		Vector3 vTo = { 1.0f, 1.1f, -0.5f };

		Vector3 vPosition = CMathUtility::GetRandomDirection(vFrom, vTo);
		float fScale = static_cast<float>(CMathUtility::GetRandomInteger(1, 2));
		fScale /= 10.0f;

		m_wpHitEffectComponent.lock()->SetComponentLocalPosition(vPosition);
		m_wpHitEffectComponent.lock()->SetComponentLocalScale({ fScale, fScale, fScale });
		m_wpHitEffectComponent.lock()->PlayMeshEffect();
		return 0.0f;
	}

	Vector3 vFrom = { -1.0f, 0.9f, -2.0f };
	Vector3 vTo = { 1.0f, 1.1f, -1.0f };

	Vector3 vPosition = CMathUtility::GetRandomDirection(vFrom, vTo);
	float fScale = static_cast<float>(CMathUtility::GetRandomInteger(12, 20));
	fScale /= 10.0f;

	m_wpHitEffectComponent.lock()->SetComponentLocalPosition(vPosition);
	m_wpHitEffectComponent.lock()->SetComponentLocalScale({ fScale, fScale, fScale });
	m_wpHitEffectComponent.lock()->PlayMeshEffect();
	return 0.0f;
}

void Client::CWildAnimal::OpenItemBox()
{
	if (IsDead() == false) { return; }

	if (m_bOpened) { return; }

	if (m_bFirstOpened) { m_bFirstOpened = false; }

	m_bOpened = true;

	for (int32 iIndex = 0; iIndex < 8; ++iIndex)
	{
		m_wpItemBoxPanel.lock()->SetItem(m_arrItems[iIndex], iIndex);
	}
	m_wpItemBoxPanel.lock()->SetActive(true);
}

void Client::CWildAnimal::CloseItemBox()
{
	if (IsDead() == false) { return; }

	if (!m_bOpened) { return; }
	m_bOpened = false;

	for (int32 iIndex = 0; iIndex < 8; ++iIndex)
	{
		m_wpItemBoxPanel.lock()->SetItem(nullptr, iIndex);
	}
	m_wpItemBoxPanel.lock()->SetActive(false);
}

void Client::CWildAnimal::RemoveItem(EItemSlotType _eItemSlotType)
{
	m_wpItemBoxPanel.lock()->SetItem(nullptr, (int32)_eItemSlotType);
	m_arrItems[(int32)_eItemSlotType] = nullptr;
}
