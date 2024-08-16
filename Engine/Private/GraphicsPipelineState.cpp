#include "pch.h"
#include "GraphicsPipelineState.h"

void Engine::CGraphicsPipelineState::Release()
{
	m_cpVertexShader		= nullptr;
	m_cpPixelShader			= nullptr;
	m_cpHullShader			= nullptr;
	m_cpDomainShader		= nullptr;
	m_cpGeometryShader		= nullptr;
	m_cpInputLayout			= nullptr;
	m_cpBlendState			= nullptr;
	m_cpDepthStencilState	= nullptr;
	m_cpRasterizerState		= nullptr;
}

void Engine::CGraphicsPipelineState::operator=(const CGraphicsPipelineState& _oGraphicsPipelineState)
{
	m_cpVertexShader		= _oGraphicsPipelineState.m_cpVertexShader;
	m_cpPixelShader			= _oGraphicsPipelineState.m_cpPixelShader;
	m_cpHullShader			= _oGraphicsPipelineState.m_cpHullShader;
	m_cpDomainShader		= _oGraphicsPipelineState.m_cpDomainShader;
	m_cpGeometryShader		= _oGraphicsPipelineState.m_cpGeometryShader;
	m_cpInputLayout			= _oGraphicsPipelineState.m_cpInputLayout;
	m_cpBlendState			= _oGraphicsPipelineState.m_cpBlendState;
	m_cpDepthStencilState	= _oGraphicsPipelineState.m_cpDepthStencilState;
	m_cpRasterizerState		= _oGraphicsPipelineState.m_cpRasterizerState;
	
	for (int32 iInnerLoopIndex = 0; iInnerLoopIndex < 4; ++iInnerLoopIndex)
	{
		m_fBlendFactor[iInnerLoopIndex] = _oGraphicsPipelineState.m_fBlendFactor[iInnerLoopIndex];
	}
	m_iStencilRef = _oGraphicsPipelineState.m_iStencilRef;
	m_primitiveTopology = _oGraphicsPipelineState.m_primitiveTopology;
}

void Engine::CGraphicsPipelineState::SetBlendFactor(const float _fBlendFactor[4])
{
	memcpy(m_fBlendFactor, _fBlendFactor, sizeof(float) * 4);
}

void Engine::CGraphicsPipelineState::SetPipelineState(const ComPtr<ID3D11DeviceContext>& _cpDeviceContext)
{
	_cpDeviceContext->VSSetShader				(m_cpVertexShader.Get(), 0, 0);
	_cpDeviceContext->PSSetShader				(m_cpPixelShader.Get(), 0, 0);
	_cpDeviceContext->HSSetShader				(m_cpHullShader.Get(), 0, 0);
	_cpDeviceContext->DSSetShader				(m_cpDomainShader.Get(), 0, 0);
	_cpDeviceContext->GSSetShader				(m_cpGeometryShader.Get(), 0, 0);
	_cpDeviceContext->IASetInputLayout			(m_cpInputLayout.Get());
	_cpDeviceContext->RSSetState				(m_cpRasterizerState.Get());
	_cpDeviceContext->OMSetBlendState			(m_cpBlendState.Get(), m_fBlendFactor, 0xffff'ffff);
	_cpDeviceContext->OMSetDepthStencilState	(m_cpDepthStencilState.Get(), m_iStencilRef);
	_cpDeviceContext->IASetPrimitiveTopology	(m_primitiveTopology);
}
