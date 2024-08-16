#pragma once
#include "Manager.h"

namespace Engine
{
	class CEngineModule;
	class CInputManager;
	class CCameraManager;
	class CDeviceManager;
}

namespace Editor
{
	class CEditorCamera;
	class CEffectWindow;
	class CModeWindow;
	class CDetailWindow;
	class CTabWindow;

	class CIMGUIManager final : public CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CIMGUIManager() = default;

		virtual ~CIMGUIManager() = default;
		
	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize(const std::shared_ptr<CEngineModule>& _spEngineModule);

		HRESULT Initialize();

		HRESULT PostInitialize();

		int32 PreTick();

		int32 Tick(float _fDeltaSeconds);

		int32 PostTick();

		void Render();

		virtual void Release() override;
		
	/********************
		Getter/Setter
	********************/
	public:
		const std::shared_ptr<CDetailWindow>& GetDetailWindow() { return m_spDetailWindow; }

		const std::shared_ptr<CModeWindow>& GetModeWindow() { return m_spModeWindow; }

		const std::shared_ptr<CTabWindow>& GetTabWindow() { return m_spTabWindow; }

		const std::shared_ptr<CEditorCamera>& GetEditorCamera() { return m_spEditorCamera; }

	public:
		std::shared_ptr<CInputManager> GetInputManager() { return m_wpInputManager.expired() ? nullptr : m_wpInputManager.lock(); }

	/********************
		Data Members
	********************/
	private:
		std::shared_ptr<CDetailWindow> m_spDetailWindow = nullptr;

		std::shared_ptr<CModeWindow> m_spModeWindow = nullptr;

		std::shared_ptr<CTabWindow> m_spTabWindow = nullptr;

		std::shared_ptr<CEffectWindow> m_spEffectWindow = nullptr;

		std::shared_ptr<CEditorCamera> m_spEditorCamera = nullptr;

	private:
		std::weak_ptr<CEngineModule> m_wpEngineModule;

		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CCameraManager> m_wpCameraManager;

		std::weak_ptr<CInputManager> m_wpInputManager;

	private:
		EEditorState m_eEditorState = EEditorState::EDIT;
	};
}
