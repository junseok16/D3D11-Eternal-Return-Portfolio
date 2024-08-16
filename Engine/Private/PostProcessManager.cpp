#include "pch.h"
#include "PostProcessManager.h"

#include "DeviceManager.h"
#include "LightManager.h"
#include "ShaderHandler.h"
#include "StateHandler.h"
#include "ViewHandler.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "Texture.h"
#include "Sampler.h"
#include "DepthStencil.h"
#include "Blend.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "DeferredWorldViewProjectionConstantBuffer.h"
#include "InvViewInvProjectionConstantBuffer.h"
#include "LightViewLightProjectionConstantBuffer.h"
#include "LightConstantBuffer.h"

HRESULT Engine::CPostProcessManager::PreInitialize(const std::shared_ptr<CLightManager>& _spLightManager)
{
	m_wpLightManager = _spLightManager;
	return S_OK;
}

HRESULT Engine::CPostProcessManager::Initialize()
{
	m_wpViewHandler = CViewHandler::GetInstance();
	m_wpStateHandler = CStateHandler::GetInstance();
	m_wpShaderHandler = CShaderHandler::GetInstance();

	float fWindowSizeX = static_cast<float>(m_wpStateHandler.lock()->GetDeviceManager()->GetWindowSizeX());
	float fWindowSizeY = static_cast<float>(m_wpStateHandler.lock()->GetDeviceManager()->GetWindowSizeY());

	m_matDeferredWorld._11 = fWindowSizeX;
	m_matDeferredWorld._22 = fWindowSizeY;
	m_matDeferredView = Matrix::Identity;
	m_matDeferredOrthogonalProjection = XMMatrixOrthographicLH(fWindowSizeX, fWindowSizeY, 0.0f, 1.0f);

	m_spVertexBuffer = CVertexBuffer::Create<CVertexBuffer>(nullptr, -1, EPrimitiveType::RECT);
	m_wpLightManager.lock()->SetVertexBuffer(m_spVertexBuffer);

	m_spIndexBuffer = CIndexBuffer::Create<CIndexBuffer>(nullptr, -1, EPrimitiveType::RECT);
	m_wpLightManager.lock()->SetIndexBuffer(m_spIndexBuffer);

	shared_ptr<FVertexShaderDesc> spVSDesc = m_wpShaderHandler.lock()->FindVertexShaderDesc(L"VS_DeferredBegin");
	m_spVertexShader = CVertexShader::Create<CVertexShader>(spVSDesc);
	m_wpLightManager.lock()->SetVertexShader(m_spVertexShader);

	shared_ptr<FPixelShaderDesc> spPSDesc = m_wpShaderHandler.lock()->FindPixelShaderDesc(L"PS_DeferredEnd");
	m_spPostProcessPixelShader = CPixelShader::Create<CPixelShader>(spPSDesc);

	// 버텍스 셰이더 상수 버퍼를 생성합니다.
	shared_ptr<CDeferredWorldViewProjectionConstantBuffer> spDefWVP = CConstantBuffer::Create<CDeferredWorldViewProjectionConstantBuffer>(nullptr, L"CB_DeferredWorldViewProjection", 0);
	spDefWVP->SetWorldMatrix(m_matDeferredWorld);
	spDefWVP->SetViewMatrix(m_matDeferredView);
	spDefWVP->SetProjectionMatix(m_matDeferredOrthogonalProjection);
	spDefWVP->CopyConstantBuffer(0);
	m_spVSConstantBuffers = spDefWVP;
	m_wpLightManager.lock()->SetVertexConstantBuffer(m_spVSConstantBuffers);
	
	// 픽셀 셰이더 상수 버퍼를 생성합니다.
	shared_ptr<CInvViewInvProjectionConstantBuffer> spInvVInvP = CConstantBuffer::Create<CInvViewInvProjectionConstantBuffer>(nullptr, L"CB_InvViewInvProjection", 0);
	m_spPSConstantBuffers[0] = spInvVInvP;


	shared_ptr<CLightViewLightProjectionConstantBuffer> spLightVP = CConstantBuffer::Create<CLightViewLightProjectionConstantBuffer>(nullptr, L"CB_LightViewLightProjection", 1);
	m_spPSConstantBuffers[1] = spLightVP;

	// 픽셀 셰이더 텍스처를 생성합니다.
	m_vecPostProcessPixelShaderTextures.resize(4);
	m_vecPostProcessPixelShaderTextures[0] = CTexture::Create(L"DIFFUSE", 0, false);
	m_vecPostProcessPixelShaderTextures[1] = CTexture::Create(L"SHADE", 1, false);
	m_vecPostProcessPixelShaderTextures[2] = CTexture::Create(L"DEPTH", 2, false);
	m_vecPostProcessPixelShaderTextures[3] = CTexture::Create(L"SHADOW", 3, false);

	// 픽셀 셰이더 샘플러를 생성합니다.
	m_spPSSampler[0] = CSampler::Create(L"SS_FILTER_POINT_ADDRESS_WRAP", 0);
	m_spPSSampler[1] = CSampler::Create(L"SS_FILTER_LINEAR_ADDRESS_WRAP", 1);
	m_spPSSampler[2] = CSampler::Create(L"CSS_FILTER_LINEAR_ADDRESS_BORDER", 2);
	return S_OK;
}

int32 Engine::CPostProcessManager::Tick()
{
	return 0;
}

void Engine::CPostProcessManager::Render()
{
}

void Engine::CPostProcessManager::Release()
{
	m_spVertexShader->Release();
	m_spVertexShader = nullptr;

	m_spVSConstantBuffers->Release();
	m_spVSConstantBuffers = nullptr;

	m_spPostProcessPixelShader->Release();
	m_spPostProcessPixelShader = nullptr;
	
	for (auto& spPSTexture : m_vecPostProcessPixelShaderTextures)
	{
		spPSTexture->Release();
		spPSTexture = nullptr;
	}
	
	for (int32 iIndex = 0; iIndex < 3; ++iIndex)
	{
		m_spPSSampler[iIndex]->Release();
		m_spPSSampler[iIndex] = nullptr;
	}

	m_spVertexBuffer->Release();
	m_spVertexBuffer = nullptr;

	m_spIndexBuffer->Release();
	m_spIndexBuffer = nullptr;
}

void Engine::CPostProcessManager::RenderLight()
{
	m_wpLightManager.lock()->Render();
}

void Engine::CPostProcessManager::RenderPostProcess()
{
	m_spVertexBuffer->IASetVertexBuffer();
	m_spIndexBuffer->IASetIndexBuffer();
	m_spIndexBuffer->IASetPrimitiveTopology();

	m_spVertexShader->IASetInputLayout();
	m_spVertexShader->VSSetShader();
	m_spPostProcessPixelShader->PSSetShader();

	m_spVSConstantBuffers->CopyConstantBuffer(0);
	m_spVSConstantBuffers->VSSetConstantBuffers();

	m_spPSConstantBuffers[0]->TickConstantBuffer(0);
	m_spPSConstantBuffers[0]->CopyConstantBuffer(0);
	m_spPSConstantBuffers[0]->PSSetConstantBuffers();

	m_spPSConstantBuffers[1]->TickConstantBuffer(0);
	m_spPSConstantBuffers[1]->CopyConstantBuffer(0);
	m_spPSConstantBuffers[1]->PSSetConstantBuffers();

	m_vecPostProcessPixelShaderTextures[0]->PSSetShaderResources();
	m_vecPostProcessPixelShaderTextures[1]->PSSetShaderResources();
	m_vecPostProcessPixelShaderTextures[2]->PSSetShaderResources();
	m_vecPostProcessPixelShaderTextures[3]->PSSetShaderResources();

	m_spPSSampler[0]->PSSetSamplers();
	m_spPSSampler[1]->PSSetSamplers();
	m_spPSSampler[2]->PSSetSamplers();

	m_spIndexBuffer->DrawIndexed();
	m_vecPostProcessPixelShaderTextures[0]->PSUnsetShaderResources();
	m_vecPostProcessPixelShaderTextures[1]->PSUnsetShaderResources();
	m_vecPostProcessPixelShaderTextures[2]->PSUnsetShaderResources();
	m_vecPostProcessPixelShaderTextures[3]->PSUnsetShaderResources();
}

void Engine::CPostProcessManager::RenderDebug()
{

}

HRESULT Engine::CPostProcessManager::BeginViewGroup(const std::wstring& _wstrViewGroupName)
{
	return m_wpViewHandler.lock()->BeginViewGroup(_wstrViewGroupName);
}

HRESULT Engine::CPostProcessManager::EndViewGroup()
{
	return m_wpViewHandler.lock()->EndViewGroup();
}
