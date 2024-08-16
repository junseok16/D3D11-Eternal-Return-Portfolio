#include "pch.h"
#include "EngineModule.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "DeviceManager.h"
#include "InputManager.h"
#include "LightManager.h"
#include "RenderManager.h"
#include "FrameManager.h"
#include "PostProcessManager.h"
#include "EffectManager.h"
#include "GraphicsPipelineManager.h"

#include "ViewHandler.h"

HRESULT Engine::CEngineModule::PreInitialize(HWND _hWnd, HINSTANCE _hInst, uint32 _iWindowSizeX, uint32 _iWindowSizeY)
{
	m_spDeviceManager			= CManager::Create<CDeviceManager>(shared_from_this());
	m_spCameraManager			= CManager::Create<CCameraManager>(shared_from_this());
	m_spCollisionManager		= CManager::Create<CCollisionManager>(shared_from_this());
	m_spInputManager			= CManager::Create<CInputManager>(shared_from_this());
	m_spLightManager			= CManager::Create<CLightManager>(shared_from_this());
	m_spRenderManager			= CManager::Create<CRenderManager>(shared_from_this());
	m_spFrameManager			= CManager::Create<CFrameManager>(shared_from_this());
	m_spPostProcessManager		= CManager::Create<CPostProcessManager>(shared_from_this());
	m_spEffectManager			= CManager::Create<CEffectManager>(shared_from_this());
	m_spGraphicsPipelineManager = CGraphicsPipelineManager::GetInstance();


	m_spDeviceManager->PreInitialize(_hWnd, _hInst, _iWindowSizeX, _iWindowSizeY);
	m_spGraphicsPipelineManager->PreInitialize(m_spDeviceManager->GetDevice(), m_spDeviceManager->GetDeviceContext());
	m_spCameraManager->PreInitialize();
	m_spCollisionManager->PreInitialize();
	m_spInputManager->PreInitialize();
	m_spLightManager->PreInitialize();
	m_spRenderManager->PreInitialize();
	m_spFrameManager->PreInitialize();
	m_spPostProcessManager->PreInitialize(m_spLightManager);
	m_spEffectManager->PreInitialize();
	return S_OK;
}

HRESULT Engine::CEngineModule::Initialize()
{
	m_spDeviceManager->Initialize();
	m_spGraphicsPipelineManager->Initialize();
	m_spCameraManager->Initialize();
	m_spCollisionManager->Initialize();
	m_spInputManager->Initialize();
	m_spRenderManager->Initialize();
	m_spFrameManager->Initialize();
	m_spEffectManager->Initialize();
	return S_OK;
}

HRESULT Engine::CEngineModule::PostInitialize()
{
	m_spPostProcessManager->Initialize();
	m_spLightManager->Initialize();
	return S_OK;
}

int32 Engine::CEngineModule::PreTick(float* _pDeltaSeconds)
{
	m_fSumDeltaSeconds += m_spFrameManager->Tick(L"OuterLoop");
	if (m_fSumDeltaSeconds < m_fFrameRate)
	{
		*_pDeltaSeconds = 0.0f;
		return -1;
	}

	m_fSumDeltaSeconds = 0.0f;
	*_pDeltaSeconds = m_spFrameManager->Tick(L"InnerLoop");
	
	m_spInputManager->Tick();
	m_spCollisionManager->Tick();
	return 0;
}

int32 Engine::CEngineModule::Tick()
{
	m_spCameraManager->Tick();
	return 0;
}

int32 Engine::CEngineModule::PostTick()
{
	m_spPostProcessManager->Tick();
	m_spRenderManager->Tick();
	return 0;
}

void Engine::CEngineModule::PreRender()
{
	m_spDeviceManager->GetViewHandler()->ClearRenderTargetView(L"RTV_BACK_BUFFER", m_fColorRGBA);
	m_spDeviceManager->GetViewHandler()->ClearDepthStencilView(L"DSV_BACK_BUFFER");
	m_spRenderManager->Render();
}

void Engine::CEngineModule::PostRender()
{
	m_spDeviceManager->Present();
}

void Engine::CEngineModule::Release()
{
	m_spGraphicsPipelineManager->Release();
	m_spEffectManager->Release();
	m_spPostProcessManager->Release();
	m_spRenderManager->Release();
	m_spCollisionManager->Release();
	m_spCameraManager->Release();
	m_spLightManager->Release();
	m_spFrameManager->Release();
	m_spInputManager->Release();
	m_spDeviceManager->Release();

	m_spGraphicsPipelineManager = nullptr;
	m_spEffectManager = nullptr;
	m_spPostProcessManager = nullptr;
	m_spRenderManager = nullptr;
	m_spCollisionManager = nullptr;
	m_spCameraManager = nullptr;
	m_spLightManager = nullptr;
	m_spFrameManager = nullptr;
	m_spInputManager = nullptr;
	m_spDeviceManager = nullptr;
}
