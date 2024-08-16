#pragma once

namespace Engine
{
	class CStateHandler;

	class CSampler final
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CSampler() = default;

		virtual ~CSampler() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CSampler> Create(const std::wstring& _wstrSamplerName, uint8 _iBindPoint);

		virtual HRESULT Initialize(const std::wstring& _wstrSamplerName, uint8 _iBindPoint);

		virtual void Release();
		
	/******************
		Methods
	******************/
	public:
		void PSSetSamplers();

		void VSSetSamplers();
		
		void GSSetSamplers();

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CStateHandler> m_wpStateHandler;

	private:
		uint8 m_iBindPoint = -1;

		ComPtr<ID3D11SamplerState> m_cpSamplerState = nullptr;

	private:
		std::wstring m_wstrSamplerName = L"";
	};
}
