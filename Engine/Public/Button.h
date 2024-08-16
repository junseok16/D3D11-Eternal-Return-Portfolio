#pragma once
#include "UI.h"

namespace Engine
{
	class CInputManager;
	class CDeviceManager;
	class CGeometryComponent;

	class ENGINE_DLL CButton : public CUI
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CButton() = default;

		virtual ~CButton() = default;
		
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
		
	private:
		virtual void TickButtonState(float _fDeltaSeconds);

	/********************
		Getter/Setter
	********************/
	public:
		void SetButtonState(EButtonState _eButtonState) { m_eButtonState = _eButtonState; }

		void SetButtonMouseState(EButtonMouseState _eButtonMouseState) { m_eButtonMouseState = _eButtonMouseState; }

		void SetPrimitiveType(EPrimitiveType _ePrimitiveType) { m_ePrimitiveType = _ePrimitiveType; }

		// void SetButtonNames(const std::array<std::wstring, 3>& _arrButtonNames) { m_arrButtonNames = _arrButtonNames; }
		
		void SetButtonNames(const std::vector<std::wstring>& _vecButtonNames) { m_vecButtonNames = _vecButtonNames; }

		void SetTextureIndex(uint32 _iTextureIndex);

	/********************
		Methods
	********************/
	public:
		virtual void OnButtonUpIn();

		virtual void OnButtonUpOut();

		template<typename T>
		void AddOnButtonUpInDelegate(std::shared_ptr<T> _spOwner, void(T::* function)())
		{
			m_fnOnButtonUpInDelegate = [_spOwner, function]() { (_spOwner.get()->*function)(); };
		}

		template<typename T>
		void AddOnButtonUpOutDelegate(std::shared_ptr<T> _spOwner, void(T::*function)())
		{
			m_fnOnButtonUpOutDelegate = [_spOwner, function](){ (_spOwner.get()->*function)(); };
		}

	public:
		bool IsMouseInButton();

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CGeometryComponent> m_wpButtonComponent;

		EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

		EButtonState m_eButtonState = EButtonState::INACTIVE;

		EButtonMouseState m_eButtonMouseState = EButtonMouseState::ENUM_END;

		std::vector<std::wstring> m_vecButtonNames;

		// std::array<std::wstring, 3> m_arrButtonNames{ L"" };

	protected:
		std::function<void(void)> m_fnOnButtonUpInDelegate = nullptr;

		std::function<void(void)> m_fnOnButtonUpOutDelegate = nullptr;

		float m_fSumDeltaSeconds = 0.0f;

	protected:
		HWND m_hWnd{};

		RECT m_tButtonRect{};

		POINT m_tMousePosition{ 0, 0 };

	protected:
		std::weak_ptr<CInputManager> m_wpInputManager;
	};
}
