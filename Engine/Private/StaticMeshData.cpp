// default
#include "pch.h"
#include "StaticMeshData.h"

// mesh
#include "MeshBuffer.h"
#include "MeshShader.h"

// handler
#include "ModelHandler.h"

std::shared_ptr<CStaticMeshData> Engine::CStaticMeshData::Create(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrModelDesc, const std::wstring& _wstrVertexShaderDesc, const std::wstring& _wstrPixelShaderDesc)
{
	const shared_ptr<CStaticMeshData> spStaticMeshData = make_shared<CStaticMeshData>();
	ENSUREF(spStaticMeshData->Initialize(_spOwnerComponent, _wstrModelDesc, _wstrVertexShaderDesc, _wstrPixelShaderDesc), L"Failed to initialize static mesh data.");
	return spStaticMeshData;
}

HRESULT Engine::CStaticMeshData::Initialize(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrModelDesc, const std::wstring& _wstrVertexShaderDesc, const std::wstring& _wstrPixelShaderDesc)
{
	m_wpOwnerComponent = _spOwnerComponent;
	if (_wstrModelDesc.empty()) { return S_OK; }

	m_wstrStaticModelDesc = _wstrModelDesc;
	m_iNumMeshes = CModelHandler::GetInstance()->FindModelDesc(_wstrModelDesc)->m_iNumMeshes;
	m_spMeshBuffer = CMeshBuffer::Create(_wstrModelDesc);
	m_spMeshShader = CMeshShader::Create(_spOwnerComponent, nullptr, nullptr, _wstrModelDesc, _wstrVertexShaderDesc, _wstrPixelShaderDesc);
	m_spShadowMeshShader = CMeshShader::Create(_spOwnerComponent, nullptr, nullptr, _wstrModelDesc, L"VS_Shadow", L"PS_Shadow");
	return S_OK;
}

int32 Engine::CStaticMeshData::Tick()
{
	// 메시나 셰이더를 설정하지 않은 경우, 업데이트하지 않습니다.
	if (!m_spMeshBuffer || !m_spMeshShader) { return 0; }
	
	m_spShadowMeshShader->Tick();
	return m_spMeshShader->Tick();
}

void Engine::CStaticMeshData::Render()
{
	// 메시나 셰이더를 설정하지 않은 경우, 렌더하지 않습니다.
	if (!m_spMeshBuffer || !m_spMeshShader) { return; }

	for (uint16 iMeshIndex = 0; iMeshIndex < m_iNumMeshes; ++iMeshIndex)
	{
		m_spMeshBuffer->IASetVertexBuffer(iMeshIndex);
		m_spMeshBuffer->IASetIndexBuffer(iMeshIndex);
		m_spMeshBuffer->IASetPrimitiveTopology(iMeshIndex);
		m_spMeshShader->IASetInputLayout(iMeshIndex);

		m_spMeshShader->VSSetShader(iMeshIndex);
		m_spMeshShader->PSSetShader(iMeshIndex);

		m_spMeshShader->CopyConstantBuffers(iMeshIndex);

		m_spMeshShader->VSSetConstantBuffers(iMeshIndex);
		m_spMeshShader->PSSetConstantBuffers(iMeshIndex);

		m_spMeshShader->VSSetShaderResources(iMeshIndex);
		m_spMeshShader->PSSetShaderResources(iMeshIndex);

		m_spMeshShader->VSSetSamplers(iMeshIndex);
		m_spMeshShader->PSSetSamplers(iMeshIndex);

		m_spMeshBuffer->DrawIndexed(iMeshIndex);
	}
}

void Engine::CStaticMeshData::RenderShadow()
{
	for (uint16 iMeshIndex = 0; iMeshIndex < m_iNumMeshes; ++iMeshIndex)
	{
		m_spMeshBuffer->IASetVertexBuffer(iMeshIndex);
		m_spMeshBuffer->IASetIndexBuffer(iMeshIndex);
		m_spMeshBuffer->IASetPrimitiveTopology(iMeshIndex);
		m_spShadowMeshShader->IASetInputLayout(iMeshIndex);

		m_spShadowMeshShader->VSSetShader(iMeshIndex);
		m_spShadowMeshShader->PSSetShader(iMeshIndex);

		m_spShadowMeshShader->CopyConstantBuffers(iMeshIndex);

		m_spShadowMeshShader->VSSetConstantBuffers(iMeshIndex);
		m_spShadowMeshShader->PSSetConstantBuffers(iMeshIndex);

		m_spShadowMeshShader->VSSetShaderResources(iMeshIndex);
		m_spShadowMeshShader->PSSetShaderResources(iMeshIndex);

		m_spShadowMeshShader->VSSetSamplers(iMeshIndex);
		m_spShadowMeshShader->PSSetSamplers(iMeshIndex);

		m_spMeshBuffer->DrawIndexed(iMeshIndex);
	}
}

void Engine::CStaticMeshData::Release()
{
	if (m_spMeshBuffer)
	{
		m_spMeshBuffer->Release();
		m_spMeshBuffer = nullptr;
	}

	if (m_spMeshShader)
	{
		m_spMeshShader->Release();
		m_spMeshShader = nullptr;
	}

	if (m_spShadowMeshShader)
	{
		m_spShadowMeshShader->Release();
		m_spShadowMeshShader = nullptr;
	}
}

void Engine::CStaticMeshData::Clear()
{
	if (m_spMeshBuffer)
	{
		m_spMeshBuffer->Release();
		m_spMeshBuffer = nullptr;
	}

	if (m_spMeshShader)
	{
		m_spMeshShader->Release();
		m_spMeshShader = nullptr;
	}

	if (m_spShadowMeshShader)
	{
		m_spShadowMeshShader->Release();
		m_spShadowMeshShader = nullptr;
	}
}

HRESULT Engine::CStaticMeshData::ChangeModelDesc(const std::wstring& _wstrModelDesc)
{
	if (m_wstrStaticModelDesc == _wstrModelDesc) { return S_OK; }

	m_wstrStaticModelDesc = _wstrModelDesc;
	m_iNumMeshes = CModelHandler::GetInstance()->FindModelDesc(_wstrModelDesc)->m_iNumMeshes;

	// 이미 메시 버퍼가 있는 경우
	if (m_spMeshBuffer)
	{
		m_spMeshBuffer->Release();
		m_spMeshBuffer = nullptr;
	}
	m_spMeshBuffer = CMeshBuffer::Create(_wstrModelDesc);

	if (m_spMeshShader)
	{
		m_spMeshShader->Release();
		m_spMeshShader = nullptr;
	}
	m_spMeshShader = CMeshShader::Create(m_wpOwnerComponent.lock(), nullptr, nullptr, _wstrModelDesc, L"VS_StaticMesh", L"PS_StaticMesh");
	return S_OK;
}
