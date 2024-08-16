#pragma once

namespace Engine
{
	class CModelHandler;
	class CViewHandler;
	class CEffectHandler;

	class CTexture final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CTexture() = default;

		virtual ~CTexture() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CTexture> Create(const std::wstring& wstrTextureName, uint8 _iBindPoint, bool _bModel);

		virtual HRESULT Initialize(const std::wstring& wstrTextureName, uint8 _iBindPoint, bool _bModel);

		virtual void Release();
		
	/******************
		Methods
	******************/
	public:
		void PSSetShaderResources();

		void PSUnsetShaderResources();

		void VSSetShaderResources();

		void GSSetShaderResources();
		
	/********************
		Getter/Setter
	********************/
	public:
		HRESULT SetShaderResourceView(const std::wstring& _wstrTextureName);

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CModelHandler> m_wpModelHandler;

		std::weak_ptr<CViewHandler> m_wpViewHandler;

		std::weak_ptr<CEffectHandler> m_wpEffectHandler;

	private:
		uint8 m_iBindPoint = -1;

		ComPtr<ID3D11ShaderResourceView> m_cpShaderResourceView = nullptr;

	private:
		bool m_bModel = false;

		std::wstring m_wstrTextureName = L"";
	};
}
