// default
#include "pch.h"
#include "LightManager.h"

#include "LightComponent.h"

#include "ShaderHandler.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "Sampler.h"

#include "LightConstantBuffer.h"
#include "InvViewInvProjectionConstantBuffer.h"

HRESULT Engine::CLightManager::PreInitialize()
{
	return S_OK;
}

HRESULT Engine::CLightManager::Initialize()
{
	m_wpShaderHandler = CShaderHandler::GetInstance();

	{
		shared_ptr<FPixelShaderDesc> spPSDesc = m_wpShaderHandler.lock()->FindPixelShaderDesc(L"PS_DeferredDirectionalLight");
		m_spDirectionalLightPixelShader = CPixelShader::Create<CPixelShader>(spPSDesc);
	}

	{
		shared_ptr<FPixelShaderDesc> spPSDesc = m_wpShaderHandler.lock()->FindPixelShaderDesc(L"PS_DeferredPointLight");
		m_spPointLightPixelShader = CPixelShader::Create<CPixelShader>(spPSDesc);
}

	{
		m_spNormalTexture = CTexture::Create(L"NORMAL", 0, false);
		m_spDepthTexture = CTexture::Create(L"DEPTH", 1, false);
	}

	{
		m_spPSSampler[0] = CSampler::Create(L"SS_FILTER_POINT_ADDRESS_WRAP", 0);
		m_spPSSampler[1] = CSampler::Create(L"SS_FILTER_LINEAR_ADDRESS_WRAP", 0);
	}
	
	return S_OK;
}

int32 Engine::CLightManager::Tick()
{
	return S_OK;
}

void Engine::CLightManager::Render()
{
	for (const auto& pair : m_umapDirectionalLightComponents)
	{
		m_spVertexBuffer->IASetVertexBuffer();
		m_spIndexBuffer->IASetIndexBuffer();
		m_spIndexBuffer->IASetPrimitiveTopology();

		m_spVertexShader->IASetInputLayout();
		m_spVertexShader->VSSetShader();
		m_spDirectionalLightPixelShader->PSSetShader();

		m_spVSConstantBuffers->CopyConstantBuffer(0);
		m_spVSConstantBuffers->VSSetConstantBuffers();

		pair.second.lock()->Render();

		/*
		m_spDirectionalLightPSConstantBuffers->TickConstantBuffer(0);
		m_spDirectionalLightPSConstantBuffers->CopyConstantBuffer(0);
		m_spDirectionalLightPSConstantBuffers->PSSetConstantBuffers();
		*/

		m_spNormalTexture->PSSetShaderResources();
		m_spPSSampler[0]->PSSetSamplers();
		m_spIndexBuffer->DrawIndexed();

		m_spNormalTexture->PSUnsetShaderResources();
	}

	for (const auto& pair : m_umapPointLightComponents)
	{
		m_spVertexBuffer->IASetVertexBuffer();
		m_spIndexBuffer->IASetIndexBuffer();
		m_spIndexBuffer->IASetPrimitiveTopology();

		m_spVertexShader->IASetInputLayout();
		m_spVertexShader->VSSetShader();
		m_spPointLightPixelShader->PSSetShader();

		m_spVSConstantBuffers->CopyConstantBuffer(0);
		m_spVSConstantBuffers->VSSetConstantBuffers();

		pair.second.lock()->Render();

		/*
		m_spPointLightPSConstantBuffers[0]->TickConstantBuffer(0);
		m_spPointLightPSConstantBuffers[0]->CopyConstantBuffer(0);
		m_spPointLightPSConstantBuffers[0]->PSSetConstantBuffers();
		m_spPointLightPSConstantBuffers[1]->TickConstantBuffer(0);
		m_spPointLightPSConstantBuffers[1]->CopyConstantBuffer(0);
		m_spPointLightPSConstantBuffers[1]->PSSetConstantBuffers();
		*/

		m_spNormalTexture->PSSetShaderResources();
		m_spDepthTexture->PSSetShaderResources();
		m_spPSSampler[0]->PSSetSamplers();
		m_spIndexBuffer->DrawIndexed();

		m_spNormalTexture->PSUnsetShaderResources();
		m_spDepthTexture->PSUnsetShaderResources();
	}
}

void Engine::CLightManager::Release()
{
	m_spVertexBuffer->Release();
	m_spVertexBuffer = nullptr;

	m_spIndexBuffer->Release();
	m_spIndexBuffer = nullptr;

	m_spVertexShader->Release();
	m_spVertexShader = nullptr;

	m_spVSConstantBuffers->Release();
	m_spVSConstantBuffers = nullptr;

	m_spDirectionalLightPixelShader->Release();
	m_spDirectionalLightPixelShader = nullptr;

	m_spPointLightPixelShader->Release();
	m_spPointLightPixelShader = nullptr;

	// m_spDirectionalLightPSConstantBuffers->Release();
	// m_spDirectionalLightPSConstantBuffers = nullptr;
	// 
	// m_spPointLightPSConstantBuffers[0]->Release();
	// m_spPointLightPSConstantBuffers[0] = nullptr;
	// m_spPointLightPSConstantBuffers[1]->Release();
	// m_spPointLightPSConstantBuffers[1] = nullptr;

	m_spNormalTexture->Release();
	m_spNormalTexture = nullptr;

	m_spDepthTexture->Release();
	m_spDepthTexture = nullptr;

	m_spPSSampler[0]->Release();
	m_spPSSampler[0] = nullptr;

	m_spPSSampler[1]->Release();
	m_spPSSampler[1] = nullptr;
}

HRESULT Engine::CLightManager::AddLightComponent(const std::wstring& _wstrLightComponentName, const std::shared_ptr<CLightComponent>& _spLightComponent, ELightType _eLightType)
{
	switch (_eLightType)
	{
	case Engine::ELightType::DIRECTIONAL:
	{
		if (m_umapDirectionalLightComponents.find(_wstrLightComponentName) != m_umapDirectionalLightComponents.end()) { return E_FAIL; }

		m_umapDirectionalLightComponents.emplace(_wstrLightComponentName, _spLightComponent);
	}
	break;

	case Engine::ELightType::POINT:
	{
		if (m_umapPointLightComponents.find(_wstrLightComponentName) != m_umapPointLightComponents.end()) { return E_FAIL; }

		m_umapPointLightComponents.emplace(_wstrLightComponentName, _spLightComponent);
	}
	break;

	case Engine::ELightType::SPOT:
	{
		if (m_umapSpotLightComponents.find(_wstrLightComponentName) != m_umapSpotLightComponents.end()) { return E_FAIL; }

		m_umapSpotLightComponents.emplace(_wstrLightComponentName, _spLightComponent);
	}
	break;

	default:
		break;
	}

	return S_OK;
}

HRESULT Engine::CLightManager::RemoveLightComponent(const std::wstring& _wstrLightComponentName, ELightType _eLightType)
{
	switch (_eLightType)
	{
	case Engine::ELightType::DIRECTIONAL:
	{
		if (m_umapDirectionalLightComponents.find(_wstrLightComponentName) == m_umapDirectionalLightComponents.end()) { return E_FAIL; }

		m_umapDirectionalLightComponents.erase(_wstrLightComponentName);
	}
	break;

	case Engine::ELightType::POINT:
	{
		if (m_umapPointLightComponents.find(_wstrLightComponentName) == m_umapPointLightComponents.end()) { return E_FAIL; }

		m_umapPointLightComponents.erase(_wstrLightComponentName);
	}
	break;

	case Engine::ELightType::SPOT:
	{
		if (m_umapSpotLightComponents.find(_wstrLightComponentName) == m_umapSpotLightComponents.end()) { return E_FAIL; }

		m_umapSpotLightComponents.erase(_wstrLightComponentName);
	}
	break;

	default:
		break;
	}

	return S_OK;
}

std::shared_ptr<CLightComponent> Engine::CLightManager::FindLightComponent(const std::wstring& _wstrLightComponentName, ELightType _eLightType)
{
	switch (_eLightType)
	{
	case Engine::ELightType::DIRECTIONAL:
	{
		if (m_umapDirectionalLightComponents.find(_wstrLightComponentName) == m_umapDirectionalLightComponents.end()) { return nullptr; }

		return m_umapDirectionalLightComponents[_wstrLightComponentName].lock();
	}
	break;

	case Engine::ELightType::POINT:
	{
		if (m_umapPointLightComponents.find(_wstrLightComponentName) == m_umapPointLightComponents.end()) { return nullptr; }

		return m_umapPointLightComponents[_wstrLightComponentName].lock();
	}
	break;

	case Engine::ELightType::SPOT:
	{
		if (m_umapSpotLightComponents.find(_wstrLightComponentName) == m_umapSpotLightComponents.end()) { return nullptr; }

		return m_umapSpotLightComponents[_wstrLightComponentName].lock();
	}
	break;

	default:
		break;
	}

	return nullptr;
}
