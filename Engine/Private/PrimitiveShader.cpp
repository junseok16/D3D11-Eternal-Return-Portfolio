// default
#include "pch.h"
#include "PrimitiveShader.h"

// component
#include "SceneComponent.h"

// shader
#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "Sampler.h"
#include "ConstantBuffer.h"

// constant buffer
#include "CameraPositionConstantBuffer.h"
#include "WorldConstantBuffer.h"
#include "WorldViewOrthoProjConstantBuffer.h"
#include "WorldViewProjectionConstantBuffer.h"
#include "WorldInvTransWorldViewProjectionConstantBuffer.h"
#include "ViewProjectionConstantBuffer.h"
#include "ViewOrthoProjConstantBuffer.h"
#include "Size2DConstantBuffer.h"
#include "BillboardProjectileConstantBuffer.h"
#include "RatioConstantBuffer.h"
#include "LightViewLightProjectionConstantBuffer.h"
#include "ColorConstantBuffer.h"
#include "LerpConstantBuffer.h"

// handler
#include "ViewHandler.h"
#include "ShaderHandler.h"

std::shared_ptr<CPrimitiveShader> Engine::CPrimitiveShader::Create
(
	const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
	EPrimitiveType _ePrimitiveType,
	const std::vector<std::wstring>& _vecTextureNames,
	const std::wstring& _wstrVertexShaderDesc,
	const std::wstring& _wstrPixelShaderDesc,
	const std::wstring& _wstrGeometryShaderDesc
)
{
	const shared_ptr<CPrimitiveShader> spPrimitiveShader = make_shared<CPrimitiveShader>();
	ENSUREF(spPrimitiveShader->Initialize
	(
		_spOwnerComponent,
		_ePrimitiveType,
		_vecTextureNames,
		_wstrVertexShaderDesc, 
		_wstrPixelShaderDesc,
		_wstrGeometryShaderDesc
	), L"Failed to initialize primitive shader.");

	return spPrimitiveShader;
}

HRESULT Engine::CPrimitiveShader::Initialize
(
	const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
	EPrimitiveType _ePrimitiveType,
	const std::vector<std::wstring>& _vecTextureNames,
	const std::wstring& _wstrVertexShaderDesc,
	const std::wstring& _wstrPixelShaderDesc,
	const std::wstring& _wstrGeometryShaderDesc
)
{
	m_ePrimitiveType = _ePrimitiveType;
	if ( _wstrVertexShaderDesc.empty() || _wstrPixelShaderDesc.empty()) { return S_OK; }

	shared_ptr<FVertexShaderDesc> spVertexShaderDesc = CShaderHandler::GetInstance()->FindVertexShaderDesc(_wstrVertexShaderDesc);
	shared_ptr<FPixelShaderDesc> spPixelShaderDesc = CShaderHandler::GetInstance()->FindPixelShaderDesc(_wstrPixelShaderDesc);
	shared_ptr<FGeometryShaderDesc> spGeometryShaderDesc = CShaderHandler::GetInstance()->FindGeometryShaderDesc(_wstrGeometryShaderDesc);

	// 버텍스 셰이더
	m_spVertexShader = CVertexShader::Create<CVertexShader>(spVertexShaderDesc);

	// 픽셀 셰이더
	m_spPixelShader = CPixelShader::Create<CPixelShader>(spPixelShaderDesc);

	// 지오메트리 셰이더
	switch (_ePrimitiveType)
	{
	case Engine::EPrimitiveType::POINT:
	case Engine::EPrimitiveType::INSTANCE_POINT:
		m_spGeometryShader = CGeometryShader::Create<CGeometryShader>(spGeometryShaderDesc);
		break;

	case Engine::EPrimitiveType::RECT:
		break;

	case Engine::EPrimitiveType::CUBE:
		break;

	case Engine::EPrimitiveType::ENUM_END:
		break;

	default:
		break;
	}

	// 버텍스 셰이더 텍스처가 없습니다.
	
	// 픽셀 셰이더 텍스쳐
	auto& vecPixelTextureInfo = spPixelShaderDesc->m_vecTextureInfo;
	if (!vecPixelTextureInfo.empty())
	{
		m_vecPSMaterials.reserve(vecPixelTextureInfo.size());
		m_vecPSMaterials.resize(vecPixelTextureInfo.size());

		for (size_t iIndex = 0; iIndex < vecPixelTextureInfo.size(); ++iIndex)
		{
			m_vecPSMaterials[iIndex].reserve(_vecTextureNames.size());
			m_vecPSMaterials[iIndex].resize(_vecTextureNames.size());

			for (size_t jIndex = 0; jIndex < _vecTextureNames.size(); ++jIndex)
			{
				// 텍스쳐 이름, 레지스터 번호를 인자로 전달합니다.
				m_vecPSMaterials[iIndex][jIndex] = CTexture::Create(_vecTextureNames[jIndex], vecPixelTextureInfo[iIndex].first, false);
			}
		}
	}

	// 지오메트리 텍스처가 없습니다.

	// 버텍스 셰이더 상수 버퍼
	auto& vecVSConstantBufferInfo = spVertexShaderDesc->m_vecConstantBufferInfo;
	if (!vecVSConstantBufferInfo.empty())
	{
		m_vecVSConstantBuffers.reserve(vecVSConstantBufferInfo.size());
		m_vecVSConstantBuffers.resize(vecVSConstantBufferInfo.size());

		for (size_t jIndex = 0; jIndex < vecVSConstantBufferInfo.size(); ++jIndex)
		{
			if (vecVSConstantBufferInfo[jIndex].second == L"CB_World")
			{
				m_vecVSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_World",
						vecVSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecVSConstantBufferInfo[jIndex].second == L"CB_WorldViewProjection")
			{
				m_vecVSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldViewProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_WorldViewProjection",
						vecVSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecVSConstantBufferInfo[jIndex].second == L"CB_WorldInvTransWorldViewProjection")
			{
				m_vecVSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldInvTransWorldViewProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_WorldInvTransWorldViewProjection",
						vecVSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecVSConstantBufferInfo[jIndex].second == L"CB_WorldViewOrthoProj")
			{
				m_vecVSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldViewOrthoProjConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_WorldViewOrthoProj",
						vecVSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecVSConstantBufferInfo[jIndex].second == L"CB_LightViewLightProjection")
			{
				m_vecVSConstantBuffers[jIndex] = CConstantBuffer::Create<CLightViewLightProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_LightViewLightProjection",
						vecVSConstantBufferInfo[jIndex].first
					);
			}
		}
	}

	// 픽셀 셰이더 상수 버퍼
	auto& vecPSConstantBufferInfo = spPixelShaderDesc->m_vecConstantBufferInfo;
	if (!vecPSConstantBufferInfo.empty())
	{
		m_vecPSConstantBuffers.reserve(vecPSConstantBufferInfo.size());
		m_vecPSConstantBuffers.resize(vecPSConstantBufferInfo.size());

		for (size_t jIndex = 0; jIndex < vecPSConstantBufferInfo.size(); ++jIndex)
		{
			if (vecPSConstantBufferInfo[jIndex].second == L"CB_WorldViewProjection")
			{
				m_vecPSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldViewProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_WorldViewProjection",
						vecPSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecPSConstantBufferInfo[jIndex].second == L"CB_WorldInvTransWorldViewProjection")
			{
				_spOwnerComponent->GetOwnerActor(),
				m_vecPSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldInvTransWorldViewProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_WorldInvTransWorldViewProjection",
						vecPSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecPSConstantBufferInfo[jIndex].second == L"CB_Size2D")
			{
				m_vecPSConstantBuffers[jIndex] = CConstantBuffer::Create<CSize2DConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_Size2D",
						vecPSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecPSConstantBufferInfo[jIndex].second == L"CB_BillboardProjectile")
			{
				m_vecPSConstantBuffers[jIndex] = CConstantBuffer::Create<CBillboardProjectileConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_BillboardProjectile",
						vecPSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecPSConstantBufferInfo[jIndex].second == L"CB_Ratio")
			{
				m_vecPSConstantBuffers[jIndex] = CConstantBuffer::Create<CRatioConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_Ratio",
						vecPSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecPSConstantBufferInfo[jIndex].second == L"CB_LightViewLightProjection")
			{
				m_vecPSConstantBuffers[jIndex] = CConstantBuffer::Create<CLightViewLightProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_LightViewLightProjection",
						vecPSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecPSConstantBufferInfo[jIndex].second == L"CB_Color")
			{
				m_vecPSConstantBuffers[jIndex] = CConstantBuffer::Create<CColorConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_Color",
						vecPSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecPSConstantBufferInfo[jIndex].second == L"CB_Lerp")
			{
				m_vecPSConstantBuffers[jIndex] = CConstantBuffer::Create<CLerpConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_Lerp",
						vecPSConstantBufferInfo[jIndex].first
					);
			}
		}
	}

	
	// 버텍스 셰이더 샘플러
	auto& vecVSSamplerInfo = spVertexShaderDesc->m_vecSamplerInfo;
	if (!vecVSSamplerInfo.empty())
	{
		m_spVSSampler = CSampler::Create(L"SS_FILTER_LINEAR_ADDRESS_WRAP", 0);
	}

	// 픽셀 셰이더 샘플러
	auto& vecPSSamplerInfo = spPixelShaderDesc->m_vecSamplerInfo;
	if (!vecPSSamplerInfo.empty())
	{
		m_spPSSampler = CSampler::Create(L"SS_FILTER_LINEAR_ADDRESS_WRAP", 0);
	}

	// 지오메트리 셰이더를 사용하지 않는 경우
	if (!spGeometryShaderDesc) { return S_OK; }

	// 지오메트리 셰이더 상수 버퍼
	auto& vecGSConstantBufferInfo = spGeometryShaderDesc->m_vecConstantBufferInfo;
	if (!vecGSConstantBufferInfo.empty())
	{
		m_vecGSConstantBuffers.reserve(vecGSConstantBufferInfo.size());
		m_vecGSConstantBuffers.resize(vecGSConstantBufferInfo.size());

		for (size_t jIndex = 0; jIndex < vecGSConstantBufferInfo.size(); ++jIndex)
		{
			if (vecGSConstantBufferInfo[jIndex].second == L"CB_WorldViewOrthoProj")
			{
				m_vecGSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldViewOrthoProjConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_WorldViewOrthoProj",
						vecGSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecGSConstantBufferInfo[jIndex].second == L"CB_ViewProjection")
			{
				m_vecGSConstantBuffers[jIndex] = CConstantBuffer::Create<CViewProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_ViewProjection",
						vecGSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecGSConstantBufferInfo[jIndex].second == L"CB_WorldViewProjection")
			{
				m_vecGSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldViewProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_WorldViewProjection",
						vecGSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecGSConstantBufferInfo[jIndex].second == L"CB_WorldInvTransWorldViewProjection")
			{
				m_vecGSConstantBuffers[jIndex] = CConstantBuffer::Create<CWorldInvTransWorldViewProjectionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_WorldInvTransWorldViewProjection",
						vecGSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecGSConstantBufferInfo[jIndex].second == L"CB_CameraPosition")
			{
				m_vecGSConstantBuffers[jIndex] = CConstantBuffer::Create<CCameraPositionConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_CameraPosition",
						vecGSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecGSConstantBufferInfo[jIndex].second == L"CB_ViewOrthoProj")
			{
				m_vecGSConstantBuffers[jIndex] = CConstantBuffer::Create<CViewOrthoProjConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_ViewOrthoProj",
						vecGSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecGSConstantBufferInfo[jIndex].second == L"CB_Size2D")
			{
				m_vecGSConstantBuffers[jIndex] = CConstantBuffer::Create<CSize2DConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_Size2D",
						vecGSConstantBufferInfo[jIndex].first
					);
			}

			else if (vecGSConstantBufferInfo[jIndex].second == L"CB_BillboardProjectile")
			{
				m_vecGSConstantBuffers[jIndex] = CConstantBuffer::Create<CBillboardProjectileConstantBuffer>
					(
						_spOwnerComponent->GetOwnerActor(),
						L"CB_BillboardProjectile",
						vecGSConstantBufferInfo[jIndex].first
					);
			}
		}
	}


	// 지오메트리 셰이더 샘플러
	auto& vecGSSamplerInfo = spGeometryShaderDesc->m_vecSamplerInfo;
	if (!vecGSSamplerInfo.empty())
	{
		m_spGSSampler = CSampler::Create(L"SS_FILTER_LINEAR_ADDRESS_WRAP", 0);
	}

	return S_OK;
}

int32 Engine::CPrimitiveShader::Tick()
{
	for (size_t iIndex = 0; iIndex < m_vecVSConstantBuffers.size(); ++iIndex)
	{
		m_vecVSConstantBuffers[iIndex]->TickConstantBuffer(static_cast<uint32>(iIndex));
	}

	for (size_t iIndex = 0; iIndex < m_vecGSConstantBuffers.size(); ++iIndex)
	{
		m_vecGSConstantBuffers[iIndex]->TickConstantBuffer(static_cast<uint32>(iIndex));
	}

	for (size_t iIndex = 0; iIndex < m_vecPSConstantBuffers.size(); ++iIndex)
	{
		m_vecPSConstantBuffers[iIndex]->TickConstantBuffer(static_cast<uint32>(iIndex));
	}

	return 0;
}

void Engine::CPrimitiveShader::Release()
{
	// 버텍스 셰이더
	m_spVertexShader->Release();
	m_spVertexShader = nullptr;

	// 버텍스 셰이더 텍스처
	for (auto& spTexture : m_vecVSMaterials)
	{
		if (!spTexture) { continue; }

		spTexture->Release();
		spTexture = nullptr;
	}
	m_vecVSMaterials.clear();

	// 버텍스 셰이더 상수 버퍼
	for (auto& spConstantBuffer : m_vecVSConstantBuffers)
	{
		spConstantBuffer->Release();
		spConstantBuffer = nullptr;
	}
	m_vecVSConstantBuffers.clear();

	// 버텍스 셰이더 샘플러
	if (m_spVSSampler)
	{
		m_spVSSampler->Release();
		m_spVSSampler = nullptr;
	}


	// 픽셀 셰이더
	m_spPixelShader->Release();
	m_spPixelShader = nullptr;
	
	// 픽셀 셰이더 텍스처
	for (auto& vecTextures : m_vecPSMaterials)
	{
		for (auto& spTexture : vecTextures)
		{
			if (!spTexture) { continue; }

			spTexture->Release();
			spTexture = nullptr;
		}
		vecTextures.clear();
	}
	m_vecPSMaterials.clear();

	// 픽셀 셰이더 상수 버퍼
	for (auto& spConstantBuffer : m_vecPSConstantBuffers)
	{
		spConstantBuffer->Release();
		spConstantBuffer = nullptr;
	}
	m_vecPSConstantBuffers.clear();

	// 픽셀 셰이더 샘플러
	if (m_spPSSampler)
	{
		m_spPSSampler->Release();
		m_spPSSampler = nullptr;
	}


	// 지오메트리 셰이더
	if (m_spGeometryShader)
	{
		m_spGeometryShader->Release();
		m_spGeometryShader = nullptr;
	}

	// 지오메트리 셰이더 텍스처
	for (auto& spTexture : m_vecGSMaterials)
	{
		if (!spTexture) { continue; }

		spTexture->Release();
		spTexture = nullptr;
	}
	m_vecGSMaterials.clear();

	// 지오메트리 셰이더 상수 버퍼
	for (auto& spConstantBuffer : m_vecGSConstantBuffers)
	{
		spConstantBuffer->Release();
		spConstantBuffer = nullptr;
	}
	m_vecGSConstantBuffers.clear();
	
	// 지오메트리 셰이더 샘플러
	if (m_spGSSampler)
	{
		m_spGSSampler->Release();
		m_spGSSampler = nullptr;
	}
}

void Engine::CPrimitiveShader::IASetInputLayout()
{
	m_spVertexShader->IASetInputLayout();
}

void Engine::CPrimitiveShader::CopyConstantBuffers()
{
	if (!m_vecVSConstantBuffers.empty())
	{
		for (size_t iIndex = 0; iIndex < m_vecVSConstantBuffers.size(); ++iIndex)
		{
			m_vecVSConstantBuffers[iIndex]->CopyConstantBuffer(0);
		}
	}
	
	if (!m_vecGSConstantBuffers.empty())
	{
		for (size_t iIndex = 0; iIndex < m_vecGSConstantBuffers.size(); ++iIndex)
		{
			m_vecGSConstantBuffers[iIndex]->CopyConstantBuffer(0);
		}
	}

	if (!m_vecPSConstantBuffers.empty())
	{
		for (const auto& spPSConstantBuffers : m_vecPSConstantBuffers)
		{
			spPSConstantBuffers->CopyConstantBuffer(0);
		}
	}
}

void Engine::CPrimitiveShader::VSSetShader()
{
	m_spVertexShader->VSSetShader();
}

void Engine::CPrimitiveShader::VSSetConstantBuffers()
{
	if (m_vecVSConstantBuffers.empty()) { return; }

	for (const auto& spConstantBuffer : m_vecVSConstantBuffers)
	{
		spConstantBuffer->VSSetConstantBuffers();
	}
}

void Engine::CPrimitiveShader::VSSetShaderResources()
{
	if (m_vecVSMaterials.empty()) { return; }

	for (const auto& spTexture : m_vecVSMaterials)
	{
		if (spTexture)
		{
			spTexture->VSSetShaderResources();
		}
	}
}

void Engine::CPrimitiveShader::VSSetSamplers()
{
	if (!m_spVSSampler) { return; }

	m_spVSSampler->VSSetSamplers();
}

void Engine::CPrimitiveShader::PSSetShader()
{
	m_spPixelShader->PSSetShader();
}

void Engine::CPrimitiveShader::PSSetConstantBuffers()
{
	if (m_vecPSConstantBuffers.empty()) { return; }

	for (const auto& spConstantBuffer : m_vecPSConstantBuffers)
	{
		spConstantBuffer->PSSetConstantBuffers();
	}
}

void Engine::CPrimitiveShader::PSSetShaderResources(uint32 _iIndex)
{
	if (m_vecPSMaterials.empty()) { return; }

	for (const auto& vecTextures : m_vecPSMaterials)
	{
		vecTextures[_iIndex]->PSSetShaderResources();
	}
}

void Engine::CPrimitiveShader::PSSetMultiShaderResources()
{
	m_vecPSMaterials[0][0]->PSSetShaderResources();
	m_vecPSMaterials[1][1]->PSSetShaderResources();
}

void Engine::CPrimitiveShader::PSSetSamplers()
{
	if (!m_spPSSampler) { return; }

	m_spPSSampler->PSSetSamplers();
}

void Engine::CPrimitiveShader::GSSetShader()
{
	m_spGeometryShader->GSSetShader();
}

void Engine::CPrimitiveShader::GSSetConstantBuffers()
{
	if (m_vecGSConstantBuffers.empty()) { return; }

	for (const auto& spConstantBuffer : m_vecGSConstantBuffers)
	{
		spConstantBuffer->GSSetConstantBuffers();
	}
}

void Engine::CPrimitiveShader::GSSetShaderResources()
{
	if (m_vecGSMaterials.empty()) { return; }

	for (const auto& spTexture : m_vecGSMaterials)
	{
		if (spTexture)
		{
			spTexture->GSSetShaderResources();
		}
	}
}

void Engine::CPrimitiveShader::GSSetSamplers()
{
	if (!m_spGSSampler) { return; }

	m_spGSSampler->GSSetSamplers();
}

void Engine::CPrimitiveShader::GSUnsetShader()
{
	m_spGeometryShader->GSUnsetShader();
}

void Engine::CPrimitiveShader::AddConstantBuffer(const shared_ptr<CConstantBuffer>& _spConstantBuffer)
{
	if (m_vecPSConstantBuffers.empty())
	{
		m_vecPSConstantBuffers.push_back(_spConstantBuffer);
		return;
	}

	for (auto& spConstantBuffer : m_vecPSConstantBuffers)
	{
		if (!spConstantBuffer)
		{
			spConstantBuffer = _spConstantBuffer;
			return;
		}
	}
}
