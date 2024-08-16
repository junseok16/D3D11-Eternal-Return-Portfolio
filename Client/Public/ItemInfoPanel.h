#pragma once
#include "Panel.h"

namespace Client
{
	class CItem;
	class CItemInfoBackground;
	class CItemInfoImage;
	class CItemInfoText;
	class CItemInfoLevelImage;

    class CItemInfoPanel : public CPanel
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemInfoPanel() = default;

		virtual ~CItemInfoPanel() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitialize();

		virtual HRESULT Initialize();

		virtual HRESULT PostInitialize();

		virtual HRESULT BeginPlay();

		virtual int32 PreTick(float _fDeltaSeconds);

		virtual int32 Tick(float _fDeltaSeconds);
		
		virtual int32 PostTick(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void Release();

	public:
		void RegisterItem(const shared_ptr<CItem>& _spItem, EItemSlotType _eItemSlotType);

		void UnregisterItem(EItemSlotType _eItemSlotType);

		void CheckItemInfo(const shared_ptr<CItem>& _spItem);

	private:
		std::weak_ptr<CItem> m_wpItem;

		EItemSlotType m_eItemRegister = EItemSlotType::ENUM_END;

	private:
		std::weak_ptr<CItemInfoBackground> m_wpItemInfoBackground;

		std::weak_ptr<CItemInfoLevelImage> m_wpItemInfoLevelBackgoundImage;

		std::weak_ptr<CItemInfoLevelImage> m_wpItemInfoLevelLineImage;

		std::weak_ptr<CItemInfoImage> m_wpItemInfoImage;

		std::weak_ptr<CItemInfoText> m_wpItemInfoText[5];
    };
}
