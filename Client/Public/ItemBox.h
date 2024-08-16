#pragma once
#include "Actor.h"

namespace Engine
{
	class CStaticMeshComponent;
	class CSphereComponent;
	class CSoundComponent;
}

namespace Client
{
	class CItem;
	class CItemBoxPanel;
	class CInItemBoxPanel;

	class CItemBox : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemBox() = default;

		virtual ~CItemBox() = default;

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
		Getter/Setter
	********************/
	public:
		void SetItemBoxPanel(const std::shared_ptr<CItemBoxPanel>& _spItemBoxPanel) { m_wpItemBoxPanel = _spItemBoxPanel; }

		void SetInItemBoxPanel(const std::shared_ptr<CInItemBoxPanel>& _spInItemBoxPanel) { m_wpInItemBoxPanel = _spInItemBoxPanel; }

		bool IsOpened() const { return m_bOpened; }

		bool IsFirstOpened() const { return m_bFirstOpened; }

	/********************
		Methods
	********************/
	public:
		void OpenItemBox();

		void CloseItemBox();
		
	/********************
		Getter/Setter
	********************/
	public:
		std::array<std::shared_ptr<CItem>, 8>& GetItems() { return m_arrItems; }

		void RemoveItem(EItemSlotType _eItemSlotType);

		const Vector4 GetItemBoxWorldPosition() { return m_vItemBoxWorldPosition; }

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;

		std::weak_ptr<CSphereComponent> m_wpSphereComponent;
		
		std::weak_ptr<CSoundComponent> m_wpSoundComponent;

	private:
		Vector4 m_vSrcColor = Vector4::One;

		Vector4 m_vDstColor = Vector4::One;

		float m_fCurLerpSeconds = 0.0f;

		float m_fMaxLerpSeconds = 0.5f;

		bool m_bLerped = false;

		// 아이템 박스가 열렸는지 여부
		bool m_bOpened = false;

		// 아이템 박스가 처음 열렸는지 여부
		bool m_bFirstOpened = true;

		bool m_bIsInRange = true;

		// 이 아이템 상자에 있는 아이템들
		std::array<std::shared_ptr<CItem>, 8> m_arrItems{ nullptr };

	private:
		std::weak_ptr<CItemBoxPanel> m_wpItemBoxPanel;

		std::weak_ptr<CInItemBoxPanel> m_wpInItemBoxPanel;

		Vector4 m_vItemBoxWorldPosition = Vector4::Zero;

	private:
		std::array<string, 10> m_arrOpenSounds
		{
			"OpenSound_AltarTable_01",
			"OpenSound_Bag_01",
			"OpenSound_CartonBox_01",
			"OpenSound_Coffin_01",
			"OpenSound_Drum_01",
			"OpenSound_SteelBox_01",
			"OpenSound_TrashCan_01",
			"OpenSound_VendingMachine_01"
			"OpenSound_Wheelbarrow_01",
			"OpenSound_WreckCar_01",
		};
	};
}
