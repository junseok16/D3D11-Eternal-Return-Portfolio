#include "pch.h"
#include "SkeletalMeshData.h"

// mesh
#include "MeshBuffer.h"
#include "MeshShader.h"
#include "MeshBone.h"

// handler
#include "ModelHandler.h"

std::shared_ptr<CSkeletalMeshData> Engine::CSkeletalMeshData::Create(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrModelDesc, const std::wstring& _wstrVertexShaderDesc, const std::wstring& _wstrPixelShaderDesc)
{
	const shared_ptr<CSkeletalMeshData> spSkeletalMeshData = make_shared<CSkeletalMeshData>();
	ENSUREF(spSkeletalMeshData->Initialize(_spOwnerComponent, _wstrModelDesc, _wstrVertexShaderDesc, _wstrPixelShaderDesc), L"Failed to initialize skeletal mesh data.");
	return spSkeletalMeshData;
}

HRESULT Engine::CSkeletalMeshData::Initialize(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrModelDesc, const std::wstring& _wstrVertexShaderDesc, const std::wstring& _wstrPixelShaderDesc)
{
	m_wpOwnerComponent = _spOwnerComponent;
	if (_wstrModelDesc.empty()) { return S_OK; }

	m_iNumMeshes = CModelHandler::GetInstance()->FindModelDesc(_wstrModelDesc)->m_iNumMeshes;
	m_spMeshBuffer = CMeshBuffer::Create(_wstrModelDesc);
	m_spMeshShader = CMeshShader::Create(_spOwnerComponent, shared_from_this(), nullptr, _wstrModelDesc, _wstrVertexShaderDesc, _wstrPixelShaderDesc);
	m_spShadowMeshShader = CMeshShader::Create(_spOwnerComponent, nullptr, nullptr, _wstrModelDesc, L"VS_Shadow", L"PS_Shadow");

	m_spMeshBone = CMeshBone::Create(_spOwnerComponent, _wstrModelDesc);

	return S_OK;
}

int32 Engine::CSkeletalMeshData::Tick(float _fDeltaSeconds)
{
	if (!m_spMeshShader) { return 0; }

	// 행렬을 계산한다.
	if (m_bPlayAnimation)
	{
		m_spMeshBone->Tick(_fDeltaSeconds);
	}
	
	// 부모 행렬과 자식 행렬을 곱한다.
	m_spShadowMeshShader->Tick();
	return m_spMeshShader->Tick();
}

void Engine::CSkeletalMeshData::RenderShadow()
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

void Engine::CSkeletalMeshData::Render()
{
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

void Engine::CSkeletalMeshData::Release()
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

	if (m_spMeshBone)
	{
		m_spMeshBone->Release();
		m_spMeshBone = nullptr;
	}

	if (m_spShadowMeshShader)
	{
		m_spShadowMeshShader->Release();
		m_spShadowMeshShader = nullptr;
	}
}

void Engine::CSkeletalMeshData::SetAnimData(const std::shared_ptr<CAnimData>& _spAnimData)
{
	m_wpAnimData = _spAnimData;
	m_spMeshBone->SetAnimData(_spAnimData);
}

std::shared_ptr<CBone> Engine::CSkeletalMeshData::FindBone(const std::string& _strBoneName)
{
	return m_spMeshBone->FindBone(_strBoneName);
}

void Engine::CSkeletalMeshData::SetPlayRate(float _fPlayRate)
{
	m_spMeshBone->SetPlayRate(_fPlayRate);
}
