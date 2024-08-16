#pragma once
#include "Shader.h"

namespace Engine
{
	class CVertexShader final : public IShader
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CVertexShader() = default;

		virtual ~CVertexShader() = default;
		
	/******************
		Events
	******************/
	public:
		virtual HRESULT Initialize(std::shared_ptr<FShaderDesc> _spShaderDesc = nullptr) override;

		virtual void Release() override;

	/******************
		Methods
	******************/
	public:
		void IASetInputLayout();

		void VSSetShader();

	/******************
		Data Members
	******************/
	private:
		ComPtr<ID3D11VertexShader> m_cpVertexShader = nullptr;

		ComPtr<ID3D11InputLayout> m_cpInputLayout = nullptr;

		std::wstring m_wstrVertexShaderName = L"";

		std::wstring m_wstrInputLayoutName = L"";
	};
}
