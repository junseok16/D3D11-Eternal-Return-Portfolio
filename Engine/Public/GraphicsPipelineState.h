#pragma once

namespace Engine
{
	class CGraphicsPipelineState final
	{
	public:
		explicit CGraphicsPipelineState() = default;

		virtual ~CGraphicsPipelineState() = default;

	public:
		void Release();

	public:
		void operator=(const CGraphicsPipelineState& _oGraphicsPipelineState);

		void SetBlendFactor(const float _fBlendFactor[4]);

		void SetPipelineState(const ComPtr<ID3D11DeviceContext>& _cpDeviceContext);

	public:
		ComPtr<ID3D11VertexShader> m_cpVertexShader = nullptr;

		ComPtr<ID3D11PixelShader> m_cpPixelShader = nullptr;

		ComPtr<ID3D11HullShader> m_cpHullShader = nullptr;

		ComPtr<ID3D11DomainShader> m_cpDomainShader = nullptr;

		ComPtr<ID3D11GeometryShader> m_cpGeometryShader = nullptr;

		ComPtr<ID3D11InputLayout> m_cpInputLayout = nullptr;

	public:
		ComPtr<ID3D11SamplerState> m_cpSamplerState = nullptr;

		ComPtr<ID3D11BlendState> m_cpBlendState = nullptr;

		ComPtr<ID3D11DepthStencilState> m_cpDepthStencilState = nullptr;

		ComPtr<ID3D11RasterizerState> m_cpRasterizerState = nullptr;

		float m_fBlendFactor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

		UINT m_iStencilRef = 0;

		D3D11_PRIMITIVE_TOPOLOGY m_primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	};
}
