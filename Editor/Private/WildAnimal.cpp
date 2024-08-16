#include "pch.h"
#include "WildAnimal.h"

#include "WildAnimalStateComponent.h"

#include "Survivor.h"
#include "Item.h"
#include "ItemBoxPanel.h"

#include "MathUtility.h"

HRESULT Editor::CWildAnimal::PreInitialize()
{
	return CCharacter::PreInitialize();
}

HRESULT Editor::CWildAnimal::Initialize()
{
	if (FAILED(CCharacter::Initialize())) { return E_FAIL; }

	return S_OK;
}

HRESULT Editor::CWildAnimal::PostInitialize()
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

HRESULT Editor::CWildAnimal::BeginPlay()
{
	if (FAILED(CCharacter::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Editor::CWildAnimal::PreTick(float _fDeltaSeconds)
{
	switch (CCharacter::PreTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	// 델타 타임을 갱신합니다.
	m_fDeltaSeconds = _fDeltaSeconds;

	return 0;
}

int32 Editor::CWildAnimal::Tick(float _fDeltaSeconds)
{
	switch (CCharacter::Tick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Editor::CWildAnimal::PostTick(float _fDeltaSeconds)
{
	switch (CCharacter::PostTick(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Editor::CWildAnimal::EndPlay()
{
	if (FAILED(CCharacter::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Editor::CWildAnimal::Render()
{
	CCharacter::Render();
}

void Editor::CWildAnimal::Release()
{
	CCharacter::Release();
}

float Editor::CWildAnimal::TakeDamage(float _fDamageAmount, std::shared_ptr<CController> _spInstigatorController, std::shared_ptr<CPawn> _spInstigatorPawn)
{
	m_bAttacked = true;
	m_fCurHP -= _fDamageAmount;

	if (m_fCurHP <= 0.0f)
	{
		dynamic_pointer_cast<CSurvivor>(_spInstigatorPawn)->AddCurExp(m_fExp);
	}

	return 0.0f;
}

void Editor::CWildAnimal::OpenItemBox()
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

void Editor::CWildAnimal::CloseItemBox()
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

void Editor::CWildAnimal::RemoveItem(EItemSlotType _eItemSlotType)
{
	m_wpItemBoxPanel.lock()->SetItem(nullptr, (int32)_eItemSlotType);
	m_arrItems[(int32)_eItemSlotType] = nullptr;
}
