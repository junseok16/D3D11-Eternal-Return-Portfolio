#pragma once

namespace Engine
{
	class CStateHandler;

	class CDepthStencil final
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CDepthStencil() = default;

		virtual ~CDepthStencil() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CDepthStencil> Create(const std::wstring& _wstrDepthStencilName);

		virtual HRESULT Initialize(const std::wstring& _wstrDepthStencilName);

		virtual void Release();
		
	/******************
		Methods
	******************/
	public:
		void OMSetDepthStencilState();

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CStateHandler> m_wpStateHandler;

	private:
		ComPtr<ID3D11DepthStencilState> m_cpDepthStencilState = nullptr;

	private:
		std::wstring m_wstrDepthStencilName = L"";
	};
}

