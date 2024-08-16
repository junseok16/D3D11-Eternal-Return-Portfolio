#pragma once

namespace Engine
{
	class CDeviceManager;
	class CViewHandler;

	class CViewLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CViewLoader() = default;

		virtual ~CViewLoader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CViewLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	private:
		HRESULT CreateBackBufferRenderTargetView();

		HRESULT CreateBackBufferDepthStencilView();

		HRESULT BindBackBufferRenderTarget();

	public:
		HRESULT CreateShaderResourceViewFromFile();

		HRESULT CreateDeferredViews();

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CViewHandler> m_wpViewHandler;

		std::wstring m_wstrViewFilePath = L"../../Resource/Textures/";

		RECT m_tClientRect{};
	};
}
