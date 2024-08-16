#include "pch.h"
#include "Shader.h"

#include "ShaderHandler.h"

HRESULT Engine::IShader::Initialize(std::shared_ptr<FShaderDesc> _spShaderDesc)
{
	m_wpShaderHandler = CShaderHandler::GetInstance();
	CHECK(!m_wpShaderHandler.expired());
	return S_OK;
}

void Engine::IShader::Release()
{
}
