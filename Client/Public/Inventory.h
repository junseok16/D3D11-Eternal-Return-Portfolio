#pragma once

namespace Client
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

		void CraftItem(EItemLevel& _eItemLevel);

		void CheckItemBuildOrder();

		void EatItem(int32 _iSlot);

		EItemCategoryType GetItemCategoryType(int32 _iSlot) const;

	public:
		void AddAdditionalPower(EItemCategoryType _eItemCategoryType, float _fPower);

	/********************
		Getter/Setter
	********************/
	public:
		void SetInventoryOwner(const shared_ptr<CSurvivor>& _spInventoryOwner) { m_wpInventoryOwner = _spInventoryOwner; }

		void SetItemPanel(const std::shared_ptr<CItemPanel>& _spItemPanel) { m_wpItemPanel = _spItemPanel; }

		void RefreshItemPanel();

		void SetStatusPanel(const std::shared_ptr<CStatusPanel>& _spStatusPanel) { m_wpStatusPanel = _spStatusPanel; }

		void RefreshStatusPanel();

		std::shared_ptr<CItem> GetItem(EItemSlotType _eItemSlotType) const { return m_arrItems[static_cast<int32>(_eItemSlotType)]; }

		std::shared_ptr<CItem> GetEquipment(EEquipSlotType _eEquipmentSlotType) const { return m_arrEquipments[static_cast<int32>(_eEquipmentSlotType)];}

		std::shared_ptr<CItem> GetCraft(EItemSlotType _eItemSlotType) const { return m_arrCrafts[static_cast<int32>(_eItemSlotType)]; }

		const std::unordered_set<EItemType>& GetItemTypes();

		std::shared_ptr<CItem> GetCurCraft() const { return m_arrCrafts[static_cast<int32>(m_eOutputItemCraftSlotType)]; }

	/********************
		Data Members
	********************/
	private:
		// 인벤토리에 있는 장비들
		std::array<std::shared_ptr<CItem>, static_cast<int32>(EEquipSlotType::ENUM_END)> m_arrEquipments{ nullptr };

		// 인벤토리에 있는 아이템들
		std::array<std::shared_ptr<CItem>, static_cast<int32>(EItemSlotType::ENUM_END)> m_arrItems{ nullptr };

		// 제작할 수 있는 아이템들
		std::array<std::shared_ptr<CItem>, static_cast<int32>(EItemSlotType::FIFTH)> m_arrCrafts{ nullptr };

		// 인벤토리에 있는 아이템, 장비들
		std::unordered_set<EItemType> m_usetItemTypes;

		// 인벤토리 패널
		std::weak_ptr<CItemPanel> m_wpItemPanel;

		// 상태 패널
		std::weak_ptr<CStatusPanel> m_wpStatusPanel;

	private:
		// 아이템 빌드 오더
		std::shared_ptr<CItemBuild> m_spItemBuild = nullptr;

		std::weak_ptr<CSurvivor> m_wpInventoryOwner;

	private:
		std::pair<wstring, int32> m_prFirstInputItem;

		std::pair<wstring, int32> m_prSecondInputItem;

		EItemSlotType m_eOutputItemCraftSlotType = EItemSlotType::ENUM_END;
	};
}
