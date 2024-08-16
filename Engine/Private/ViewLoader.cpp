#include "pch.h"
#include "ViewLoader.h"

#include "DeviceManager.h"
#include "ViewHandler.h"

std::shared_ptr<CViewLoader> Engine::CViewLoader::Create()
{
	const std::shared_ptr<CViewLoader> spLoader = make_shared<CViewLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create view loader.");
	return spLoader;
}

HRESULT Engine::CViewLoader::Initialize()
{
	m_wpViewHandler = CViewHandler::GetInstance();
	m_wpDeviceManager = CViewHandler::GetInstance()->GetDeviceManager();

	CreateBackBufferRenderTargetView();
	CreateBackBufferDepthStencilView();
	
	BindBackBufferRenderTarget();

	// 외부 파일을 불러옵니다.
	CreateShaderResourceViewFromFile();
	CreateDeferredViews();
	return S_OK;
}

void Engine::CViewLoader::Release()
{
}

HRESULT Engine::CViewLoader::CreateBackBufferRenderTargetView()
{
	ComPtr<ID3D11Texture2D> cpBackBufferTexture2D = nullptr;
	ENSURE(m_wpDeviceManager.lock()->GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(cpBackBufferTexture2D.GetAddressOf())));
	m_wpViewHandler.lock()->CreateRenderTargetView(L"RTV_BACK_BUFFER", cpBackBufferTexture2D.Get());
	return S_OK;
}

HRESULT Engine::CViewLoader::CreateBackBufferDepthStencilView()
{
	GetClientRect(m_wpDeviceManager.lock()->GetWindowHandle(), &m_tClientRect);

	{
		D3D11_TEXTURE2D_DESC tTexture2DDesc;
		ZeroMemory(&tTexture2DDesc, sizeof(tTexture2DDesc));
		tTexture2DDesc.Width = m_tClientRect.right - m_tClientRect.left;
		tTexture2DDesc.Height = m_tClientRect.bottom - m_tClientRect.top;
		tTexture2DDesc.MipLevels = 1;
		tTexture2DDesc.ArraySize = 1;
		tTexture2DDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		tTexture2DDesc.SampleDesc.Count = 1;
		tTexture2DDesc.SampleDesc.Quality = 0;
		tTexture2DDesc.Usage = D3D11_USAGE_DEFAULT;
		tTexture2DDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		tTexture2DDesc.CPUAccessFlags = 0;
		tTexture2DDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> cpTexture2D = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateTexture2D(&tTexture2DDesc, nullptr, cpTexture2D.GetAddressOf()));
		m_wpViewHandler.lock()->CreateDepthStencilView(L"DSV_BACK_BUFFER", cpTexture2D.Get());
	}
	
	{
		D3D11_TEXTURE2D_DESC tTexture2DDesc;
		ZeroMemory(&tTexture2DDesc, sizeof(tTexture2DDesc));
		tTexture2DDesc.Width = 8192;
		tTexture2DDesc.Height = 4608;
		tTexture2DDesc.MipLevels = 1;
		tTexture2DDesc.ArraySize = 1;
		tTexture2DDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		tTexture2DDesc.SampleDesc.Quality = 0;
		tTexture2DDesc.SampleDesc.Count = 1;
		tTexture2DDesc.Usage = D3D11_USAGE_DEFAULT;
		tTexture2DDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		tTexture2DDesc.CPUAccessFlags = 0;
		tTexture2DDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> cpTexture2D = nullptr;
		m_wpDeviceManager.lock()->GetDevice()->CreateTexture2D(&tTexture2DDesc, nullptr, cpTexture2D.GetAddressOf());
		m_wpViewHandler.lock()->CreateDepthStencilView(L"DSV_SHADOW", cpTexture2D.Get());
	}

	return S_OK;
}

HRESULT Engine::CViewLoader::BindBackBufferRenderTarget()
{
	ComPtr<ID3D11RenderTargetView> cpRenderTargetView = m_wpViewHandler.lock()->FindRenderTargetView(L"RTV_BACK_BUFFER");
	ComPtr<ID3D11DepthStencilView> cpDepthStencilView = m_wpViewHandler.lock()->FindDepthStencilView(L"DSV_BACK_BUFFER");
	CHECK(cpRenderTargetView != nullptr);
	CHECK(cpDepthStencilView != nullptr);

	array<ComPtr<ID3D11RenderTargetView>, 1> arrRenderTargetViews{ cpRenderTargetView };
	m_wpViewHandler.lock()->OMSetRenderTargets(static_cast<UINT>(arrRenderTargetViews.size()), arrRenderTargetViews.data()->GetAddressOf(), cpDepthStencilView.Get());
	return S_OK;
}

HRESULT Engine::CViewLoader::CreateDeferredViews()
{
	{
		D3D11_TEXTURE2D_DESC tTexture2DDesc;
		ZeroMemory(&tTexture2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
		tTexture2DDesc.Width = m_tClientRect.right - m_tClientRect.left;
		tTexture2DDesc.Height = m_tClientRect.bottom - m_tClientRect.top;
		tTexture2DDesc.MipLevels = 1;
		tTexture2DDesc.ArraySize = 1;
		tTexture2DDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		tTexture2DDesc.SampleDesc.Quality = 0;
		tTexture2DDesc.SampleDesc.Count = 1;
		tTexture2DDesc.Usage = D3D11_USAGE_DEFAULT;
		tTexture2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tTexture2DDesc.CPUAccessFlags = 0;
		tTexture2DDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> cpDiffuseTexture2D = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateTexture2D(&tTexture2DDesc, nullptr, cpDiffuseTexture2D.GetAddressOf()));
		ENSURE(m_wpViewHandler.lock()->CreateRenderTargetView(L"DIFFUSE", cpDiffuseTexture2D.Get()));
		ENSURE(m_wpViewHandler.lock()->CreateShaderResourceView(L"DIFFUSE", cpDiffuseTexture2D.Get()));
	}
	
	{
		D3D11_TEXTURE2D_DESC tTexture2DDesc;
		ZeroMemory(&tTexture2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
		tTexture2DDesc.Width = m_tClientRect.right - m_tClientRect.left;
		tTexture2DDesc.Height = m_tClientRect.bottom - m_tClientRect.top;
		tTexture2DDesc.MipLevels = 1;
		tTexture2DDesc.ArraySize = 1;
		tTexture2DDesc.Format = DXGI_FORMAT_R16G16B16A16_UNORM;
		tTexture2DDesc.SampleDesc.Quality = 0;
		tTexture2DDesc.SampleDesc.Count = 1;
		tTexture2DDesc.Usage = D3D11_USAGE_DEFAULT;
		tTexture2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tTexture2DDesc.CPUAccessFlags = 0;
		tTexture2DDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> cpDiffuseTexture2D = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateTexture2D(&tTexture2DDesc, nullptr, cpDiffuseTexture2D.GetAddressOf()));
		ENSURE(m_wpViewHandler.lock()->CreateRenderTargetView(L"NORMAL", cpDiffuseTexture2D.Get()));
		ENSURE(m_wpViewHandler.lock()->CreateShaderResourceView(L"NORMAL", cpDiffuseTexture2D.Get()));
	}

	{
		D3D11_TEXTURE2D_DESC tTexture2DDesc;
		ZeroMemory(&tTexture2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
		tTexture2DDesc.Width = m_tClientRect.right - m_tClientRect.left;
		tTexture2DDesc.Height = m_tClientRect.bottom - m_tClientRect.top;
		tTexture2DDesc.MipLevels = 1;
		tTexture2DDesc.ArraySize = 1;
		tTexture2DDesc.Format = DXGI_FORMAT_R16G16B16A16_UNORM;
		tTexture2DDesc.SampleDesc.Quality = 0;
		tTexture2DDesc.SampleDesc.Count = 1;
		tTexture2DDesc.Usage = D3D11_USAGE_DEFAULT;
		tTexture2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tTexture2DDesc.CPUAccessFlags = 0;
		tTexture2DDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> cpDiffuseTexture2D = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateTexture2D(&tTexture2DDesc, nullptr, cpDiffuseTexture2D.GetAddressOf()));
		ENSURE(m_wpViewHandler.lock()->CreateRenderTargetView(L"SHADE", cpDiffuseTexture2D.Get()));
		ENSURE(m_wpViewHandler.lock()->CreateShaderResourceView(L"SHADE", cpDiffuseTexture2D.Get()));
	}

	{
		D3D11_TEXTURE2D_DESC tTexture2DDesc;
		ZeroMemory(&tTexture2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
		tTexture2DDesc.Width = m_tClientRect.right - m_tClientRect.left;
		tTexture2DDesc.Height = m_tClientRect.bottom - m_tClientRect.top;
		tTexture2DDesc.MipLevels = 1;
		tTexture2DDesc.ArraySize = 1;
		tTexture2DDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		tTexture2DDesc.SampleDesc.Quality = 0;
		tTexture2DDesc.SampleDesc.Count = 1;
		tTexture2DDesc.Usage = D3D11_USAGE_DEFAULT;
		tTexture2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tTexture2DDesc.CPUAccessFlags = 0;
		tTexture2DDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> cpDiffuseTexture2D = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateTexture2D(&tTexture2DDesc, nullptr, cpDiffuseTexture2D.GetAddressOf()));
		ENSURE(m_wpViewHandler.lock()->CreateRenderTargetView(L"DEPTH", cpDiffuseTexture2D.Get()));
		ENSURE(m_wpViewHandler.lock()->CreateShaderResourceView(L"DEPTH", cpDiffuseTexture2D.Get()));
	}

	{
		D3D11_TEXTURE2D_DESC tTexture2DDesc;
		ZeroMemory(&tTexture2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
		tTexture2DDesc.Width = 8192;
		tTexture2DDesc.Height = 4608;
		tTexture2DDesc.MipLevels = 1;
		tTexture2DDesc.ArraySize = 1;
		tTexture2DDesc.Format = DXGI_FORMAT_R32_FLOAT;
		tTexture2DDesc.SampleDesc.Quality = 0;
		tTexture2DDesc.SampleDesc.Count = 1;
		tTexture2DDesc.Usage = D3D11_USAGE_DEFAULT;
		tTexture2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tTexture2DDesc.CPUAccessFlags = 0;
		tTexture2DDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> cpShadowTexture2D = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateTexture2D(&tTexture2DDesc, nullptr, cpShadowTexture2D.GetAddressOf()));
		ENSURE(m_wpViewHandler.lock()->CreateRenderTargetView(L"SHADOW", cpShadowTexture2D.Get()));
		ENSURE(m_wpViewHandler.lock()->CreateShaderResourceView(L"SHADOW", cpShadowTexture2D.Get()));
	}

	{
		// 뷰를 생성합니다.
		shared_ptr<TView> spDiffuseView = m_wpViewHandler.lock()->CreateView(L"DIFFUSE");
		shared_ptr<TView> spNormalView = m_wpViewHandler.lock()->CreateView(L"NORMAL");
		shared_ptr<TView> spShadeView = m_wpViewHandler.lock()->CreateView(L"SHADE");
		shared_ptr<TView> spDepthView = m_wpViewHandler.lock()->CreateView(L"DEPTH");
		shared_ptr<TView> spShadowView = m_wpViewHandler.lock()->CreateView(L"SHADOW");

		spDiffuseView->SetWorldMatrix(0.0f, 0.0f, 200.0f, 200.0f);
		spNormalView->SetWorldMatrix(0.0f, 0.0f, 200.0f, 200.0f);
		spShadeView->SetWorldMatrix(0.0f, 0.0f, 200.0f, 200.0f);
		spDepthView->SetWorldMatrix(0.0f, 0.0f, 200.0f, 200.0f);
		spShadowView->SetWorldMatrix(0.0f, 0.0f, 200.0f, 200.0f);

		spDiffuseView->SetClearColor({ 1.0f, 1.0f, 1.0f, 0.0f });
		spNormalView->SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		spShadeView->SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		spDepthView->SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		spShadowView->SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}

	{
		// 뷰 그룹을 생성합니다.
		m_wpViewHandler.lock()->CreateViewGroup(L"VG_OPAQUE_OBJECT");
		m_wpViewHandler.lock()->CreateViewGroup(L"VG_LIGHT");
		m_wpViewHandler.lock()->CreateViewGroup(L"VG_SHADOW");

		// 뷰 그룹에 뷰를 추가합니다.
		m_wpViewHandler.lock()->AddViewGroup(L"VG_OPAQUE_OBJECT", L"DIFFUSE");
		m_wpViewHandler.lock()->AddViewGroup(L"VG_OPAQUE_OBJECT", L"NORMAL");
		m_wpViewHandler.lock()->AddViewGroup(L"VG_OPAQUE_OBJECT", L"DEPTH");
		m_wpViewHandler.lock()->AddViewGroup(L"VG_LIGHT", L"SHADE");
		m_wpViewHandler.lock()->AddViewGroup(L"VG_SHADOW", L"SHADOW");
	}
	return S_OK;
}

HRESULT Engine::CViewLoader::CreateShaderResourceViewFromFile()
{
	for (const filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrViewFilePath))
	{
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = nullptr;
		wstring wstrTextureFileExtenstion = fsEntry.path().extension().generic_wstring();
		if (wstrTextureFileExtenstion == L".dds" || wstrTextureFileExtenstion == L".DDS")
		{
			// dds 확장자
			if (FAILED(CreateDDSTextureFromFile(m_wpDeviceManager.lock()->GetDevice().Get(), fsEntry.path().c_str(), nullptr, cpShaderResourceView.GetAddressOf()))) { return E_FAIL; }
		}
		else if (wstrTextureFileExtenstion == L".png" || wstrTextureFileExtenstion == L".PNG" || wstrTextureFileExtenstion == L".jpg" || wstrTextureFileExtenstion == L".JPG")
		{
			// jpg, png 확장자
			if (FAILED(CreateWICTextureFromFile(m_wpDeviceManager.lock()->GetDevice().Get(), fsEntry.path().c_str(), nullptr, cpShaderResourceView.GetAddressOf()))) { return E_FAIL; }
		}
		else
		{
			// 기타 확장자
			continue;
		}

		wstring wstrTextureFileName = fsEntry.path().stem().generic_wstring();
		m_wpViewHandler.lock()->AddShaderResourceView(wstrTextureFileName, cpShaderResourceView.Get());
	}
	return S_OK;
}
