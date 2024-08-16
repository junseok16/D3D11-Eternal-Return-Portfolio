#pragma once
#include "Manager.h"

namespace Engine
{
	class CGraphicsPipelineState;
	class CStateHandler;

	class CGraphicsPipelineManager final : public CManager
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CGraphicsPipelineManager)

	public:
		HRESULT PreInitialize(const ComPtr<ID3D11Device>& _cpDevice, const ComPtr<ID3D11DeviceContext>& _cpDeviceContext);

		HRESULT Initialize();

		void Release();

	private:
		void InitializeRasterizerStates();

		void InitializeBlendStates();

		void InitializeDepthStencilStates();

		void CreatePipelineStates();

	public:
		void BeginRenderState(ERenderType _eRenderType);

		void EndRenderState();

	public:
		ComPtr<ID3D11Device> m_cpDevice = nullptr;

		ComPtr<ID3D11DeviceContext> m_cpDeviceContext = nullptr;

	public:
		std::weak_ptr<CStateHandler> m_wpStateHandler;

	public:
		// Rasterizer States
		ComPtr<ID3D11RasterizerState> m_cpFillSolidCullBackRasterizerState = nullptr;

		ComPtr<ID3D11RasterizerState> m_cpFillSolidCullNoneRasterizerState = nullptr;

		// Depth Stencil States
		ComPtr<ID3D11DepthStencilState> m_cpEnableDepthStencilState = nullptr;

		ComPtr<ID3D11DepthStencilState> m_cpDisableDepthStencilState = nullptr;

		ComPtr<ID3D11DepthStencilState> m_cpEnableDepthNeverCompareStencilState = nullptr;

		// Blend States
		ComPtr<ID3D11BlendState> m_cpSrcInvSrcEnableBlendState = nullptr;

		ComPtr<ID3D11BlendState> m_cpOneEnableBlendState = nullptr;

		ComPtr<ID3D11BlendState> m_cpDisableBlendState = nullptr;

		ComPtr<ID3D11SamplerState> m_cpPointWrapSamplerState = nullptr;

		ComPtr<ID3D11SamplerState> m_cpLinearWrapSamplerState = nullptr;

	public:
		// Graphics Pipeline States
		std::shared_ptr<CGraphicsPipelineState> m_spDefaultPipelineState = nullptr;

		std::shared_ptr<CGraphicsPipelineState> m_spShadowPipelineState = nullptr;

		std::shared_ptr<CGraphicsPipelineState> m_spPreRenderPipelineState = nullptr;

		std::shared_ptr<CGraphicsPipelineState> m_spRenderLightPipelineState = nullptr;

		std::shared_ptr<CGraphicsPipelineState> m_spRenderPostProcessPipelineState = nullptr;

		std::shared_ptr<CGraphicsPipelineState> m_spRenderEffectPipelineState = nullptr;

		std::shared_ptr<CGraphicsPipelineState> m_spRenderTranslucentObjectPipelineState = nullptr;

		std::shared_ptr<CGraphicsPipelineState> m_spRenderTranslucentUIPipelineState = nullptr;
	};
}
