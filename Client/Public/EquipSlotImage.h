#pragma once
#include "Image.h"

namespace Client
{
	class CItem;

	class CEquipSlotImage final : public CImage
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEquipSlotImage() = default;

		virtual ~CEquipSlotImage() = default;
		
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
		void SetEquipSlotType(EEquipSlotType _eEquipSlotType) { m_eEquipSlotType = _eEquipSlotType; }

		void SetItem(const std::shared_ptr<CItem>& _spItem) { m_spItem = _spItem; }

	/********************
		Events
	********************/
	private:
		EEquipSlotType m_eEquipSlotType = EEquipSlotType::ENUM_END;

		std::shared_ptr<CItem> m_spItem = nullptr;
	};
}
