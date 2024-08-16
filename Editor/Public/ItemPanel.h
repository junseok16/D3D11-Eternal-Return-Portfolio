#pragma once
#include "Panel.h"

namespace Editor
{
	class CItemBox;
	class CItemSlotImage;
	class CItemButton;
	class CItem;

    class CItemPanel final : public CPanel
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemPanel() = default;

		virtual ~CItemPanel() = default;
		
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
		
	/********************
		Methods
	********************/
	public:
		void SetItem(const std::shared_ptr<CItem>& _spItem, int32 _iSlot);

		void SetCraft(const std::shared_ptr<CItem>& _spItem, int32 _iSlot);

	/********************
		Data Members
	********************/
	private:
		std::array<std::weak_ptr<CItemSlotImage>, (int32)EItemSlotType::FIFTH> m_arrCraftSlots;
		
		std::array<std::weak_ptr<CItemButton>, (int32)EItemSlotType::FIFTH> m_arrCraftButtons;

		std::array<std::weak_ptr<CItemSlotImage>, (int32)EItemSlotType::ENUM_END> m_arrItemSlots;

		std::array<std::weak_ptr<CItemButton>, (int32)EItemSlotType::ENUM_END> m_arrItemButtons;
    };
}
