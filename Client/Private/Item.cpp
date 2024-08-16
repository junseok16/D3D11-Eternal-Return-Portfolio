#include "pch.h"
#include "Item.h"

std::shared_ptr<CItem> Client::CItem::Create
(
	const std::shared_ptr<CActor>& _spItemOwner,
	EItemBelongType _eItemBelongType,
	EItemCategoryType _eItemCategoryType,
	EItemLevel _eItemLevel,
	EItemType _eItemType,
	int32 _iCurAmount
)
{
	const std::shared_ptr<CItem> spItem = make_shared<CItem>();
	spItem->Initialize(_spItemOwner, _eItemBelongType, _eItemCategoryType, _eItemLevel, _eItemType, _iCurAmount);
	return spItem;
}

HRESULT Client::CItem::Initialize
(
	const std::shared_ptr<CActor>& _spItemOwner,
	EItemBelongType _eItemBelongType,
	EItemCategoryType _eItemCategoryType,
	EItemLevel _eItemLevel,
	EItemType _eItemType,
	int32 _iCurAmount
)
{
	m_wpItemOwner = _spItemOwner;
	m_eItemBelongType = _eItemBelongType;
	m_eItemCategoryType = _eItemCategoryType;
	m_eItemLevel = _eItemLevel;
	m_eItemType = _eItemType;
	m_iCurAmount = _iCurAmount;

	switch (_eItemCategoryType)
	{
	case Client::EItemCategoryType::FOOD:
	{
		switch (m_eItemType)
		{
		case Client::EItemType::MEAT:
		case Client::EItemType::BREAD:
		case Client::EItemType::RAMEN:
		case Client::EItemType::CHOCOLATE:
			m_fHPIncrease = 300.0f;
			break;
		}
	}
	break;

	case Client::EItemCategoryType::DRINK:
	{
		switch (m_eItemType)
		{
		case Client::EItemType::HONEY:
		case Client::EItemType::WATER:
		case Client::EItemType::WHISKEY:
		case Client::EItemType::CARBONATED_WATER:
			m_fSPIncrease = 200.0f;
			break;

		case Client::EItemType::BOILING_WATER:
			m_fSPIncrease = 400.0f;
			break;

		case Client::EItemType::COLA:
			m_fSPIncrease = 400.0f;
			break;

		case Client::EItemType::HIGHBALL:
			m_fSPIncrease = 630.0f;
			break;

		case Client::EItemType::HONEY_WATER:
			m_fSPIncrease = 400.0f;
			break;
		}
	}
	break;

	default:
		break;
	}

	return S_OK;
}
