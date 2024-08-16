#pragma once

namespace Engine
{
	class CActor;
}

namespace Editor
{
	class CItem final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItem() = default;

		virtual ~CItem() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CItem> Create
		(
			const std::shared_ptr<CActor>& _spItemOwner,
			EItemBelongType _eItemBelongType,
			EItemCategoryType _eItemCategoryType,
			EItemLevel _eItemLevel,
			EItemType _eItemType,
			int32 _iCurAmount
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CActor>& _spItemOwner,
			EItemBelongType _eItemBelongType,
			EItemCategoryType _eItemCategoryType,
			EItemLevel _eItemLevel,
			EItemType _eItemType,
			int32 _iCurAmount
		);

	/********************
		Getter/Setter
	********************/
	public:
		void SetItemBelongType(EItemBelongType _eItemBelongType) { m_eItemBelongType = _eItemBelongType; }

		EItemBelongType GetItemBelongType() const { return m_eItemBelongType; }

		EItemLevel GetItemLevel() const { return m_eItemLevel; }

		EItemCategoryType GetItemCategoryType() const { return m_eItemCategoryType; }

		EItemType GetItemType() const { return m_eItemType; }

		std::shared_ptr<CActor> GetItemOwner() const { return m_wpItemOwner.expired() ? nullptr : m_wpItemOwner.lock(); }

		float GetHPIncrease() const { return m_fHPIncrease; }

		float GetSPIncrease() const { return m_fSPIncrease; }

	private:
		// 아이템 카테고리
		EItemCategoryType m_eItemCategoryType = EItemCategoryType::ENUM_END;

		// 아이템 등급
		EItemLevel m_eItemLevel = EItemLevel::ENUM_END;

		// 아이템 타입
		EItemType m_eItemType = EItemType::ENUM_END;

		// 아이템 현재 수량
		int32 m_iCurAmount = 0;

		// 이 아이템 소속
		EItemBelongType m_eItemBelongType = EItemBelongType::ENUM_END;

		// 이 아이템 소속된 액터
		std::weak_ptr<CActor> m_wpItemOwner;

		// HP 증가량
		float m_fHPIncrease = 0.0f;

		// SP 증가량
		float m_fSPIncrease = 0.0f;
	};
}
