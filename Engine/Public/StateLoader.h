#pragma once

namespace Engine
{
	class CDeviceManager;
	class CStateHandler;

	class CStateLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStateLoader() = default;

		virtual ~CStateLoader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CStateLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	private:
		HRESULT LoadRasterizerState();

		HRESULT LoadDepthStencilState();

		HRESULT LoadSamplerState();

		HRESULT LoadBlendState();

		void SetStates();

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CStateHandler> m_wpStateHandler;

		std::wstring m_wstrStateFilePath = L"";
	};
}
