#pragma once
#include "Manager.h"

namespace Engine
{
	class CDeviceManager;

	class ENGINE_DLL CInputManager final : public Engine::CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CInputManager() = default;

		virtual ~CInputManager() = default;
		
	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize();

		HRESULT Initialize();

		int32 Tick();

		virtual void Release() override;

	/********************
		Getter/Setter
	********************/
	public:
		bool IsKeyDown(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::DOWN; }

		bool IsKeyPressed(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::PRESSED; }

		bool IsKeyUp(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::UP; }

		bool IsKeyReleased(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::RELEASED; }

		bool IsMouseDown(EMouseActionType _eMouseActionType) { return GetMouseState(_eMouseActionType) == EMouseState::DOWN; }

		bool IsMousePressed(EMouseActionType _eMouseActionType) { return GetMouseState(_eMouseActionType) == EMouseState::PRESSED; }

		bool IsMouseUp(EMouseActionType _eMouseActionType) { return GetMouseState(_eMouseActionType) == EMouseState::UP; }

		bool IsMouseReleased(EMouseActionType _eMouseActionType) { return GetMouseState(_eMouseActionType) == EMouseState::RELEASED; }

		bool IsMouseMoved(EMouseAxisType _eMouseAxisType) { return m_arrMouseDelta[(int32)_eMouseAxisType] != 0; }

		int32 GetMouseDelta(EMouseAxisType _eMouseAxisType) { return m_arrMouseDelta[(int32)_eMouseAxisType]; }

		std::tuple<int32, int32, int32> GetMouseDeltaAll() { return { m_arrMouseDelta[(int32)EMouseAxisType::X_AXIS], m_arrMouseDelta[(int32)EMouseAxisType::Y_AXIS],m_arrMouseDelta[(int32)EMouseAxisType::Z_AXIS] }; }

		POINT GetCursorScreenPos();

		std::pair<float, float> GetCursorNDCPos();

		void LockCursor(bool _bCursorLocked) { m_bCursorLocked = _bCursorLocked; }

	private:
		EKeyState GetKeyState(uint8 _iKey) { return m_arrKeyStates[_iKey]; }

		EMouseState GetMouseState(EMouseActionType _eMouseActionType) { return m_arrMouseStates[(int8)_eMouseActionType]; }

	/********************
		Data Members
	********************/
	private:
		LPDIRECTINPUT8 m_pDeviceInput = nullptr;

		LPDIRECTINPUTDEVICE8 m_pDIKeyDevice = nullptr;

		LPDIRECTINPUTDEVICE8 m_pDIMouseDevice = nullptr;

	private:
		std::array<EKeyState, 256> m_arrKeyStates{ EKeyState::RELEASED };

		std::array<EMouseState, 3> m_arrMouseStates{ EMouseState::RELEASED };

		std::array<int32, 3> m_arrMouseDelta{ 0 };

	private:
		bool m_bCursorLocked = false;

		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		HWND m_hWnd{};

		float m_fWindowSizeX = 0.0f;

		float m_fWindowSizeY = 0.0f;

		POINT m_tCursorPoint{ 640, 360 };
	};
}
