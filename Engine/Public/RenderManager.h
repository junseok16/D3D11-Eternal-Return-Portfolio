#pragma once
#include "Manager.h"

namespace Engine
{
	class CPostProcessManager;
	class CEffectManager;
	class CGraphicsPipelineManager;
	class CDeviceManager;

	class CViewHandler;
	class CStateHandler;
	class CActor;
	class CUI;

	class CRenderManager final : public Engine::CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CRenderManager() = default;

		virtual ~CRenderManager() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize();

		HRESULT Initialize();

		int32 Tick();

		void Render();

		virtual void Release() override;

	/********************
		Methods
	********************/
	public:
		HRESULT AddActorToRenderer(std::shared_ptr<CActor> _spActor, ERenderType _eRenderType);

		HRESULT RemoveActorFromRenderer(std::shared_ptr<CActor> _spActor, ERenderType _eRenderType);

	private:
		void PreRender();

		void RenderShadow();

		void RenderOpaqueObject();

		void RenderLight();

		void RenderPostProcess();

		void RenderParticle();

		void RenderTranslucentObject();

		void RenderOpaqueUserInterface();

		void RenderTranslucentUserInterface();

		void PostRender();

		void RenderDebug();

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CPostProcessManager> m_wpPostProcessManager;

		std::weak_ptr<CEffectManager> m_wpEffectManager;

		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CGraphicsPipelineManager> m_wpGraphicsPipelineManager;

		std::weak_ptr<CViewHandler> m_wpViewHandler;

	private:
		// 렌더할 액터들
		std::array<std::list<std::shared_ptr<CActor>>, (uint8)ERenderType::ENUM_END> m_arrActors;

		// 렌더할 사용자 인터페이스들
		std::array<std::list<std::shared_ptr<CUI>>, (uint8)ERenderType::ENUM_END> m_arrUIs;
	};
}
