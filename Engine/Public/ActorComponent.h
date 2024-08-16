#pragma once
#include "Object.h"

namespace Engine
{
	class CActor;
	class CWorld;

	class ENGINE_DLL CActorComponent : public CObject
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CActorComponent() = default;

		virtual ~CActorComponent() = default;

	/********************
		Framework
	********************/
	public:
		virtual HRESULT PreInitializeComponent();

		virtual HRESULT InitializeComponent();

		virtual HRESULT PostInitializeComponent();

		virtual HRESULT BeginPlay();

		virtual int32 PreTickComponent(float _fDeltaSeconds);

		virtual int32 TickComponent(float _fDeltaSeconds);

		virtual int32 PostTickComponent(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void RenderShadow();

		virtual void Release();

	/********************
		Getter/Setter
	********************/
	public:
		/**
		* @details		�� ������Ʈ�� ���� �ִ� ���͸� �����մϴ�.
		* @param[in]	std::shared_ptr<CActor> _spOwnerActor: �� ���͸� ���� �ִ� ������ �ξ�� ������
		*/
		void SetOwnerActor(std::shared_ptr<CActor> _spOwnerActor) { m_wpOwnerActor = _spOwnerActor; }

		/**
		* @details		�� ������Ʈ�� ���� �ִ� ���͸� �ҷ��ɴϴ�.
		* @return		�� ������Ʈ�� ���� �ִ� ������ �ξ�� ������
		*/
		const std::shared_ptr<CActor> GetOwnerActor() const;

		void SetComponentType(EComponentType _eComponentType) { m_eComponentType = _eComponentType; }

		void SetComponentName(const std::wstring& _wstrComponentName) { m_wstrComponentName = _wstrComponentName; }

		EComponentType GetComponentType() const { return m_eComponentType; }

		const std::wstring& GetComponentName() const { return m_wstrComponentName; }

	/********************
		Data Members
	********************/
	protected:
		// �� ������Ʈ�� ���� �ִ� ����
		std::weak_ptr<CActor> m_wpOwnerActor;

		// �� ������Ʈ�� ���� �ִ� ����
		std::weak_ptr<CWorld> m_wpOwnerWorld;

		// �� ������Ʈ�� Ÿ��
		EComponentType m_eComponentType = EComponentType::ACTOR;

		// ������Ʈ �̸�
		wstring m_wstrComponentName = L"";
	};
}
