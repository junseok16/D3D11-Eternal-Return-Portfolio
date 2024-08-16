#pragma once
#include "ActorComponent.h"

namespace Engine
{
	class CInputManager;

	class ENGINE_DLL CInputComponent final : public CActorComponent
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInputComponent() = default;

		virtual ~CInputComponent() = default;

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
		Data Members
	********************/
	public:
		// 키 액시스
		HRESULT MapKeyAxis(const std::wstring& _wstrKeyAxis, int32 _iKey, int32 _iScale);

		template<typename T>
		HRESULT BindKeyAxis(const std::wstring& _wstrKeyAxis, std::shared_ptr<T> _spOwner, void(T::*function)(int32))
		{
			std::function<void(int32)> fnCallback = [_spOwner, function](int32 _iAxisValue)
				{ (_spOwner.get()->*function)(_iAxisValue); };

			if (m_umapKeyAxisCallbacks.find(_wstrKeyAxis) != m_umapKeyAxisCallbacks.end()) { return E_FAIL; }

			m_umapKeyAxisCallbacks.insert({ _wstrKeyAxis, fnCallback });
			return S_OK;
		}

		// 키 액션
		HRESULT MapKeyAction(const std::wstring& _wstrAction, int32 _iKey);

		template<typename T>
		HRESULT BindKeyAction(const std::wstring& _wstrAction, std::shared_ptr<T> _spOwner, bool(T::*function)())
		{
			std::function<bool(void)> fnCallback = [_spOwner, function]() { return (_spOwner.get()->*function)(); };

			if (m_umapKeyActionCallbacks.find(_wstrAction) != m_umapKeyActionCallbacks.end()) { return E_FAIL; }

			m_umapKeyActionCallbacks.insert({ _wstrAction, fnCallback });
			return S_OK;
		}
		
		// 마우스 액시스
		HRESULT MapMouseAxis(const std::wstring& _wstrMouseAxis, int32 _iKey, int32 _iScale);

		template<typename T>
		HRESULT BindMouseAxis(const std::wstring& _wstrMouseAxis, std::shared_ptr<T> _spOwner, void(T::*function)(int32))
		{
			std::function<void(int32)> fnCallback = [_spOwner, function](int32 _iAxisValue)
				{ (_spOwner.get()->*function)(_iAxisValue); };

			if (m_umapMouseAxisCallbacks.find(_wstrMouseAxis) != m_umapMouseAxisCallbacks.end()) { return E_FAIL; }

			m_umapMouseAxisCallbacks.insert({ _wstrMouseAxis, fnCallback });
			return S_OK;
		}

		// 마우스 액션
		HRESULT MapMouseAction(const std::wstring& _wstrMouseAction, int32 _iKey);

		template<typename T>
		HRESULT BindMouseAction(const std::wstring& _wstrMouseAction, std::shared_ptr<T> _spOwner, void(T::* function)())
		{
			std::function<void(void)> fnCallback = [_spOwner, function]()
				{ (_spOwner.get()->*function)(); };

			if (m_umapMouseActionCallbacks.find(_wstrMouseAction) != m_umapMouseActionCallbacks.end()) { return E_FAIL; }

			m_umapMouseActionCallbacks.insert({ _wstrMouseAction, fnCallback });
			return S_OK;
		}

	public:
		void ClearKeyAction();

		void ClearKeyAxis();

	/********************
		Getter/Setter
	********************/
	public:
		bool IsKeyDown(int32 _iKey) const;

		bool IsKeyPressed(int32 _iKey) const;

		bool IsKeyUp(int32 _iKey) const;

		bool IsMouseDown(EMouseActionType _eMouseActionType) const;

		bool IsMousePressed(EMouseActionType _eMouseActionType) const;

		void LockCursor(bool _bCursorLocked);

	public:
		void EnableInput() { m_bInput = true; }

		void DisableInput() { m_bInput = false; }

	/********************
		Data Members
	********************/
	private:
		// 키보드 액시스 맵(axis, key, scale)
		std::unordered_map<std::wstring, std::pair<int32, int32>> m_umapKeyAxisMaps;

		// 키보드 액시스 맵 콜백 함수(axis, callback)
		std::unordered_map<std::wstring, std::function<void(int32)>> m_umapKeyAxisCallbacks;

		// 키보드 액션 맵(action, key)
		std::unordered_map<std::wstring, int32> m_umapKeyActionMaps;

		// 키보드 액션 맵 콜백 함수(action, callback)
		std::unordered_map<std::wstring, std::function<bool(void)>> m_umapKeyActionCallbacks;

	private:
		// 마우스 액시스 맵
		std::unordered_map<std::wstring, std::pair<int32, int32>> m_umapMouseAxisMaps;
		
		// 마우스 액시스 맵 콜백 함수
		std::unordered_map<std::wstring, std::function<void(int32)>> m_umapMouseAxisCallbacks;

		// 마우스 액션 맵
		std::unordered_map<std::wstring, int32> m_umapMouseActionMaps;

		// 마우스 액션 맵 콜백 함수
		std::unordered_map<std::wstring, std::function<void(void)>> m_umapMouseActionCallbacks;

	private:
		std::weak_ptr<CInputManager> m_wpInputManager;

		bool m_bInput = false;
	};
}
