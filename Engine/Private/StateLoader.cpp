#include "pch.h"
#include "StateLoader.h"

#include "StateHandler.h"

std::shared_ptr<CStateLoader> Engine::CStateLoader::Create()
{
	const std::shared_ptr<CStateLoader> spLoader = make_shared<CStateLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create state loader.");
	return spLoader;
}

HRESULT Engine::CStateLoader::Initialize()
{
	m_wpStateHandler = CStateHandler::GetInstance();
	m_wpDeviceManager = CStateHandler::GetInstance()->GetDeviceManager();

	// LoadRasterizerState();
	// LoadDepthStencilState();
	LoadSamplerState();
	// LoadBlendState();

	// SetStates();
	return S_OK;
}

void Engine::CStateLoader::Release()
{
}

HRESULT Engine::CStateLoader::LoadRasterizerState()
{
	{
		D3D11_RASTERIZER_DESC tRasterizerDesc;
		ZeroMemory(&tRasterizerDesc, sizeof(tRasterizerDesc));
		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		tRasterizerDesc.FrontCounterClockwise = false;
		tRasterizerDesc.DepthClipEnable = true;

		ENSURE(m_wpStateHandler.lock()->CreateRasterizerState(L"RS_FILL_SOLID_CULL_BACK", &tRasterizerDesc));
	}
	
	{
		D3D11_RASTERIZER_DESC tRasterizerDesc;
		ZeroMemory(&tRasterizerDesc, sizeof(tRasterizerDesc));
		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		tRasterizerDesc.FrontCounterClockwise = false;
		tRasterizerDesc.DepthClipEnable = true;

		ENSURE(m_wpStateHandler.lock()->CreateRasterizerState(L"RS_FILL_SOLID_CULL_NONE", &tRasterizerDesc));
	}

	return S_OK;
}

HRESULT Engine::CStateLoader::LoadDepthStencilState()
{
	{
		D3D11_DEPTH_STENCIL_DESC tDepthStencilDesc;
		ZeroMemory(&tDepthStencilDesc, sizeof(tDepthStencilDesc));
		tDepthStencilDesc.DepthEnable = true;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		ENSURE(m_wpStateHandler.lock()->CreateDepthStencilState(L"DSS_DEPTH_ENABLE", &tDepthStencilDesc));
	}

	{
		D3D11_DEPTH_STENCIL_DESC tDepthStencilDesc;
		ZeroMemory(&tDepthStencilDesc, sizeof(tDepthStencilDesc));
		tDepthStencilDesc.DepthEnable = false;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_NEVER;

		ENSURE(m_wpStateHandler.lock()->CreateDepthStencilState(L"DSS_DEPTH_DISABLE", &tDepthStencilDesc));
	}
	
	return S_OK;
}

HRESULT Engine::CStateLoader::LoadSamplerState()
{
	{
		D3D11_SAMPLER_DESC tSamplerDesc;
		ZeroMemory(&tSamplerDesc, sizeof(tSamplerDesc));
		tSamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		tSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		tSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		tSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		tSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		tSamplerDesc.MinLOD = 0;
		tSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		ENSURE(m_wpStateHandler.lock()->CreateSamplerState(L"SS_FILTER_LINEAR_ADDRESS_WRAP", &tSamplerDesc));
	}

	{
		D3D11_SAMPLER_DESC tSamplerDesc;
		ZeroMemory(&tSamplerDesc, sizeof(tSamplerDesc));
		tSamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		tSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		tSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		tSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		tSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		tSamplerDesc.MinLOD = 0;
		tSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		ENSURE(m_wpStateHandler.lock()->CreateSamplerState(L"SS_FILTER_POINT_ADDRESS_WRAP", &tSamplerDesc));
	}

	{
		D3D11_SAMPLER_DESC tSamplerDesc;
		ZeroMemory(&tSamplerDesc, sizeof(tSamplerDesc));
		tSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		tSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		tSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		tSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		tSamplerDesc.BorderColor[0] = 100.0f;		
		tSamplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
		tSamplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;

		ENSURE(m_wpStateHandler.lock()->CreateSamplerState(L"CSS_FILTER_LINEAR_ADDRESS_BORDER", &tSamplerDesc));
	}
	return S_OK;
}

HRESULT Engine::CStateLoader::LoadBlendState()
{
	{
		D3D11_BLEND_DESC tBlendDesc;
		ZeroMemory(&tBlendDesc, sizeof(tBlendDesc));
		tBlendDesc.AlphaToCoverageEnable = false;
		tBlendDesc.IndependentBlendEnable = false;

		tBlendDesc.RenderTarget[0].BlendEnable				= true;
		tBlendDesc.RenderTarget[0].SrcBlend					= D3D11_BLEND_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].BlendOp					= D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ZERO;
		tBlendDesc.RenderTarget[0].BlendOpAlpha				= D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

		ENSURE(m_wpStateHandler.lock()->CreateBlendState(L"BS_BLEND_ENABLE", &tBlendDesc));
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

		ENSURE(m_wpStateHandler.lock()->CreateBlendState(L"BS_BLEND_DISABLE", &tBlendDesc));
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

		ENSURE(m_wpStateHandler.lock()->CreateBlendState(L"BS_BLEND_ONE_ENABLE", &tBlendDesc));
	}

	return S_OK;
}

void Engine::CStateLoader::SetStates()
{
	m_wpStateHandler.lock()->RSSetState(m_wpStateHandler.lock()->FindRasterizerState(L"RS_FILL_SOLID_CULL_BACK").Get());
	m_wpStateHandler.lock()->OMSetDepthStencilState(m_wpStateHandler.lock()->FindDepthStencilState(L"DSS_DEPTH_ENABLE").Get(), 0);
}
