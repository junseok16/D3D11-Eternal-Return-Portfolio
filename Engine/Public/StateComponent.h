#pragma once
#include "ActorComponent.h"

namespace Engine
{
	class CActor;

	class ENGINE_DLL CStateComponent : public CActorComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStateComponent() = default;

		virtual ~CStateComponent() = default;

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

		virtual void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		const std::stack<uint32>& GetAnimStates() { return m_stkAnimStates; }
		
		uint32 GetCurAnimState() const { return m_stkAnimStates.top(); }

		uint32 GetCurActorState() const { return m_iCurActorState; }

	/********************
		Methods
	********************/
	public:
		template<typename T>
		HRESULT AddEnterCondition
		(
			uint32 _iAnimState,
			const std::shared_ptr<T>& _spAnimState,
			bool(T::*pFunction)()
		)
		{
			if (m_mapEnterConditions.find(_iAnimState) != m_mapEnterConditions.end()) { return E_FAIL; }

			std::function<bool(void)> fnEnterCondition = [_spAnimState, pFunction]() { return (_spAnimState.get()->*pFunction)(); };

			m_mapEnterConditions.insert({ _iAnimState, fnEnterCondition });
			return S_OK;
		}

		template<typename T>
		HRESULT AddExitCondition
		(	
			uint32 _iAnimState,
			const std::shared_ptr<T>& _spAnimState,
			bool(T::* pFunction)())
		{

			if (m_mapExitConditions.find(_iAnimState) != m_mapExitConditions.end()) { return E_FAIL; }

			std::function<bool(void)> fnExitCondition = [_spAnimState, pFunction]() { return (_spAnimState.get()->*pFunction)(); };

			m_mapExitConditions.insert({ _iAnimState, fnExitCondition });
			return S_OK;
		}

		HRESULT RemoveEnterCondition(uint32 _iAnimState, const std::function<bool(void)>& _fnEnterCondition);

		HRESULT RemoveExitCondition(uint32 _iAnimState, const std::function<bool(void)>& _fnExitCondition);

		void ClearEnterCondition();

		void ClearExitCondition();

	public:
		void PushAnimState(uint32 _iAnimState);

		void PopAnimState();

	public:
		virtual void OnAnimEnter(uint32 _iAnimState, float _fRatio);

		virtual void OnAnimStay(uint32 _iAnimState, float _fRatio);
		
		virtual void OnAnimExit(uint32 _iAnimState, float _fRatio);

	/********************
		Data Members
	********************/
	protected:
		// 액터 상태
		uint32 m_iCurActorState = 0;

		// 액터 애니메이션 상태(상태 우선순위, 상태 번호)
		std::stack<uint32> m_stkAnimStates;

		// 내림차순으로 정렬된 진입 조건(상태 번호 / 진입 조건 함수)
		std::map<uint32, std::function<bool(void)>, std::greater<uint32>> m_mapEnterConditions;

		// 내림차순으로 정렬된 진출 조건(상태 번호 / 진출 조건 함수)
		std::map<uint32, std::function<bool(void)>, std::greater<uint32>> m_mapExitConditions;
	};
}
