#include "pch.h"
#include "Inventory.h"

#include "Item.h"
#include "ItemPanel.h"
#include "ItemBuild.h"
#include "StatusPanel.h"

#include "Survivor.h"
#include "GameManager.h"

std::shared_ptr<CInventory> Editor::CInventory::Create()
{
	const std::shared_ptr<CInventory> spInventory = make_shared<CInventory>();
	spInventory->Initialize();
	return spInventory;
}

HRESULT Editor::CInventory::Initialize()
{
	m_spItemBuild = CItemBuild::Create(shared_from_this());
	return S_OK;
}

void Editor::CInventory::Release()
{
	for (auto& spItem : m_arrEquipments)
	{
		if (spItem) { spItem = nullptr; }
	}

	for (auto& spItem : m_arrItems)
	{
		if (spItem) { spItem = nullptr; }
	}

	m_spItemBuild->Release();
	m_spItemBuild = nullptr;
}

HRESULT Editor::CInventory::AddItem(const std::shared_ptr<CItem>& _spItem)
{
	for (int32 iIndex = 0; iIndex < (int32)m_arrItems.size(); ++iIndex)
	{
		if (!m_arrItems[iIndex])
		{
			m_arrItems[iIndex] = _spItem;
			m_wpItemPanel.lock()->SetItem(_spItem, iIndex);
			
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT Editor::CInventory::AddEquipment(const std::shared_ptr<CItem>& _spItem, EEquipSlotType _eEquipmentSlotType)
{
	m_arrEquipments[(int32)_eEquipmentSlotType] = _spItem;
	m_wpStatusPanel.lock()->SetEquipment(_spItem, (int32)_eEquipmentSlotType);
	return S_OK;
}

HRESULT Editor::CInventory::RemoveItem(EItemSlotType _eItemSlotType)
{
	m_arrItems[static_cast<int32>(_eItemSlotType)] = nullptr;
	m_wpItemPanel.lock()->SetItem(nullptr, (int32)_eItemSlotType);
	return S_OK;
}

HRESULT Editor::CInventory::RemoveEquipment(EEquipSlotType _eEquipmentSlotType)
{
	m_arrEquipments[static_cast<int32>(_eEquipmentSlotType)] = nullptr;
	m_wpStatusPanel.lock()->SetEquipment(nullptr, (int32)_eEquipmentSlotType);
	return S_OK;
}

void Editor::CInventory::RemoveCraft(EItemSlotType _eCraftSlotType)
{
	m_arrCrafts[(int32)_eCraftSlotType] = nullptr;
	m_wpItemPanel.lock()->SetCraft(nullptr, (int32)_eCraftSlotType);
}

void Editor::CInventory::SwapItem2Equipment(const std::shared_ptr<CItem>& _spItem, EEquipSlotType _eEquipmentSlotType, EItemSlotType _eItemSlotType)
{
	if (m_arrEquipments[(int32)_eEquipmentSlotType] != nullptr)
	{
		const std::shared_ptr<CItem> spTempItem = m_arrEquipments[(int32)_eEquipmentSlotType];

		AddEquipment(_spItem, _eEquipmentSlotType);
		_spItem->SetItemBelongType(EItemBelongType::EQUIPMENT);
		RemoveItem(_eItemSlotType);

		spTempItem->SetItemBelongType(EItemBelongType::INVENTORY);
		AddItem(spTempItem);

	}
	else
	{
		AddEquipment(_spItem, _eEquipmentSlotType);
		_spItem->SetItemBelongType(EItemBelongType::EQUIPMENT);
		RemoveItem(_eItemSlotType);
	}
}

void Editor::CInventory::ReserveItem(EItemType _eOutputItem, EItemSlotType _eCraftSlotType)
{
	pair<EItemType, EItemType> prInputItems = m_spItemBuild->FindInputItems(_eOutputItem);

	{
		bool bFoundFirstItem = false;

		for (int32 iIndex = 0; iIndex < (int32)m_arrEquipments.size(); ++iIndex)
		{
			if (m_arrEquipments[iIndex] == nullptr) { continue; }

			if (m_arrEquipments[iIndex]->GetItemType() == prInputItems.first)
			{
				m_prFirstInputItem = { L"EQUIPMENT", iIndex };
				bFoundFirstItem = true;
				break;
			}
		}

		if (!bFoundFirstItem)
		{
			for (int32 iIndex = 0; iIndex < (int32)m_arrItems.size(); ++iIndex)
			{
				if (m_arrItems[iIndex] == nullptr) { continue; }

				if (m_arrItems[iIndex]->GetItemType() == prInputItems.first)
				{
					m_prFirstInputItem = { L"INVENTORY", iIndex };
					break;
				}
			}
		}
	}

	{
		bool bFoundSecondItem = false;

		for (int32 iIndex = 0; iIndex < (int32)m_arrEquipments.size(); ++iIndex)
		{
			if (m_arrEquipments[iIndex] == nullptr) { continue; }

			if (m_arrEquipments[iIndex]->GetItemType() == prInputItems.second)
			{
				m_prSecondInputItem = { L"EQUIPMENT", iIndex };
				bFoundSecondItem = true;
				break;
			}
		}

		if (!bFoundSecondItem)
		{
			for (int32 iIndex = 0; iIndex < (int32)m_arrItems.size(); ++iIndex)
			{
				if (m_arrItems[iIndex] == nullptr) { continue; }

				if (m_arrItems[iIndex]->GetItemType() == prInputItems.second)
				{
					m_prSecondInputItem = { L"INVENTORY", iIndex };
					break;
				}
			}
		}
	}

	m_eOutputItemCraftSlotType = _eCraftSlotType;
}

void Editor::CInventory::CraftItem()
{
	if (m_prFirstInputItem.first == L"EQUIPMENT")
	{
		RemoveEquipment((EEquipSlotType)m_prFirstInputItem.second);
	}
	else
	{
		RemoveItem((EItemSlotType)m_prFirstInputItem.second);
	}

	if (m_prSecondInputItem.first == L"EQUIPMENT")
	{
		RemoveEquipment((EEquipSlotType)m_prSecondInputItem.second);
	}
	else
	{
		RemoveItem((EItemSlotType)m_prSecondInputItem.second);
	}
	
	m_arrCrafts[(int32)m_eOutputItemCraftSlotType]->SetItemBelongType(EItemBelongType::INVENTORY);
	AddItem(m_arrCrafts[(int32)m_eOutputItemCraftSlotType]);

	RemoveCraft(m_eOutputItemCraftSlotType);
}

void Editor::CInventory::CheckItemBuildOrder()
{
	const std::vector<std::weak_ptr<TItemBuildOrder>>& vecItemBuildOrders = m_spItemBuild->CheckItemBuildOrder();

	int32 iNumCraftItems = static_cast<int32>(std::min(vecItemBuildOrders.size(), m_arrCrafts.size()));

	for (int32 iIndex = 0; iIndex < (int32)m_arrCrafts.size(); ++iIndex)
	{
		m_arrCrafts[iIndex] = nullptr;
	}

	for (int32 iIndex = 0; iIndex < iNumCraftItems; ++iIndex)
	{
		shared_ptr<TItemBuildOrder> spItemBuildOrder = vecItemBuildOrders[iIndex].lock();

		m_arrCrafts[iIndex] = CItem::Create
		(
			nullptr,
			EItemBelongType::CRAFT,
			spItemBuildOrder->m_eOuputItemCategoryType,
			spItemBuildOrder->m_eOutputItemLevel,
			spItemBuildOrder->m_eOutputItemType,
			1
		);
		m_wpItemPanel.lock()->SetCraft(m_arrCrafts[iIndex], iIndex);
	}

	/*
	for (int32 iIndex = 0; iIndex < (int32)vecItemBuildOrders.size(); ++iIndex)
	{
		shared_ptr<TItemBuildOrder> spItemBuildOrder = vecItemBuildOrders[iIndex].lock();

		bool bExist = false;
		for (int32 jIndex = 0; jIndex < (int32)m_arrCrafts.size(); ++jIndex)
		{
			if (!m_arrCrafts[jIndex]) { continue; }

			if (spItemBuildOrder->m_eOutputItemType == m_arrCrafts[jIndex]->GetItemType())
			{
				bExist = true;
				break;
			}
		}

		if (bExist) { continue; }

		for (int32 jIndex = 0; jIndex < (int32)m_arrCrafts.size(); ++jIndex)
		{
			if (m_arrCrafts[jIndex]) { continue; }

			m_arrCrafts[jIndex] = CItem::Create
			(
				nullptr,
				EItemBelongType::CRAFT,
				spItemBuildOrder->m_eOuputItemTCategoryType,
				spItemBuildOrder->m_eOutputItemLevel,
				spItemBuildOrder->m_eOutputItemType,
				1
			);
			m_wpItemPanel.lock()->SetCraft(m_arrCrafts[jIndex], jIndex);
			break;
		}
	}
	*/
}

void Editor::CInventory::EatItem(int32 _iSlot)
{
	// 아이템이 없는 경우, 반환합니다.
	if (!m_arrItems[_iSlot]) { return; }

	switch (m_arrItems[_iSlot]->GetItemCategoryType())
	{
	case EItemCategoryType::FOOD:
	{
		float fHPIncrease = m_arrItems[_iSlot]->GetHPIncrease();
		CGameManager::GetInstance()->GetSurvivor()->AddLerpHP(fHPIncrease);
		RemoveItem(static_cast<EItemSlotType>(_iSlot));
	}
	break;

	case EItemCategoryType::DRINK:
	{
		CGameManager::GetInstance()->GetSurvivor()->AddLerpSP(m_arrItems[_iSlot]->GetSPIncrease());
		RemoveItem(static_cast<EItemSlotType>(_iSlot));
	}
	break;

	default:
		break;
	}
}

void Editor::CInventory::AddAdditionalPower(EItemCategoryType _eItemCategoryType)
{
}

void Editor::CInventory::RefreshItemPanel()
{
	for (size_t iIndex = 0; iIndex < m_arrItems.size(); ++iIndex)
	{
		m_wpItemPanel.lock()->SetItem(m_arrItems[iIndex], (int32)iIndex);
	}

	for (size_t iIndex = 0; iIndex < m_arrCrafts.size(); ++iIndex)
	{
		m_wpItemPanel.lock()->SetCraft(m_arrCrafts[iIndex], (int32)iIndex);
	}
}

void Editor::CInventory::RefreshStatusPanel()
{
	for (size_t iIndex = 0; iIndex < m_arrEquipments.size(); ++iIndex)
	{
		m_wpStatusPanel.lock()->SetEquipment(m_arrEquipments[iIndex], (int32)iIndex);
	}
}

const std::unordered_set<EItemType>& Editor::CInventory::GetItemTypes()
{
	m_usetItemTypes.clear();

	for (const auto& spItem : m_arrEquipments)
	{
		if (spItem)
		{
			m_usetItemTypes.insert(spItem->GetItemType());
		}
	}

	for (const auto& spItem : m_arrItems)
	{
		if (spItem)
		{
			m_usetItemTypes.insert(spItem->GetItemType());
		}
	}

	return m_usetItemTypes;
}
