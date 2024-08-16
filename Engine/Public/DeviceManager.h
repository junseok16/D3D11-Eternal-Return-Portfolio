#pragma once
#include "Manager.h"

namespace Engine
{
	class CViewHandler;
	class CBufferHandler;
	class CStateHandler;
	class CShaderHandler;
	class CModelHandler;
	class CNavHandler;
	class CFontHandler;
	class CEffectHandler;
	class CSoundHandler;

	class ENGINE_DLL CDeviceManager final : public Engine::CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CDeviceManager() = default;

		virtual ~CDeviceManager() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize(HWND _hWnd, HINSTANCE _hInst, uint32 _iWindowSizeX, uint32 _iWindowSizeY);

		HRESULT Initialize();

		int32 Tick();

		virtual void Release() override;

	private:
		HRESULT CreateDevice();

		HRESULT CreateSwapChain();

		HRESULT CreateViewports();

	/********************
		Methods
	********************/
	public:
		void RSSetViewports(UINT _iNumViewports, const D3D11_VIEWPORT* _pViewports);

		HRESULT Present();
		
	/********************
		Getter/Setter
	********************/
	public:
		HWND GetWindowHandle() const { return m_hWnd; }

		HINSTANCE GetInstanceHandle() const { return m_hInst; }

		uint32 GetWindowSizeX() const { return m_iWindowSizeX; }

		uint32 GetWindowSizeY() const { return m_iWindowSizeY; }

		const ComPtr<ID3D11Device>& GetDevice() { return m_cpDevice; }

		const ComPtr<ID3D11DeviceContext>& GetDeviceContext() { return m_cpDeviceContext; }

		const ComPtr<IDXGISwapChain>& GetSwapChain() { return m_cpSwapChain; }

	public:
		std::shared_ptr<CShaderHandler> GetShaderHandler() const { return m_spShaderHandler; }

		std::shared_ptr<CBufferHandler> GetBufferHandler() const { return m_spBufferHandler; }

		std::shared_ptr<CViewHandler> GetViewHandler() const { return m_spViewHandler; }

		std::shared_ptr<CStateHandler> GetStateHandler() const { return m_spStateHandler; }

		std::shared_ptr<CNavHandler> GetNavHanlder() const { return m_spNavHandler; }

		std::shared_ptr<CSoundHandler> GetSoundHandler() const { return m_spSoundHandler; }

	/********************
		Data Members
	********************/
	private:
		HWND m_hWnd{};

		HINSTANCE m_hInst{};

		uint32 m_iWindowSizeX = 0;

		uint32 m_iWindowSizeY = 0;

	private:
		ComPtr<ID3D11Device> m_cpDevice = nullptr;

		ComPtr<ID3D11DeviceContext> m_cpDeviceContext = nullptr;

		ComPtr<IDXGISwapChain> m_cpSwapChain = nullptr;

	private:
		std::shared_ptr<CShaderHandler> m_spShaderHandler = nullptr;

		std::shared_ptr<CBufferHandler> m_spBufferHandler = nullptr;

		std::shared_ptr<CViewHandler> m_spViewHandler = nullptr;

		std::shared_ptr<CStateHandler> m_spStateHandler = nullptr;

		std::shared_ptr<CModelHandler> m_spModelHandler = nullptr;

		std::shared_ptr<CNavHandler> m_spNavHandler = nullptr;

		std::shared_ptr<CFontHandler> m_spFontHandler = nullptr;

		std::shared_ptr<CEffectHandler> m_spEffectHandler = nullptr;

		std::shared_ptr<CSoundHandler> m_spSoundHandler = nullptr;
	};
}
