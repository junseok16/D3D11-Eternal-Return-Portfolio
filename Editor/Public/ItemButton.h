#pragma once
#include "Button.h"

namespace Editor
{
	class CGameManager;
	class CItemBox;
	class CInventory;
	class CItem;
	class CSurvivor;

	class CItemButton final : public CButton
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemButton() = default;

		virtual ~CItemButton() = default;
		
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
		virtual void OnButtonUpIn() override;

		virtual void OnButtonUpOut() override;
		
	/********************
		Getter/Setter
	********************/
	public:
		void SetItemSlotType(EItemSlotType _eItemSlotType) { m_eItemSlotType = _eItemSlotType; }

		void SetItemBelongType(EItemBelongType _eItemBelongType) { m_eItemBelongType = _eItemBelongType; }

		void SetItem(const std::shared_ptr<CItem>& _spItem) { m_wpItem = _spItem; }

	/********************
		Events
	********************/
	private:
		EItemBelongType m_eItemBelongType = EItemBelongType::ENUM_END;

		EItemSlotType m_eItemSlotType = EItemSlotType::ENUM_END;

		std::weak_ptr<CGameManager> m_wpGameManager;

		std::weak_ptr<CItem> m_wpItem;

		std::weak_ptr<CInventory> m_wpInventory;

		std::weak_ptr<CSurvivor> m_wpSurvivor;
	};
}
