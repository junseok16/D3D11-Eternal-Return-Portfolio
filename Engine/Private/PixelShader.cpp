#include "pch.h"
#include "PixelShader.h"

#include "ShaderHandler.h"

HRESULT Engine::CPixelShader::Initialize(std::shared_ptr<FShaderDesc> _spShaderDesc)
{
	if (FAILED(IShader::Initialize(_spShaderDesc))) { return E_FAIL; }

	shared_ptr<FPixelShaderDesc> spPixelShaderDesc = static_pointer_cast<FPixelShaderDesc>(_spShaderDesc);

	m_cpPixelShader = m_wpShaderHandler.lock()->FindPixelShader(spPixelShaderDesc->m_wstrPixelShaderName);
	CHECK(m_cpPixelShader != nullptr);

	m_wstrPixelShaderName = spPixelShaderDesc->m_wstrPixelShaderName;
	return S_OK;
}

void Engine::CPixelShader::Release()
{
	m_cpPixelShader = nullptr;
}

void Engine::CPixelShader::PSSetShader()
{
	m_wpShaderHandler.lock()->PSSetShader(m_cpPixelShader.Get(), nullptr, 0);
}
