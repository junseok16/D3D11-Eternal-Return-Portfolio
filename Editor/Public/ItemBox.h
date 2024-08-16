#pragma once
#include "Actor.h"

namespace Engine
{
	class CStaticMeshComponent;
	class CSphereComponent;
}

namespace Editor
{
	class CItem;
	class CItemBoxPanel;

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

		void SetLocationType(ELocationType _eLocationType) { m_eLocationType = _eLocationType; }

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

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CStaticMeshComponent> m_wpStaticMeshComponent;

		std::weak_ptr<CSphereComponent> m_wpSphereComponent;
		
	private:
		// ������ �ڽ� �г�
		std::weak_ptr<CItemBoxPanel> m_wpItemBoxPanel;

		// ������ �ڽ��� ���ȴ��� ����
		bool m_bOpened = false;

		// ������ �ڽ��� ó�� ���ȴ��� ����
		bool m_bFirstOpened = true;

		// �� ������ ���ڿ� �ִ� �����۵�
		std::array<std::shared_ptr<CItem>, 8> m_arrItems{ nullptr };

		// ������ ���ڰ� ���� ����
		ELocationType m_eLocationType = ELocationType::ENUM_END;
	};
}
