#pragma once
#include "Panel.h"

namespace Editor
{
	class CItemPanel;
	class CItemSlotImage;
	class CItemButton;
	class CItem;

	class CItemBoxPanel : public CPanel
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemBoxPanel() = default;

		virtual ~CItemBoxPanel() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitialize() override;

		virtual HRESULT Initialize() override;

		virtual HRESULT PostInitialize() override;

		virtual HRESULT BeginPlay() override;

		virtual int32 PreTick(float _fDeltaSeconds) override;

		virtual int32 Tick(float _fDeltaSeconds) override;
		
		virtual int32 PostTick(float _fDeltaSeconds) override;

		virtual HRESULT EndPlay() override;

		virtual void Render() override;

		virtual void Release() override;
		
	/********************
		Methods
	********************/
	public:
		void SetItem(const std::shared_ptr<CItem>& _spItem, int32 _iSlot);

	/********************
		Data Members
	********************/
	private:
		std::array<std::weak_ptr<CItemSlotImage>, 8> m_arrItemSlots;

		std::array<std::weak_ptr<CItemButton>, 8> m_arrItemButtons;
	};
}
