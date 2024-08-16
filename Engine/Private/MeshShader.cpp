#include "pch.h"
#include "MeshShader.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "ModelHandler.h"
#include "ShaderHandler.h"
#include "EffectHandler.h"

#include "Texture.h"
#include "Sampler.h"
#include "ConstantBuffer.h"

#include "WorldViewProjectionConstantBuffer.h"
#include "WorldInvTransWorldViewProjectionConstantBuffer.h"
#include "BoneConstantBuffer.h"
#include "RimConstantBuffer.h"
#include "TextureConstantBuffer.h"
#include "MeshEffectConstantBuffer.h"
#include "MeshEffectTransformConstantBuffer.h"
#include "LightViewLightProjectionConstantBuffer.h"
#include "WorldConstantBuffer.h"

#include "SceneComponent.h"

std::shared_ptr<CMeshShader> Engine::CMeshShader::Create
(
	const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
	const std::shared_ptr<CSkeletalMeshData>& _spSkeletalMeshData,
	const std::shared_ptr<CEffectMeshData>& _spEffectMeshData,
	const std::wstring& _wstrModelDesc,
	const std::wstring& _wstrVertexShaderDesc,
	const std::wstring& _wstrPixelShaderDesc
)
{
	const shared_ptr<CMeshShader> spMeshShader = make_shared<CMeshShader>();
	ENSUREF(spMeshShader->Initialize(_spOwnerComponent, _spSkeletalMeshData, _spEffectMeshData, _wstrModelDesc, _wstrVertexShaderDesc, _wstrPixelShaderDesc), L"Failed to initialize MeshShader.");
	return spMeshShader;
}

HRESULT Engine::CMeshShader::Initialize
(
	const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
	const std::shared_ptr<CSkeletalMeshData>& _spSkeletalMeshData,
	const std::shared_ptr<CEffectMeshData>& _spEffectMeshData,
	const std::wstring& _wstrModelDesc,
	const std::wstring& _wstrVertexShaderDesc,
	const std::wstring& _wstrPixelShaderDesc
)
{
	if (_wstrModelDesc.empty() || _wstrVertexShaderDesc.empty() || _wstrPixelShaderDesc.empty()) { return S_OK; }

	shared_ptr<FModelDesc> spModelDesc = CModelHandler::GetInstance()->FindModelDesc(_wstrModelDesc);
	if (!spModelDesc) {	spModelDesc = CEffectHandler::GetInstance()->FindModelDesc(_wstrModelDesc); }

	shared_ptr<FVertexShaderDesc> spVertexShaderDesc = CShaderHandler::GetInstance()->FindVertexShaderDesc(_wstrVertexShaderDesc);
	shared_ptr<FPixelShaderDesc> spPixelShaderDesc = CShaderHandler::GetInstance()->FindPixelShaderDesc(_wstrPixelShaderDesc);

	uint32 iNumMeshes = spModelDesc->m_iNumMeshes;

	// 버텍스 셰이더, 픽셀 셰이더
	m_vecVertexShaders.reserve(iNumMeshes);
	m_vecVertexShaders.resize(iNumMeshes);
	m_vecPixelShaders.reserve(iNumMeshes);
	m_vecPixelShaders.resize(iNumMeshes);

	for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
	{
		m_vecVertexShaders[iIndex] = CVertexShader::Create<CVertexShader>(spVertexShaderDesc);
		m_vecPixelShaders[iIndex] = CPixelShader::Create<CPixelShader>(spPixelShaderDesc);
	}

	// 버텍스 셰이더 텍스쳐
	auto& vecVertexTextureInfo = spVertexShaderDesc->m_vecTextureInfo;
	if (!vecVertexTextureInfo.empty())
	{
		m_vecVSMaterials.reserve(iNumMeshes);
		m_vecVSMaterials.resize(iNumMeshes);

		for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
		{
			m_vecVSMaterials[iIndex].reserve(vecVertexTextureInfo.size());
			m_vecVSMaterials[iIndex].resize(vecVertexTextureInfo.size());

			for (size_t jIndex = 0; jIndex < vecVertexTextureInfo.size(); ++jIndex)
			{
				wstring wstrModelName = spModelDesc->m_wstrModelName + L"_" + to_wstring(spModelDesc->m_vecMaterialIndices[iIndex]) + L"_" + to_wstring(jIndex);

				// 텍스처 이름, 레지스터 번호를 인자로 전달합니다.
				m_vecVSMaterials[iIndex][jIndex] = CTexture::Create(wstrModelName, vecVertexTextureInfo[jIndex].first, true);
			}
		}
	}

	// 픽셀 셰이더 텍스쳐
	auto& vecPixelTextureInfo = spPixelShaderDesc->m_vecTextureInfo;
	if (!vecPixelTextureInfo.empty())
	{
		// 픽셀 셰이더에서 텍스쳐를 사용하는 경우
		m_vecPSMaterials.reserve(iNumMeshes);
		m_vecPSMaterials.resize(iNumMeshes);

		for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
		{
			m_vecPSMaterials[iIndex].reserve(vecPixelTextureInfo.size());
			m_vecPSMaterials[iIndex].resize(vecPixelTextureInfo.size());

			for (size_t jIndex = 0; jIndex < vecPixelTextureInfo.size(); ++jIndex)
			{
				wstring wstrModelName = spModelDesc->m_wstrModelName + L"_" + to_wstring(spModelDesc->m_vecMaterialIndices[iIndex]) + L"_" + to_wstring(jIndex);

				// 텍스쳐 이름, 레지스터 번호를 인자로 전달합니다.
				m_vecPSMaterials[iIndex][jIndex] = CTexture::Create(wstrModelName, vecPixelTextureInfo[jIndex].first, true);
			}
		}
	}

	// 버텍스 셰이더 상수 버퍼
	auto& vecVSConstantBufferInfo = spVertexShaderDesc->m_vecConstantBufferInfo;
	if (!vecVSConstantBufferInfo.empty())
	{
		m_vecVSConstantBuffers.reserve(iNumMeshes);
		m_vecVSConstantBuffers.resize(iNumMeshes);

		for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
		{
			m_vecVSConstantBuffers[iIndex].reserve(vecVSConstantBufferInfo.size());
			m_vecVSConstantBuffers[iIndex].resize(vecVSConstantBufferInfo.size());

			for (size_t jIndex = 0; jIndex < vecVSConstantBufferInfo.size(); ++jIndex)
			{
				if (vecVSConstantBufferInfo[jIndex].second == L"CB_WorldViewProjection")
				{
					m_vecVSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CWorldViewProjectionConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_WorldViewProjection", vecVSConstantBufferInfo[jIndex].first);
				}

				else if (vecVSConstantBufferInfo[jIndex].second == L"CB_World")
				{
					m_vecVSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CWorldConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_World", vecVSConstantBufferInfo[jIndex].first);
				}

				else if (vecVSConstantBufferInfo[jIndex].second == L"CB_WorldInvTransWorldViewProjection")
				{
					m_vecVSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CWorldInvTransWorldViewProjectionConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_WorldInvTransWorldViewProjection", vecVSConstantBufferInfo[jIndex].first);
				}

				else if (vecVSConstantBufferInfo[jIndex].second == L"CB_Bone")
				{
					m_vecVSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CBoneConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_Bone", vecVSConstantBufferInfo[jIndex].first);
					m_vecVSConstantBuffers[iIndex][jIndex]->SetSkeletalMeshData(_spSkeletalMeshData);
				}

				else if (vecVSConstantBufferInfo[jIndex].second == L"CB_MeshEffectTransform")
				{
					shared_ptr<CMeshEffectTransformConstantBuffer> spMeshEffectTransform = CConstantBuffer::Create<CMeshEffectTransformConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_MeshEffectTransform", vecVSConstantBufferInfo[jIndex].first);
					m_vecVSConstantBuffers[iIndex][jIndex] = spMeshEffectTransform;
					spMeshEffectTransform->SetEffectMeshData(_spEffectMeshData);
				}

				else if (vecVSConstantBufferInfo[jIndex].second == L"CB_LightViewLightProjection")
				{
					m_vecVSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CLightViewLightProjectionConstantBuffer>
						(
							_spOwnerComponent->GetOwnerActor(),
							L"CB_LightViewLightProjection",
							vecVSConstantBufferInfo[jIndex].first
						);
				}
			}
		}
	}

	// 픽셀 셰이더 상수 버퍼
	auto& vecPSConstantBufferInfo = spPixelShaderDesc->m_vecConstantBufferInfo;
	if (!vecPSConstantBufferInfo.empty())
	{
		m_vecPSConstantBuffers.reserve(iNumMeshes);
		m_vecPSConstantBuffers.resize(iNumMeshes);

		for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
		{
			m_vecPSConstantBuffers[iIndex].reserve(vecPSConstantBufferInfo.size());
			m_vecPSConstantBuffers[iIndex].resize(vecPSConstantBufferInfo.size());

			for (size_t jIndex = 0; jIndex < vecPSConstantBufferInfo.size(); ++jIndex)
			{
				if (vecPSConstantBufferInfo[jIndex].second == L"CB_WorldViewProjection")
				{
					m_vecVSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CWorldViewProjectionConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_WorldViewProjection", vecPSConstantBufferInfo[jIndex].first);
				}

				else if (vecPSConstantBufferInfo[jIndex].second == L"CB_WorldInvTransWorldViewProjection")
				{
					m_vecPSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CWorldInvTransWorldViewProjectionConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_WorldInvTransWorldViewProjection", vecPSConstantBufferInfo[jIndex].first);
				}

				else if (vecPSConstantBufferInfo[jIndex].second == L"CB_Bone")
				{
					m_vecPSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CBoneConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_Bone", vecPSConstantBufferInfo[jIndex].first);
					m_vecPSConstantBuffers[iIndex][jIndex]->SetSkeletalMeshData(_spSkeletalMeshData);
				}

				else if (vecPSConstantBufferInfo[jIndex].second == L"CB_Rim")
				{
					m_vecPSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CRimConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_Rim", vecPSConstantBufferInfo[jIndex].first);
				}

				else if (vecPSConstantBufferInfo[jIndex].second == L"CB_MeshEffect")
				{
					shared_ptr<CMeshEffectConstantBuffer> spMeshEffectConstantBuffer = CConstantBuffer::Create<CMeshEffectConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_MeshEffect", vecPSConstantBufferInfo[jIndex].first);
					m_vecPSConstantBuffers[iIndex][jIndex] = spMeshEffectConstantBuffer;
					spMeshEffectConstantBuffer->SetEffectMeshData(_spEffectMeshData);
				}

				else if (vecPSConstantBufferInfo[jIndex].second == L"CB_Texture")
				{
					shared_ptr<CTextureConstantBuffer> spTextureConstantBuffer = CConstantBuffer::Create<CTextureConstantBuffer>(_spOwnerComponent->GetOwnerActor(), L"CB_Texture", vecPSConstantBufferInfo[jIndex].first);
					m_vecPSConstantBuffers[iIndex][jIndex] = spTextureConstantBuffer;
					
					uint32 iMaterialIndex = spModelDesc->m_vecMaterialIndices[iIndex];

					for (const auto& iTextureIndex : spModelDesc->m_vecTextureIndices[iMaterialIndex])
					{
						switch (iTextureIndex)
						{
						case 1:		spTextureConstantBuffer->SetDiffuseTexture(1);	break;
						case 5:
						case 6:		spTextureConstantBuffer->SetNormalTexture(1);	break;
						default:	break;
						}
						
						spTextureConstantBuffer->SetBaseColor(spModelDesc->m_vecBaseColors[iMaterialIndex]);
					}
				}

				else if (vecPSConstantBufferInfo[jIndex].second == L"CB_LightViewLightProjection")
				{
					m_vecPSConstantBuffers[iIndex][jIndex] = CConstantBuffer::Create<CLightViewLightProjectionConstantBuffer>
						(
							_spOwnerComponent->GetOwnerActor(),
							L"CB_LightViewLightProjection",
							vecPSConstantBufferInfo[jIndex].first
						);
				}
			}
		}
	}

	// 버텍스 셰이더 샘플러
	auto& vecVSSamplerInfo = spVertexShaderDesc->m_vecSamplerInfo;
	if (!vecVSSamplerInfo.empty())
	{
		m_vecVSSamplers.reserve(iNumMeshes);
		m_vecVSSamplers.resize(iNumMeshes);

		for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
		{
			m_vecVSSamplers[iIndex] = CSampler::Create(L"SS_FILTER_LINEAR_ADDRESS_WRAP", 0);
		}
	}

	// 픽셀 셰이더 샘플러
	auto& vecPSSamplerInfo = spPixelShaderDesc->m_vecSamplerInfo;
	if (!vecPSSamplerInfo.empty())
	{
		m_vecPSSamplers.reserve(iNumMeshes);
		m_vecPSSamplers.resize(iNumMeshes);

		for (uint32 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
		{
			m_vecPSSamplers[iIndex] = CSampler::Create(L"SS_FILTER_LINEAR_ADDRESS_WRAP", 0);
		}
	}

	return S_OK;
}

int32 Engine::CMeshShader::Tick()
{
	for (size_t iIndex = 0; iIndex < m_vecVSConstantBuffers.size(); ++iIndex)
	{
		for (size_t jIndex = 0; jIndex < m_vecVSConstantBuffers[iIndex].size(); ++jIndex)
		{
			m_vecVSConstantBuffers[iIndex][jIndex]->TickConstantBuffer(static_cast<uint32>(iIndex));
		}
	}

	for (size_t iIndex = 0; iIndex < m_vecPSConstantBuffers.size(); ++iIndex)
	{
		for (size_t jIndex = 0; jIndex < m_vecPSConstantBuffers[iIndex].size(); ++jIndex)
		{
			m_vecPSConstantBuffers[iIndex][jIndex]->TickConstantBuffer(static_cast<uint32>(iIndex));
		}
	}

	return 0;
}

void Engine::CMeshShader::Release()
{
	// 버텍스 셰이더
	for (auto& spVertexShader : m_vecVertexShaders)
	{
		spVertexShader->Release();
		spVertexShader = nullptr;
	}
	m_vecVertexShaders.clear();

	// 버텍스 셰이더 텍스처
	for (auto& arrTextures : m_vecVSMaterials)
	{
		for (auto& spTexture : arrTextures)
		{
			if (!spTexture) { continue; }
			
			spTexture->Release();
			spTexture = nullptr;
		}
	}
	m_vecVSMaterials.clear();

	// 버텍스 셰이더 상수 버퍼
	for (auto& vecConstantBuffers : m_vecVSConstantBuffers)
	{
		for (auto& spConstantBuffer : vecConstantBuffers)
		{
			spConstantBuffer->Release();
			spConstantBuffer = nullptr;
		}
		vecConstantBuffers.clear();
	}
	m_vecVSConstantBuffers.clear();

	// 버텍스 셰이더 샘플러
	for (auto& spSampler : m_vecVSSamplers)
	{
		spSampler->Release();
		spSampler = nullptr;
	}
	m_vecVSSamplers.clear();

	// 픽셀 셰이더
	for (auto& spPixelShader : m_vecPixelShaders)
	{
		spPixelShader->Release();
		spPixelShader = nullptr;
	}
	m_vecPixelShaders.clear();

	// 픽셀 셰이더 텍스처
	for (auto& arrTextures : m_vecPSMaterials)
	{
		for (auto& spTexture : arrTextures)
		{
			if (!spTexture) { continue; }

			spTexture->Release();
			spTexture = nullptr;
		}
	}
	m_vecPSMaterials.clear();

	// 픽셀 셰이더 상수 버퍼
	for (auto& vecConstantBuffers : m_vecPSConstantBuffers)
	{
		for (auto& spConstantBuffer : vecConstantBuffers)
		{
			spConstantBuffer->Release();
			spConstantBuffer = nullptr;
		}
		vecConstantBuffers.clear();
	}
	m_vecPSConstantBuffers.clear();

	// 픽셀 셰이더 샘플러
	for (auto& spSampler : m_vecPSSamplers)
	{
		spSampler->Release();
		spSampler = nullptr;
	}
	m_vecPSSamplers.clear();
}

void Engine::CMeshShader::IASetInputLayout(uint16 _iMeshIndex)
{
	m_vecVertexShaders[_iMeshIndex]->IASetInputLayout();
}

void Engine::CMeshShader::CopyConstantBuffers(uint16 _iMeshIndex)
{
	if (!m_vecVSConstantBuffers.empty())
	{
		for (size_t iIndex = 0; iIndex < m_vecVSConstantBuffers[_iMeshIndex].size(); ++iIndex)
		{
			m_vecVSConstantBuffers[_iMeshIndex][iIndex]->CopyConstantBuffer(_iMeshIndex);
		}
	}

	if (!m_vecPSConstantBuffers.empty())
	{
		for (const auto& spPSConstantBuffers : m_vecPSConstantBuffers[_iMeshIndex])
		{
			spPSConstantBuffers->CopyConstantBuffer(_iMeshIndex);
		}
	}
}

void Engine::CMeshShader::VSSetShader(uint16 _iMeshIndex)
{
	m_vecVertexShaders[_iMeshIndex]->VSSetShader();
}

void Engine::CMeshShader::VSSetConstantBuffers(uint16 _iMeshIndex)
{
	if (m_vecVSConstantBuffers.empty()) { return; }

	for (const auto& spConstantBuffer : m_vecVSConstantBuffers[_iMeshIndex])
	{
		spConstantBuffer->VSSetConstantBuffers();
	}
}

void Engine::CMeshShader::VSSetShaderResources(uint16 _iMeshIndex)
{
	if (m_vecVSMaterials.empty()) { return; }

	for (const auto& spTexture : m_vecVSMaterials[_iMeshIndex])
	{
		if (spTexture)
		{
			spTexture->VSSetShaderResources();
		}
	}
}

void Engine::CMeshShader::VSSetSamplers(uint16 _iMeshIndex)
{
	if (m_vecVSSamplers.empty()) { return; }

	m_vecVSSamplers[_iMeshIndex]->VSSetSamplers();
}

void Engine::CMeshShader::PSSetShader(uint16 _iMeshIndex)
{
	m_vecPixelShaders[_iMeshIndex]->PSSetShader();
}

void Engine::CMeshShader::PSSetConstantBuffers(uint16 _iMeshIndex)
{
	if (m_vecPSConstantBuffers.empty()) { return; }

	for (const auto& spConstantBuffer : m_vecPSConstantBuffers[_iMeshIndex])
	{
		spConstantBuffer->PSSetConstantBuffers();
	}
}

void Engine::CMeshShader::PSSetShaderResources(uint16 _iMeshIndex)
{
	if (m_vecPSMaterials.empty()) { return; }

	for (const auto& spTexture : m_vecPSMaterials[_iMeshIndex])
	{
		if (spTexture)
		{
			spTexture->PSSetShaderResources();
		}
	}
}

void Engine::CMeshShader::PSSetSamplers(uint16 _iMeshIndex)
{
	if (m_vecPSSamplers.empty()) { return; }

	m_vecPSSamplers[_iMeshIndex]->PSSetSamplers();
}

void Engine::CMeshShader::ModifyPixelShaderTexture(int32 _iMeshIndex, int32 _iTextureIndex, const std::wstring& _wstrTextureName)
{
	if (m_vecPSMaterials.size() <= _iMeshIndex) { return; }

	if (m_vecPSMaterials[_iMeshIndex].size() <= _iTextureIndex) { return; }

	// 이미 텍스처가 있는 경우
	if (m_vecPSMaterials[_iMeshIndex][_iTextureIndex])
	{
		m_vecPSMaterials[_iMeshIndex][_iTextureIndex]->Release();
		m_vecPSMaterials[_iMeshIndex][_iTextureIndex] = nullptr;
	}

	m_vecPSMaterials[_iMeshIndex][_iTextureIndex] = CTexture::Create(_wstrTextureName, _iTextureIndex, true);
}
