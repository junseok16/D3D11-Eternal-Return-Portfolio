#include "pch.h"
#include "VertexShader.h"

#include "ShaderHandler.h"

HRESULT Engine::CVertexShader::Initialize(std::shared_ptr<FShaderDesc> _spShaderDesc)
{
	if (FAILED(IShader::Initialize(_spShaderDesc))) { return E_FAIL; }

	shared_ptr<FVertexShaderDesc> spVertexShaderDesc = static_pointer_cast<FVertexShaderDesc>(_spShaderDesc);

	m_cpVertexShader = m_wpShaderHandler.lock()->FindVertexShader(spVertexShaderDesc->m_wstrVertexShaderName);
	CHECK(m_cpVertexShader != nullptr);

	m_cpInputLayout = m_wpShaderHandler.lock()->FindInputLayout(spVertexShaderDesc->m_wstrInputLayoutName);
	CHECK(m_cpInputLayout != nullptr);

	m_wstrVertexShaderName = spVertexShaderDesc->m_wstrVertexShaderName;
	m_wstrInputLayoutName = spVertexShaderDesc->m_wstrInputLayoutName;
	return S_OK;
}

void Engine::CVertexShader::Release()
{
	m_cpVertexShader = nullptr;
	m_cpInputLayout = nullptr;
}

void Engine::CVertexShader::VSSetShader()
{
	m_wpShaderHandler.lock()->VSSetShader(m_cpVertexShader.Get(), nullptr, 0);
}

void Engine::CVertexShader::IASetInputLayout()
{
	m_wpShaderHandler.lock()->IASetInputLayout(m_cpInputLayout.Get());
}
