#pragma once

namespace Engine
{
	class CDeviceManager;
	class CInputManager;
	class CLightManager;
	class CCameraManager;
	class CRenderManager;
	class CFrameManager;
	class CCollisionManager;
	class CPostProcessManager;
	class CEffectManager;
	class CGraphicsPipelineManager;

	class ENGINE_DLL CEngineModule final : public enable_shared_from_this<CEngineModule>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEngineModule() = default;

		virtual ~CEngineModule() = default;
		
	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize(HWND _hWnd, HINSTANCE _hInst, uint32 _iWindowSizeX, uint32 _iWindowSizeY);

		HRESULT Initialize();

		HRESULT PostInitialize();

		int32 PreTick(float* _pDeltaSeconds);

		int32 Tick();

		int32 PostTick();

		void PreRender();

		void PostRender();

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		std::shared_ptr<CCameraManager> GetCameraManager() const { return m_spCameraManager; }

		std::shared_ptr<CCollisionManager> GetCollisionManager() const { return m_spCollisionManager; }

		std::shared_ptr<CDeviceManager> GetDeviceManager() const { return m_spDeviceManager; }

		std::shared_ptr<CInputManager> GetInputManager() const { return m_spInputManager; }

		std::shared_ptr<CLightManager> GetLightManager() const { return m_spLightManager; }

		std::shared_ptr<CRenderManager> GetRenderManager() const { return m_spRenderManager; }

		std::shared_ptr<CFrameManager> GetFrameManager() const { return m_spFrameManager; }

		std::shared_ptr<CPostProcessManager> GetPostProcessManager() const { return m_spPostProcessManager; }

		std::shared_ptr<CEffectManager> GetEffectManager() const { return m_spEffectManager; }

	/********************
		Data Members
	********************/
	private:
		std::shared_ptr<CCameraManager> m_spCameraManager = nullptr;

		std::shared_ptr<CCollisionManager> m_spCollisionManager = nullptr;

		std::shared_ptr<CDeviceManager> m_spDeviceManager = nullptr;

		std::shared_ptr<CInputManager> m_spInputManager = nullptr;

		std::shared_ptr<CLightManager> m_spLightManager = nullptr;

		std::shared_ptr<CRenderManager> m_spRenderManager = nullptr;

		std::shared_ptr<CFrameManager> m_spFrameManager = nullptr;

		std::shared_ptr<CPostProcessManager> m_spPostProcessManager = nullptr;

		std::shared_ptr<CEffectManager> m_spEffectManager = nullptr;

		std::shared_ptr<CGraphicsPipelineManager> m_spGraphicsPipelineManager = nullptr;

	private:
		const float m_fFrameRate = 1.0f / 144.0f;

		float m_fSumDeltaSeconds = 0.0f;

		float m_fColorRGBA[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	};
}
