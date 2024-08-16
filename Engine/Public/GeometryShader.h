#pragma once
#include "Shader.h"

namespace Engine
{
	class CGeometryShader final : public IShader
	{
	/******************
		Ctor/Dtor
	******************/
	public:
		explicit CGeometryShader() = default;

		virtual ~CGeometryShader() = default;
		
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
		void GSSetShader();

		void GSUnsetShader();

	/******************
		Data Members
	******************/
	private:
		ComPtr<ID3D11GeometryShader> m_cpGeometryShader = nullptr;

		std::wstring m_wstrGeometryShaderName = L"";
	};
}
