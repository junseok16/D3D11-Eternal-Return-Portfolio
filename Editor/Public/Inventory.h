#pragma once

namespace Editor
{
	class CSurvivor;
	class CStatusPanel;
	class CItemPanel;
	class CItemBuild;
	class CItem;

	class CInventory final : public enable_shared_from_this<CInventory>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInventory() = default;

		virtual ~CInventory() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CInventory> Create();
		
		HRESULT Initialize();
		
		void Release();

	/********************
		Methods
	********************/
	public:
		HRESULT AddItem(const std::shared_ptr<CItem>& _spItem);

		HRESULT AddEquipment(const std::shared_ptr<CItem>& _spItem, EEquipSlotType _eEquipmentSlotType);

		HRESULT RemoveItem(EItemSlotType _eItemSlotType);

		HRESULT RemoveEquipment(EEquipSlotType _eEquipmentSlotType);

		void RemoveCraft(EItemSlotType _eCraftSlotType);

		void SwapItem2Equipment(const std::shared_ptr<CItem>& _spItem, EEquipSlotType _eEquipmentSlotType, EItemSlotType _eItemSlotType);

		void ReserveItem(EItemType _eOutputItem, EItemSlotType _eCraftSlotType);

		void CraftItem();

		void CheckItemBuildOrder();

		void EatItem(int32 _iSlot);

		void AddAdditionalPower(EItemCategoryType _eItemCategoryType);

	/********************
		Getter/Setter
	********************/
	public:
		void SetItemPanel(const std::shared_ptr<CItemPanel>& _spItemPanel) { m_wpItemPanel = _spItemPanel; }

		void RefreshItemPanel();

		void SetStatusPanel(const std::shared_ptr<CStatusPanel>& _spStatusPanel) { m_wpStatusPanel = _spStatusPanel; }

		void RefreshStatusPanel();

		std::shared_ptr<CItem> GetItem(EItemSlotType _eItemSlotType) const { return m_arrItems[static_cast<int32>(_eItemSlotType)]; }

		std::shared_ptr<CItem> GetEquipment(EEquipSlotType _eEquipmentSlotType) const { return m_arrEquipments[static_cast<int32>(_eEquipmentSlotType)];}

		std::shared_ptr<CItem> GetCraft(EItemSlotType _eItemSlotType) const { return m_arrCrafts[static_cast<int32>(_eItemSlotType)]; }

		const std::unordered_set<EItemType>& GetItemTypes();

	/********************
		Data Members
	********************/
	private:
		// �κ��丮�� �ִ� ����
		std::array<std::shared_ptr<CItem>, static_cast<int32>(EEquipSlotType::ENUM_END)> m_arrEquipments{ nullptr };

		// �κ��丮�� �ִ� �����۵�
		std::array<std::shared_ptr<CItem>, static_cast<int32>(EItemSlotType::ENUM_END)> m_arrItems{ nullptr };

		// ������ �� �ִ� �����۵�
		std::array<std::shared_ptr<CItem>, static_cast<int32>(EItemSlotType::FIFTH)> m_arrCrafts{ nullptr };

		// �κ��丮�� �ִ� ������, ����
		std::unordered_set<EItemType> m_usetItemTypes;

		// �κ��丮 �г�
		std::weak_ptr<CItemPanel> m_wpItemPanel;

		// ���� �г�
		std::weak_ptr<CStatusPanel> m_wpStatusPanel;

	private:
		// ������ ���� ����
		std::shared_ptr<CItemBuild> m_spItemBuild = nullptr;

		std::weak_ptr<CSurvivor> m_wpOwnerSurvivor;

	private:
		std::pair<wstring, int32> m_prFirstInputItem;

		std::pair<wstring, int32> m_prSecondInputItem;

		EItemSlotType m_eOutputItemCraftSlotType = EItemSlotType::ENUM_END;
	};
}
