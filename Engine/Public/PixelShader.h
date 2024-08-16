#pragma once
#include "Shader.h"

namespace Engine
{
	class CPixelShader final : public IShader
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CPixelShader() = default;

		virtual ~CPixelShader() = default;

	/******************
		Events
	******************/
	public:
		virtual HRESULT Initialize(std::shared_ptr<FShaderDesc> _spShaderDesc = nullptr) override;

		virtual void Release() override;

	/******************
		Methods
	******************/
		void PSSetShader();
		
	/******************
		Data Members
	******************/
	private:
		ComPtr<ID3D11PixelShader> m_cpPixelShader = nullptr;

		std::wstring m_wstrPixelShaderName = L"";
	};
}
