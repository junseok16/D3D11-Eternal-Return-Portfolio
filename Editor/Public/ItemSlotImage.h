#pragma once
#include "Image.h"

namespace Editor
{
	class CItem;

	class CItemSlotImage final : public CImage
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemSlotImage() = default;

		virtual ~CItemSlotImage() = default;
		
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

		std::weak_ptr<CItem> m_wpItem;
	};
}
