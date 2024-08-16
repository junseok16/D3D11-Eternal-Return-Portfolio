#pragma once
#include "Panel.h"

namespace Client
{
	class CItem;
	class CItemButton;
	class CEquipSlotImage;

    class CStatusPanel final : public CPanel
    {
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStatusPanel() = default;

		virtual ~CStatusPanel() = default;
		
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
		void SetEquipment(const std::shared_ptr<CItem>& _spItem, int32 _iSlot);

	/********************
		Data Members
	********************/
	private:
		ESurvivorType m_eSurvivorType = ESurvivorType::ENUM_END;

		std::array<std::weak_ptr<CEquipSlotImage>, (int32)EEquipSlotType::ENUM_END> m_arrEquipImages;

		std::array<std::weak_ptr<CItemButton>, (int32)EEquipSlotType::ENUM_END> m_arrEquipButtons;
    };
}
