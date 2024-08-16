#pragma once

namespace Engine
{
	class CStateHandler;

	class CBlend final
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CBlend() = default;

		virtual ~CBlend() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CBlend> Create(const std::wstring& _wstrBlendName);

		virtual HRESULT Initialize(const std::wstring& _wstrBlendName);

		virtual void Release();
		
	/******************
		Methods
	******************/
	public:
		void OMSetBlendState();

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CStateHandler> m_wpStateHandler;

	private:
		ComPtr<ID3D11BlendState> m_cpBlendState = nullptr;

	private:
		std::wstring m_wstrBlendName = L"";
	};
}
