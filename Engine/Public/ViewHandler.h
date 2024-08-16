#pragma once

namespace Engine
{
	class CDeviceManager;
	class CViewLoader;

	struct TView final
	{
	public:
		ComPtr<ID3D11RenderTargetView> m_cpRenderTargetView = nullptr;

		ComPtr<ID3D11ShaderResourceView> m_cpShaderResourceView = nullptr;

		float m_fClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		Matrix m_matWorld = Matrix::Identity;

	public:
		void ClearRenderTargetView(const ComPtr<ID3D11DeviceContext>& _cpDeviceContext)
		{
			_cpDeviceContext->ClearRenderTargetView(m_cpRenderTargetView.Get(), m_fClearColor);
		}

		void SetWorldMatrix(float _fX, float _fY, float _fWidth, float _fHeight)
		{
			m_matWorld._11 = _fWidth;
			m_matWorld._22 = _fHeight;
			m_matWorld._41 = _fX;// -(1280.0f * 0.5f);
			m_matWorld._42 = -_fY;// +(720.0f * 0.5f);
		}

		void SetClearColor(const std::array<float, 4> _arrClearColor)
		{
			for (int32 iIndex = 0; iIndex < 4; ++iIndex) { m_fClearColor[iIndex] = _arrClearColor[iIndex]; }
		}
	};

	class ENGINE_DLL CViewHandler final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CViewHandler)
		
	/********************
		Events
	********************/
	public:
		HRESULT Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager);

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT CreateRenderTargetView(const std::wstring& _wstrRenderTargetViewName, ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pRenderTargetViewDesc = nullptr);

		HRESULT CreateDepthStencilView(const std::wstring& _wstrDepthStencilViewName, ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDepthStencilViewDesc = nullptr);

		HRESULT CreateShaderResourceView(const std::wstring& _wstrShaderResourceViewName, ID3D11Resource* _pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* _pShaderResourceViewDesc = nullptr);

		shared_ptr<TView> CreateView(const std::wstring& _wstrViewName);

		HRESULT CreateViewGroup(const std::wstring& _wstrViewGroupName);

	public:
		ComPtr<ID3D11RenderTargetView> FindRenderTargetView(const std::wstring& _wstrRenderTargetViewName);

		ComPtr<ID3D11DepthStencilView> FindDepthStencilView(const std::wstring& _wstrDepthStencilViewName);

		ComPtr<ID3D11ShaderResourceView> FindShaderResourceView(const std::wstring& _wstrShaderResourceViewName);

		shared_ptr<TView> FindView(const std::wstring& _wstrViewName);

		std::list<std::weak_ptr<TView>>* FindViewGroup(const std::wstring& _wstrViewGroupName);

	public:
		HRESULT AddShaderResourceView(const std::wstring& _wstrShaderResourceViewName, const ComPtr<ID3D11ShaderResourceView>& _cpShaderResouceView);

		HRESULT AddViewGroup(const std::wstring& _wstrViewGroupName, const std::wstring& _wstrViewName);

	public:
		void ClearRenderTargetView(const std::wstring& _wstrRenderTargetViewName, const FLOAT* _pColorRGBA);

		void ClearDepthStencilView(const std::wstring& _wstrDepthStencilViewName, UINT _iClearFlags = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, FLOAT _fDepth = 1.0f, UINT8 _iStencil = 0);

	public:
		void OMSetRenderTargets(UINT _iNumViews, ID3D11RenderTargetView* const* _ppRenderTargetViews, ID3D11DepthStencilView* _pDepthStencilView);

		void VSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews);

		void PSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews);
		
		void GSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews);

	public:
		HRESULT BeginViewGroup(const std::wstring& _wstrViewGroupName, const ComPtr<ID3D11DepthStencilView>& _cpDepthStencilView = nullptr);

		HRESULT EndViewGroup();

	public:
		void RenderViewGroup(const std::wstring& _wstrViewGroupName);

	/********************
		Getter/Setter
	********************/
	public:
		shared_ptr<CDeviceManager> GetDeviceManager() const { return m_wpDeviceManager.expired() ? nullptr : m_wpDeviceManager.lock(); }

	/********************
		Data Members
	********************/
	private:
		// ·»´õ Å¸°Ù ºäµé
		std::unordered_map<std::wstring, ComPtr<ID3D11RenderTargetView>> m_umapRenderTargetViews;

		// µª½º ½ºÅÙ½Ç ºäµé
		std::unordered_map<std::wstring, ComPtr<ID3D11DepthStencilView>> m_umapDepthStencilViews;

		// ¼ÎÀÌ´õ ¸®¼Ò½º ºäµé
		std::unordered_map<std::wstring, ComPtr<ID3D11ShaderResourceView>> m_umapShaderResourceViews;

		// ·»´õ Å¸°Ù ºä, ¼ÎÀÌ´õ ¸®¼Ò½º ºä ÁýÇÕ
		std::unordered_map<std::wstring, std::shared_ptr<TView>> m_umapViews;

		// ·»´õ Å¸°Ù ºä, ¼ÎÀÌ´õ ¸®¼Ò½º ºä ÁýÇÕ ±×·ìµé
		std::unordered_map<std::wstring, std::list<std::weak_ptr<TView>>> m_umapViewGroups;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::shared_ptr<CViewLoader> m_spViewLoader = nullptr;
	};
}
