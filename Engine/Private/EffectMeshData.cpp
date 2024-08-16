#include "pch.h"
#include "EffectMeshData.h"

// mesh
#include "MeshBuffer.h"
#include "MeshShader.h"

// handler
#include "EffectHandler.h"

#include "SceneComponent.h"

std::shared_ptr<CEffectMeshData> Engine::CEffectMeshData::Create(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrEffectModelDesc, const std::wstring& _wstrVertexShaderDesc, const std::wstring& _wstrPixelShaderDesc)
{
	const shared_ptr<CEffectMeshData> spEffectMeshData = make_shared<CEffectMeshData>();
	ENSUREF(spEffectMeshData->Initialize(_spOwnerComponent, _wstrEffectModelDesc, _wstrVertexShaderDesc, _wstrPixelShaderDesc), L"Failed to initialize effect mesh data.");
	return spEffectMeshData;
}

HRESULT Engine::CEffectMeshData::Initialize(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrEffectModelDesc, const std::wstring& _wstrVertexShaderDesc, const std::wstring& _wstrPixelShaderDesc)
{
	m_wpOwnerComponent = _spOwnerComponent;
	if (_wstrEffectModelDesc.empty()) { return S_OK; }

	m_wstrEffectModelDesc = _wstrEffectModelDesc;
	m_wstrVertexShaderDesc = _wstrVertexShaderDesc;
	m_wstrPixelShaderDesc = _wstrPixelShaderDesc;

	m_iNumMeshes = CEffectHandler::GetInstance()->FindModelDesc(_wstrEffectModelDesc)->m_iNumMeshes;
	m_spMeshBuffer = CMeshBuffer::Create(_wstrEffectModelDesc);
	m_spMeshShader = CMeshShader::Create(_spOwnerComponent, nullptr, shared_from_this(), _wstrEffectModelDesc, _wstrVertexShaderDesc, _wstrPixelShaderDesc);
	return S_OK;
}

int32 Engine::CEffectMeshData::Tick(float _fDeltaSeconds)
{
	// 메시나 셰이더를 설정하지 않은 경우, 업데이트하지 않습니다.
	if (!m_spMeshBuffer || !m_spMeshShader) { return 0; }

	RecalcEffectMeshData(_fDeltaSeconds);

	if (m_eEffectMeshDataState == EEffectMeshDataState::OFF) { return 0; }

	return m_spMeshShader->Tick();
}

void Engine::CEffectMeshData::Render()
{
	if (m_eEffectMeshDataState == EEffectMeshDataState::OFF) { return; }

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

void Engine::CEffectMeshData::Release()
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
}

void Engine::CEffectMeshData::Clear()
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
}

HRESULT Engine::CEffectMeshData::ChangeEffectModelDesc(const std::wstring& _wstrEffectModelDesc)
{
	if (_wstrEffectModelDesc.empty()) { return E_FAIL; }

	m_wstrEffectModelDesc = _wstrEffectModelDesc;
	m_iNumMeshes = CEffectHandler::GetInstance()->FindModelDesc(_wstrEffectModelDesc)->m_iNumMeshes;

	if (m_spMeshBuffer)
	{
		m_spMeshBuffer->Release();
		m_spMeshBuffer = nullptr;
	}
	m_spMeshBuffer = CMeshBuffer::Create(_wstrEffectModelDesc);
	return S_OK;
}

HRESULT Engine::CEffectMeshData::ChangeShaders(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrVertexShaderDesc, const std::wstring& _wstrPixelShaderDesc)
{
	if (_wstrVertexShaderDesc.empty() || _wstrPixelShaderDesc.empty()) { return E_FAIL; }

	m_wstrVertexShaderDesc = _wstrVertexShaderDesc;
	m_wstrPixelShaderDesc = _wstrPixelShaderDesc;

	if (m_spMeshShader)
	{
		m_spMeshShader->Release();
		m_spMeshShader = nullptr;
	}
	m_spMeshShader = CMeshShader::Create(_spOwnerComponent, nullptr, shared_from_this(), m_wstrEffectModelDesc, _wstrVertexShaderDesc, _wstrPixelShaderDesc);
	return S_OK;
}

void Engine::CEffectMeshData::ModifyPixelShaderTexture(int32 _iMeshIndex, int32 _iTextureIndex, const std::wstring& _wstrTextureName)
{
	switch (_iTextureIndex)
	{
	case 0:		m_tMaskProperty.m_wstrMaskTextureName = _wstrTextureName;	break;// 마스크
	case 1:		m_tNoiseProperty.m_wstrNoiseTextureName = _wstrTextureName;	break;// 노이즈
	default:	CHECKF(false, L"Texture index is not designated.");			break;
	}
	
	m_spMeshShader->ModifyPixelShaderTexture(_iMeshIndex, _iTextureIndex, _wstrTextureName);
}

void Engine::CEffectMeshData::RecalcEffectMeshData(float _fDeltaSeconds)
{
	switch (m_eEffectMeshDataState)
	{
	case Engine::EEffectMeshDataState::ON:
	case Engine::EEffectMeshDataState::RESET:
	case Engine::EEffectMeshDataState::OFF:
	{
		m_fCurRatio = 0.0f;
		m_fCurPlaySeconds = 0.0f;
		m_vCurColor = m_tColorProperty.m_vStartColor;
		m_vCurEffectUV = m_tUVProperty.m_vEffectStartUV;
		m_vCurMaskUV = { 1.0f, 1.0f };
		m_vCurNoiseUV = { 1.0f, 1.0f };
	}
	break;

	case Engine::EEffectMeshDataState::PLAY:
	{
		m_fCurPlaySeconds += _fDeltaSeconds;

		if (m_tPlayProperty.m_fFinishPlaySeconds <= m_fCurPlaySeconds)
		{
			m_fCurRatio = 0.0f;
			m_iCurMaskIndex = 0;
			m_fCurPlaySeconds = 0.0f;
			
			if (m_tPlayProperty.m_bLoop)
			{
				m_eEffectMeshDataState = EEffectMeshDataState::PLAY;
			}
			else
			{
				m_eEffectMeshDataState = EEffectMeshDataState::OFF;
			}
			break;
		}

		else if (m_tPlayProperty.m_fStartPlaySeconds <= m_fCurPlaySeconds)
		{
			float m_fTotalPlaySeconds = m_tPlayProperty.m_fFinishPlaySeconds - m_tPlayProperty.m_fStartPlaySeconds;
			m_fCurRatio = (m_fCurPlaySeconds - m_tPlayProperty.m_fStartPlaySeconds) / m_fTotalPlaySeconds;

			int32 iSumMasks = m_tMaskProperty.m_iMaskRowColume[0] * m_tMaskProperty.m_iMaskRowColume[1];
			m_iCurMaskIndex = static_cast<int32>(iSumMasks * m_fCurRatio);
			
			// 이펙트 색상을 선형 보간합니다.
			m_vCurColor = Vector4::Lerp(m_tColorProperty.m_vStartColor, m_tColorProperty.m_vFinishColor, m_fCurRatio);
			
			// 이펙트 UV를 변형합니다.
			if (m_tUVProperty.m_bUseEffectUV)
			{
				m_vCurEffectUV = Vector2::Lerp(m_tUVProperty.m_vEffectStartUV, m_tUVProperty.m_vEffectFinishUV, m_fCurRatio);
			}

			// 마스크 UV를 변형합니다.
			if (m_tMaskProperty.m_bUseMask)
			{
				m_vCurMaskUV += m_tMaskProperty.m_vMaskUVSpeed;

				if (m_tMaskProperty.m_vMaskMaxUV.x <= m_vCurMaskUV.x) { m_vCurMaskUV.x = 0.0f; }
				if (m_tMaskProperty.m_vMaskMaxUV.y <= m_vCurMaskUV.y) { m_vCurMaskUV.y = 0.0f; }
			}

			// 노이즈 UV를 변형합니다.
			if (m_tNoiseProperty.m_bUseNoise)
			{
				m_vCurNoiseUV += m_tNoiseProperty.m_vNoiseUVSpeed;

				if (m_tNoiseProperty.m_vNoiseMaxUV.x <= m_vCurNoiseUV.x) { m_vCurNoiseUV.x = 0.0f; }
				if (m_tNoiseProperty.m_vNoiseMaxUV.y <= m_vCurNoiseUV.y) { m_vCurNoiseUV.y = 0.0f; }
			}

			// 이펙트 트랜스폼을 선형 보간합니다.
			m_vCurScale = Vector3::Lerp(m_tTransformProperty.m_vStartScale, m_tTransformProperty.m_vFinishScale, m_fCurRatio);
			m_vCurRotate = Vector3::Lerp(m_tTransformProperty.m_vStartRotate, m_tTransformProperty.m_vFinishRotate, m_fCurRatio);
			m_vCurTranslate = Vector3::Lerp(m_tTransformProperty.m_vStartTranslate, m_tTransformProperty.m_vFinishTranslate, m_fCurRatio);
			
			m_matEffect = Matrix::Identity;
			m_matEffect *= Matrix::CreateScale(m_vCurScale);
			m_matEffect *= Matrix::CreateRotationX(XMConvertToRadians(m_vCurRotate.x));
			m_matEffect *= Matrix::CreateRotationY(XMConvertToRadians(m_vCurRotate.y));
			m_matEffect *= Matrix::CreateRotationZ(XMConvertToRadians(m_vCurRotate.z));
			m_matEffect *= Matrix::CreateTranslation(m_vCurTranslate);

			m_matEffect *= m_wpOwnerComponent.lock()->GetComponentWorldMatrix();
		}

		else
		{
			m_fCurRatio = 0.0f;
			m_vCurColor = m_tColorProperty.m_vStartColor;
			m_vCurEffectUV = m_tUVProperty.m_vEffectStartUV;
			m_vCurMaskUV = { 1.0f, 1.0f };
			m_vCurNoiseUV = { 1.0f, 1.0f };
		}
	}
	break;

	case Engine::EEffectMeshDataState::STOP:
		break;

	default:
		break;
	}
}
