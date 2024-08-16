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
		* @details		이 컴포넌트를 갖고 있는 액터를 저장합니다.
		* @param[in]	std::shared_ptr<CActor> _spOwnerActor: 이 액터를 갖고 있는 액터의 셰어드 포인터
		*/
		void SetOwnerActor(std::shared_ptr<CActor> _spOwnerActor) { m_wpOwnerActor = _spOwnerActor; }

		/**
		* @details		이 컴포넌트를 갖고 있는 액터를 불러옵니다.
		* @return		이 컴포넌트를 갖고 있는 액터의 셰어드 포인터
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
		// 이 컴포넌트를 갖고 있는 액터
		std::weak_ptr<CActor> m_wpOwnerActor;

		// 이 컴포넌트를 갖고 있는 월드
		std::weak_ptr<CWorld> m_wpOwnerWorld;

		// 이 컴포넌트의 타입
		EComponentType m_eComponentType = EComponentType::ACTOR;

		// 컴포넌트 이름
		wstring m_wstrComponentName = L"";
	};
}
