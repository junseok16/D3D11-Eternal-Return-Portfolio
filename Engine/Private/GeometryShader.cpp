#include "pch.h"
#include "GeometryShader.h"

#include "ShaderHandler.h"

HRESULT Engine::CGeometryShader::Initialize(std::shared_ptr<FShaderDesc> _spShaderDesc)
{
	if (FAILED(IShader::Initialize(_spShaderDesc))) { return E_FAIL; }

	shared_ptr<FGeometryShaderDesc> spGeometryShaderDesc = static_pointer_cast<FGeometryShaderDesc>(_spShaderDesc);

	m_cpGeometryShader = m_wpShaderHandler.lock()->FindGeometryShader(spGeometryShaderDesc->m_wstrGeometryShaderName);
	CHECK(m_cpGeometryShader != nullptr);

	m_wstrGeometryShaderName = spGeometryShaderDesc->m_wstrGeometryShaderName;
	return S_OK;
}

void Engine::CGeometryShader::Release()
{
	m_cpGeometryShader = nullptr;
}

void Engine::CGeometryShader::GSSetShader()
{
	m_wpShaderHandler.lock()->GSSetShader(m_cpGeometryShader.Get(), nullptr, 0);
}

void Engine::CGeometryShader::GSUnsetShader()
{
	m_wpShaderHandler.lock()->GSSetShader(nullptr, nullptr, 0);
}
