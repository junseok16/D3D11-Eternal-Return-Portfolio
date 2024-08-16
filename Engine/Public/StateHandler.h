#pragma once

namespace Engine
{
	class CDeviceManager;
	class CStateLoader;

	class ENGINE_DLL CStateHandler final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CStateHandler)
		
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
		HRESULT CreateRasterizerState(const std::wstring& _wstrRasterizerStateName, const D3D11_RASTERIZER_DESC* _pRasterizerDesc);

		HRESULT CreateDepthStencilState(const std::wstring& _wstrDepthStencilStateName, const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc);

		HRESULT CreateSamplerState(const std::wstring& _wstrSamplerStateName, const D3D11_SAMPLER_DESC* _pSamplerDesc);

		HRESULT CreateBlendState(const std::wstring& _wstrBlendStateName, const D3D11_BLEND_DESC* _pBlendDesc);

	public:
		ComPtr<ID3D11RasterizerState> CreateRasterizerState(const D3D11_RASTERIZER_DESC* _pRasterizerDesc);

		ComPtr<ID3D11DepthStencilState> CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc);

		ComPtr<ID3D11SamplerState> CreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc);

		ComPtr<ID3D11BlendState> CreateBlendState(const D3D11_BLEND_DESC* _pBlendDesc);

	public:
		ComPtr<ID3D11RasterizerState> FindRasterizerState(const std::wstring& _wstrRasterizerStateName);

		ComPtr<ID3D11DepthStencilState> FindDepthStencilState(const std::wstring& _wstrDepthStencilStateName);

		ComPtr<ID3D11SamplerState> FindSamplerState(const std::wstring& _wstrSamplerStateName);

		ComPtr<ID3D11BlendState> FindBlendState(const std::wstring& _wstrBlendStateName);

	public:
		void OMSetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState, UINT _iStencilRef);

		void OMSetBlendState(ID3D11BlendState* _pBlendState, const FLOAT* _pBlendFactor, UINT _iSampleMask);

		void RSSetState(ID3D11RasterizerState* _pRasterizerState);
		
		void VSSetSamplers(UINT _iStartSlot, UINT _iNumSamplers, ID3D11SamplerState* const* _ppSamplers);

		void PSSetSamplers(UINT _iStartSlot, UINT _iNumSamplers, ID3D11SamplerState* const* _ppSamplers);

		void GSSetSamplers(UINT _iStartSlot, UINT _iNumSamplers, ID3D11SamplerState* const* _ppSamplers);

	/********************
		Getter/Setter
	********************/
	public:
		shared_ptr<CDeviceManager> GetDeviceManager() const { return m_wpDeviceManager.expired() ? nullptr : m_wpDeviceManager.lock(); }

	/********************
		Data Members
	********************/
	private:
		// 레스터라이저 스테이트들
		std::unordered_map<std::wstring, ComPtr<ID3D11RasterizerState>> m_umapRasterizerStates;

		// 뎁스 스텐실 스테이트들
		std::unordered_map<std::wstring, ComPtr<ID3D11DepthStencilState>> m_umapDepthStencilStates;

		// 샘플러 스테이트들
		std::unordered_map<std::wstring, ComPtr<ID3D11SamplerState>> m_umapSamplerStates;

		// 블렌드 스테이트들
		std::unordered_map<std::wstring, ComPtr<ID3D11BlendState>> m_umapBlendStates;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::shared_ptr<CStateLoader> m_spStateLoader = nullptr;
	};
}

