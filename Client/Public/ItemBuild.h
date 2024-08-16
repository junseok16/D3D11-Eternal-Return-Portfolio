#pragma once

namespace Client
{
	class CInventory;

	struct TItemBuildOrder
	{
		// 입력 아이템들
		std::vector<EItemType> m_vecInputItems;

		// 출력 아이템
		EItemType m_eOutputItemType = EItemType::ENUM_END;

		// 출력 아이템 카테고리
		EItemCategoryType m_eOuputItemCategoryType = EItemCategoryType::ENUM_END;

		// 출력 아이템 레벨
		EItemLevel m_eOutputItemLevel = EItemLevel::ENUM_END;
	};

	class CItemBuild final
	{
	public:
		explicit CItemBuild() = default;

		virtual ~CItemBuild() = default;

	public:
		static std::shared_ptr<CItemBuild> Create(const shared_ptr<CInventory>& _spInventory);

		HRESULT Initialize(const shared_ptr<CInventory>& _spInventory);

		void Release();

	public:
		void CreateItemBuildOrder
		(
			const std::vector<EItemType>& _vecInputItems,
			EItemType _eOutputItemType,
			EItemCategoryType _eOuputItemTCategoryType,
			EItemLevel _eOutputItemLevel
		);

		const std::vector<std::weak_ptr<TItemBuildOrder>>& CheckItemBuildOrder();

		std::pair<EItemType, EItemType> FindInputItems(EItemType _eOutputItemType);

	private:
		// EItemBuildType m_eItemBuildType = EItemBuildType::ENUM_END;

		std::vector<std::weak_ptr<TItemBuildOrder>> m_vecItemBuildOrders;

		std::map<int32, std::shared_ptr<TItemBuildOrder>> m_mapItemBuildOrders;

		std::weak_ptr<CInventory> m_wpInventory;
	};
}
