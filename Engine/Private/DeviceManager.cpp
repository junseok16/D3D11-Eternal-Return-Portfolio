#include "pch.h"
#include "DeviceManager.h"

#include "BufferHandler.h"
#include "ViewHandler.h"
#include "ShaderHandler.h"
#include "StateHandler.h"
#include "ModelHandler.h"
#include "NavHandler.h"
#include "FontHandler.h"
#include "EffectHandler.h"
#include "SoundHandler.h"

HRESULT Engine::CDeviceManager::PreInitialize(HWND _hWnd, HINSTANCE _hInst, uint32 _iWindowSizeX, uint32 _iWindowSizeY)
{
	m_hWnd = _hWnd;
	m_hInst = _hInst;
	m_iWindowSizeX = _iWindowSizeX;
	m_iWindowSizeY = _iWindowSizeY;

	ENSUREF(CreateDevice(), L"Failed to create device, device context.");
	ENSUREF(CreateSwapChain(), L"Failed to create swap chain.");
	ENSUREF(CreateViewports(), L"Failed to create viewport");
	return S_OK;
}

HRESULT Engine::CDeviceManager::Initialize()
{
	m_spViewHandler = CViewHandler::GetInstance();
	m_spBufferHandler = CBufferHandler::GetInstance();
	m_spShaderHandler = CShaderHandler::GetInstance();
	m_spStateHandler = CStateHandler::GetInstance();
	m_spModelHandler = CModelHandler::GetInstance();
	m_spNavHandler = CNavHandler::GetInstance();
	m_spFontHandler = CFontHandler::GetInstance();
	m_spEffectHandler = CEffectHandler::GetInstance();
	m_spSoundHandler = CSoundHandler::GetInstance();

	m_spViewHandler->Initialize(static_pointer_cast<CDeviceManager>(shared_from_this()));
	m_spBufferHandler->Initialize(static_pointer_cast<CDeviceManager>(shared_from_this()));
	m_spShaderHandler->Initialize(static_pointer_cast<CDeviceManager>(shared_from_this()));
	m_spStateHandler->Initialize(static_pointer_cast<CDeviceManager>(shared_from_this()));
	m_spModelHandler->Initialize(static_pointer_cast<CDeviceManager>(shared_from_this()));
	m_spNavHandler->Initialize(static_pointer_cast<CDeviceManager>(shared_from_this()));
	m_spFontHandler->Initialize(static_pointer_cast<CDeviceManager>(shared_from_this()));
	m_spEffectHandler->Initialize(static_pointer_cast<CDeviceManager>(shared_from_this()));
	m_spSoundHandler->Initialize();
	return S_OK;
}

int32 Engine::CDeviceManager::Tick()
{
	return 0;
}

void Engine::CDeviceManager::Release()
{
	m_spSoundHandler->Release();
	m_spShaderHandler->Release();
	m_spBufferHandler->Release();
	m_spViewHandler->Release();
	m_spStateHandler->Release();
	m_spModelHandler->Release();
	m_spNavHandler->Release();
	m_spFontHandler->Release();
	m_spEffectHandler->Release();

	m_spSoundHandler = nullptr;
	m_spShaderHandler = nullptr;
	m_spBufferHandler = nullptr;
	m_spViewHandler = nullptr;
	m_spStateHandler = nullptr;
	m_spModelHandler = nullptr;
	m_spNavHandler = nullptr;
	m_spFontHandler = nullptr;
	m_spEffectHandler = nullptr;

	m_cpSwapChain = nullptr;
	m_cpDeviceContext = nullptr;
	m_cpDevice = nullptr;
}

HRESULT Engine::CDeviceManager::CreateDevice()
{
	UINT iCreateDeviceFlags = 0;

#ifdef _DEBUG
	iCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL eFeatureLevel;

	const D3D_FEATURE_LEVEL eFeatureLevels[2] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_9_3
	};

	// 디바이스를 생성하면서 DX11을 지원하는지 파악합니다.
	if (FAILED(D3D11CreateDevice
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		iCreateDeviceFlags,
		eFeatureLevels,
		ARRAYSIZE(eFeatureLevels),
		D3D11_SDK_VERSION,
		m_cpDevice.GetAddressOf(),
		&eFeatureLevel,
		m_cpDeviceContext.GetAddressOf()
	)))
	{
		return E_FAIL;
	}
	
	// DX11을 지원하지 않는 경우, 실패합니다.
	if (eFeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MESSAGE_BOX(L"D3D feature level 11 is not supported.");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Engine::CDeviceManager::CreateSwapChain()
{
	ComPtr<IDXGIDevice> cpGIDevice = nullptr;
	m_cpDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&cpGIDevice);

	ComPtr<IDXGIAdapter> cpGIAdapter = nullptr;
	cpGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&cpGIAdapter);

	ComPtr<IDXGIFactory> cpGIFactory = nullptr;
	cpGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&cpGIFactory);

	// 스왑 체인을 생성합니다.
	DXGI_SWAP_CHAIN_DESC tSwapChainDesc;
	ZeroMemory(&tSwapChainDesc, sizeof(tSwapChainDesc));

	tSwapChainDesc.BufferDesc.Width = m_iWindowSizeX;
	tSwapChainDesc.BufferDesc.Height = m_iWindowSizeY;
	tSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tSwapChainDesc.BufferCount = 2;
	tSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	tSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	tSwapChainDesc.SampleDesc.Count = 1;
	tSwapChainDesc.SampleDesc.Quality = 0;
	tSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tSwapChainDesc.OutputWindow = m_hWnd;
	tSwapChainDesc.Windowed = TRUE;
	tSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	tSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	return cpGIFactory->CreateSwapChain(m_cpDevice.Get(), &tSwapChainDesc, m_cpSwapChain.GetAddressOf());
}

HRESULT Engine::CDeviceManager::CreateViewports()
{
	D3D11_VIEWPORT tViewport;
	ZeroMemory(&tViewport, sizeof(tViewport));
	tViewport.TopLeftX = 0.0f;
	tViewport.TopLeftY = 0.0f;
	tViewport.Width = static_cast<FLOAT>(m_iWindowSizeX);
	tViewport.Height = static_cast<FLOAT>(m_iWindowSizeY);
	tViewport.MinDepth = 0.0f;
	tViewport.MaxDepth = 1.0f;
	RSSetViewports(1, &tViewport);
	return S_OK;
}

void Engine::CDeviceManager::RSSetViewports(UINT _iNumViewports, const D3D11_VIEWPORT* _pViewports)
{
	m_cpDeviceContext->RSSetViewports(_iNumViewports, _pViewports);
}

HRESULT Engine::CDeviceManager::Present()
{
	return m_cpSwapChain->Present(0, 0);
}
