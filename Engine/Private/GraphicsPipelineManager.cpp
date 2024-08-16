#include "pch.h"
#include "GraphicsPipelineManager.h"
#include "GraphicsPipelineState.h"

#include "StateHandler.h"

IMPLEMENT_SINGLETON(CGraphicsPipelineManager)

HRESULT Engine::CGraphicsPipelineManager::PreInitialize(const ComPtr<ID3D11Device>& _cpDevice, const ComPtr<ID3D11DeviceContext>& _cpDeviceContext)
{
	m_wpStateHandler = CStateHandler::GetInstance();

	m_cpDevice = _cpDevice;
	m_cpDeviceContext = _cpDeviceContext;
	return S_OK;
}

HRESULT Engine::CGraphicsPipelineManager::Initialize()
{
	InitializeRasterizerStates();
	InitializeBlendStates();
	InitializeDepthStencilStates();
	CreatePipelineStates();
	return S_OK;
}

void Engine::CGraphicsPipelineManager::Release()
{
	m_spDefaultPipelineState->Release();
	m_spShadowPipelineState->Release();
	m_spPreRenderPipelineState->Release();
	m_spRenderLightPipelineState->Release();
	m_spRenderEffectPipelineState->Release();
	m_spRenderTranslucentObjectPipelineState->Release();
	m_spRenderTranslucentUIPipelineState->Release();
	m_spRenderPostProcessPipelineState->Release();

	m_spDefaultPipelineState = nullptr;
	m_spShadowPipelineState = nullptr;
	m_spPreRenderPipelineState = nullptr;
	m_spRenderLightPipelineState = nullptr;
	m_spRenderEffectPipelineState = nullptr;
	m_spRenderTranslucentObjectPipelineState = nullptr;
	m_spRenderTranslucentUIPipelineState = nullptr;
	m_spRenderPostProcessPipelineState = nullptr;

	m_cpFillSolidCullBackRasterizerState = nullptr;
	m_cpFillSolidCullNoneRasterizerState = nullptr;
	m_cpEnableDepthStencilState = nullptr;
	m_cpDisableDepthStencilState = nullptr;
	m_cpSrcInvSrcEnableBlendState = nullptr;
	m_cpOneEnableBlendState = nullptr;
	m_cpDisableBlendState = nullptr;

	m_cpDeviceContext = nullptr;
	m_cpDevice = nullptr;

	m_spInstance = nullptr;
}

void Engine::CGraphicsPipelineManager::InitializeRasterizerStates()
{
	{
		D3D11_RASTERIZER_DESC tRasterizerDesc;
		ZeroMemory(&tRasterizerDesc, sizeof(tRasterizerDesc));
		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		tRasterizerDesc.FrontCounterClockwise = false;
		tRasterizerDesc.DepthClipEnable = true;
		m_cpFillSolidCullBackRasterizerState = m_wpStateHandler.lock()->CreateRasterizerState(&tRasterizerDesc);
	}
	
	{
		D3D11_RASTERIZER_DESC tRasterizerDesc;
		ZeroMemory(&tRasterizerDesc, sizeof(tRasterizerDesc));
		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		tRasterizerDesc.FrontCounterClockwise = false;
		tRasterizerDesc.DepthClipEnable = true;
		m_cpFillSolidCullNoneRasterizerState = m_wpStateHandler.lock()->CreateRasterizerState(&tRasterizerDesc);
	}

}

void Engine::CGraphicsPipelineManager::InitializeBlendStates()
{
	{
		D3D11_BLEND_DESC tBlendDesc;
		ZeroMemory(&tBlendDesc, sizeof(tBlendDesc));
		tBlendDesc.AlphaToCoverageEnable = false;
		tBlendDesc.IndependentBlendEnable = false;

		tBlendDesc.RenderTarget[0].BlendEnable = true;
		tBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		tBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_cpSrcInvSrcEnableBlendState = m_wpStateHandler.lock()->CreateBlendState(&tBlendDesc);
	}

	{
		D3D11_BLEND_DESC tBlendDesc;
		ZeroMemory(&tBlendDesc, sizeof(tBlendDesc));
		tBlendDesc.AlphaToCoverageEnable = false;
		tBlendDesc.IndependentBlendEnable = false;

		tBlendDesc.RenderTarget[0].BlendEnable = true;
		tBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		tBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_cpOneEnableBlendState = m_wpStateHandler.lock()->CreateBlendState(&tBlendDesc);
	}

	{
		D3D11_BLEND_DESC tBlendDesc;
		ZeroMemory(&tBlendDesc, sizeof(tBlendDesc));
		tBlendDesc.AlphaToCoverageEnable = false;
		tBlendDesc.IndependentBlendEnable = false;

		tBlendDesc.RenderTarget[0].BlendEnable = false;
		tBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		tBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_cpDisableBlendState = m_wpStateHandler.lock()->CreateBlendState(&tBlendDesc);
	}
}

void Engine::CGraphicsPipelineManager::InitializeDepthStencilStates()
{
	{
		D3D11_DEPTH_STENCIL_DESC tDepthStencilDesc;
		ZeroMemory(&tDepthStencilDesc, sizeof(tDepthStencilDesc));
		tDepthStencilDesc.DepthEnable = true;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		m_cpEnableDepthStencilState = m_wpStateHandler.lock()->CreateDepthStencilState(&tDepthStencilDesc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC tDepthStencilDesc;
		ZeroMemory(&tDepthStencilDesc, sizeof(tDepthStencilDesc));
		tDepthStencilDesc.DepthEnable = false;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_NEVER;
		m_cpEnableDepthNeverCompareStencilState = m_wpStateHandler.lock()->CreateDepthStencilState(&tDepthStencilDesc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC tDepthStencilDesc;
		ZeroMemory(&tDepthStencilDesc, sizeof(tDepthStencilDesc));
		tDepthStencilDesc.DepthEnable = false;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_NEVER;
		m_cpDisableDepthStencilState = m_wpStateHandler.lock()->CreateDepthStencilState(&tDepthStencilDesc);
	}
}

void Engine::CGraphicsPipelineManager::CreatePipelineStates()
{
	{
		m_spDefaultPipelineState = make_shared<CGraphicsPipelineState>();

		m_spDefaultPipelineState->m_cpBlendState			= m_cpDisableBlendState;
		m_spDefaultPipelineState->m_cpDepthStencilState		= m_cpEnableDepthStencilState;
		m_spDefaultPipelineState->m_cpRasterizerState		= m_cpFillSolidCullBackRasterizerState;

		m_spDefaultPipelineState->m_cpVertexShader			= nullptr;
		m_spDefaultPipelineState->m_cpPixelShader			= nullptr;
		m_spDefaultPipelineState->m_cpHullShader			= nullptr;
		m_spDefaultPipelineState->m_cpGeometryShader		= nullptr;
		m_spDefaultPipelineState->m_cpInputLayout			= nullptr;
	}
	
	{
		m_spPreRenderPipelineState = make_shared<CGraphicsPipelineState>();

		m_spPreRenderPipelineState->m_cpBlendState			= m_cpDisableBlendState;
		m_spPreRenderPipelineState->m_cpDepthStencilState	= m_cpEnableDepthNeverCompareStencilState;
		m_spPreRenderPipelineState->m_cpRasterizerState		= m_cpFillSolidCullNoneRasterizerState;

		m_spPreRenderPipelineState->m_cpVertexShader		= nullptr;
		m_spPreRenderPipelineState->m_cpPixelShader			= nullptr;
		m_spPreRenderPipelineState->m_cpHullShader			= nullptr;
		m_spPreRenderPipelineState->m_cpGeometryShader		= nullptr;
		m_spPreRenderPipelineState->m_cpInputLayout			= nullptr;
	}

	{
		m_spShadowPipelineState= make_shared<CGraphicsPipelineState>();

		m_spShadowPipelineState->m_cpBlendState				= m_cpDisableBlendState;
		m_spShadowPipelineState->m_cpDepthStencilState		= m_cpEnableDepthStencilState;
		m_spShadowPipelineState->m_cpRasterizerState		= m_cpFillSolidCullBackRasterizerState;

		m_spShadowPipelineState->m_cpVertexShader			= nullptr;
		m_spShadowPipelineState->m_cpPixelShader			= nullptr;
		m_spShadowPipelineState->m_cpHullShader				= nullptr;
		m_spShadowPipelineState->m_cpGeometryShader			= nullptr;
		m_spShadowPipelineState->m_cpInputLayout			= nullptr;
	}

	{
		m_spRenderLightPipelineState = make_shared<CGraphicsPipelineState>();

		m_spRenderLightPipelineState->m_cpBlendState			= m_cpOneEnableBlendState;
		m_spRenderLightPipelineState->m_cpDepthStencilState		= m_cpDisableDepthStencilState;
		m_spRenderLightPipelineState->m_cpRasterizerState		= m_cpFillSolidCullNoneRasterizerState;

		m_spRenderLightPipelineState->m_cpVertexShader			= nullptr;
		m_spRenderLightPipelineState->m_cpPixelShader			= nullptr;
		m_spRenderLightPipelineState->m_cpHullShader			= nullptr;
		m_spRenderLightPipelineState->m_cpGeometryShader		= nullptr;
		m_spRenderLightPipelineState->m_cpInputLayout			= nullptr;
	}

	{
		m_spRenderEffectPipelineState = make_shared<CGraphicsPipelineState>();

		m_spRenderEffectPipelineState->m_cpBlendState			= m_cpSrcInvSrcEnableBlendState;
		m_spRenderEffectPipelineState->m_cpDepthStencilState	= m_cpEnableDepthStencilState;
		m_spRenderEffectPipelineState->m_cpRasterizerState		= m_cpFillSolidCullNoneRasterizerState;

		m_spRenderEffectPipelineState->m_cpVertexShader			= nullptr;
		m_spRenderEffectPipelineState->m_cpPixelShader			= nullptr;
		m_spRenderEffectPipelineState->m_cpHullShader			= nullptr;
		m_spRenderEffectPipelineState->m_cpGeometryShader		= nullptr;
		m_spRenderEffectPipelineState->m_cpInputLayout			= nullptr;
	}

	{
		m_spRenderPostProcessPipelineState = make_shared<CGraphicsPipelineState>();

		m_spRenderPostProcessPipelineState->m_cpBlendState			= m_cpDisableBlendState;
		m_spRenderPostProcessPipelineState->m_cpDepthStencilState	= m_cpDisableDepthStencilState;
		m_spRenderPostProcessPipelineState->m_cpRasterizerState		= m_cpFillSolidCullBackRasterizerState;

		m_spRenderPostProcessPipelineState->m_cpVertexShader		= nullptr;
		m_spRenderPostProcessPipelineState->m_cpPixelShader			= nullptr;
		m_spRenderPostProcessPipelineState->m_cpHullShader			= nullptr;
		m_spRenderPostProcessPipelineState->m_cpGeometryShader		= nullptr;
		m_spRenderPostProcessPipelineState->m_cpInputLayout			= nullptr;
	}

	{
		m_spRenderTranslucentObjectPipelineState = make_shared<CGraphicsPipelineState>();
		
		m_spRenderTranslucentObjectPipelineState->m_cpBlendState			= m_cpSrcInvSrcEnableBlendState;
		m_spRenderTranslucentObjectPipelineState->m_cpDepthStencilState		= m_cpEnableDepthStencilState;
		m_spRenderTranslucentObjectPipelineState->m_cpRasterizerState		= m_cpFillSolidCullBackRasterizerState;

		m_spRenderTranslucentObjectPipelineState->m_cpVertexShader			= nullptr;
		m_spRenderTranslucentObjectPipelineState->m_cpPixelShader			= nullptr;
		m_spRenderTranslucentObjectPipelineState->m_cpHullShader			= nullptr;
		m_spRenderTranslucentObjectPipelineState->m_cpGeometryShader		= nullptr;
		m_spRenderTranslucentObjectPipelineState->m_cpInputLayout			= nullptr;
	}

	{
		m_spRenderTranslucentUIPipelineState = make_shared<CGraphicsPipelineState>();
		
		m_spRenderTranslucentUIPipelineState->m_cpBlendState			= m_cpSrcInvSrcEnableBlendState;
		m_spRenderTranslucentUIPipelineState->m_cpDepthStencilState		= m_cpEnableDepthStencilState;
		m_spRenderTranslucentUIPipelineState->m_cpRasterizerState		= m_cpFillSolidCullBackRasterizerState;

		m_spRenderTranslucentUIPipelineState->m_cpVertexShader			= nullptr;
		m_spRenderTranslucentUIPipelineState->m_cpPixelShader			= nullptr;
		m_spRenderTranslucentUIPipelineState->m_cpHullShader			= nullptr;
		m_spRenderTranslucentUIPipelineState->m_cpGeometryShader		= nullptr;
		m_spRenderTranslucentUIPipelineState->m_cpInputLayout			= nullptr;
	}
}

void Engine::CGraphicsPipelineManager::BeginRenderState(ERenderType _eRenderType)
{
	switch (_eRenderType)
	{
	case Engine::ERenderType::PRE_RENDER:
		m_spPreRenderPipelineState->SetPipelineState(m_cpDeviceContext);
		break;

	case Engine::ERenderType::OPAQUE_OBJECT:
		break;

	case Engine::ERenderType::LIGHT:
		m_spRenderLightPipelineState->SetPipelineState(m_cpDeviceContext);
		break;

	case Engine::ERenderType::POST_PROCESS:
		m_spRenderPostProcessPipelineState->SetPipelineState(m_cpDeviceContext);
		break;

	case Engine::ERenderType::EFFECT:
		m_spRenderEffectPipelineState->SetPipelineState(m_cpDeviceContext);
		break;

	case Engine::ERenderType::PARTICLE_OBJECT:
		break;

	case Engine::ERenderType::TRANSLUCENT_OBJECT:
		m_spRenderTranslucentObjectPipelineState->SetPipelineState(m_cpDeviceContext);
		break;

	case Engine::ERenderType::OPAQUE_USER_INTERFACE:
		break;

	case Engine::ERenderType::TRANSLUCENT_USER_INTERFACE:
		m_spRenderTranslucentUIPipelineState->SetPipelineState(m_cpDeviceContext);
		break;

	case Engine::ERenderType::POST_RENDER:
		break;

	default:
		break;
	}
}

void Engine::CGraphicsPipelineManager::EndRenderState()
{
	m_spDefaultPipelineState->SetPipelineState(m_cpDeviceContext);
}
