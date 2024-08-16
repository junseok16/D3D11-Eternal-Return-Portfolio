#include "pch.h"
#include "EffectParticleData.h"

#include "PrimitiveBuffer.h"
#include "PrimitiveShader.h"

std::shared_ptr<CEffectParticleData> Engine::CEffectParticleData::Create
(
	const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
	int32 _iNumInstances,
	const std::vector<std::wstring>& _vecTextureNames,
	const std::wstring& _wstrEffectParticleDesc,
	const std::wstring& _wstrVertexShaderDesc,
	const std::wstring& _wstrPixelShaderDesc,
	const std::wstring& _wstrGeometryShaderDesc
)
{
	const shared_ptr<CEffectParticleData> spEffectParticleData = make_shared<CEffectParticleData>();
	ENSUREF(spEffectParticleData->Initialize
	(
		_spOwnerComponent,
		_iNumInstances,
		_vecTextureNames,
		_wstrEffectParticleDesc,
		_wstrVertexShaderDesc,
		_wstrPixelShaderDesc,
		_wstrGeometryShaderDesc
	), L"Failed to initialize effect particle data.");

	return spEffectParticleData;
}

HRESULT Engine::CEffectParticleData::Initialize
(
	const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
	int32 _iNumInstances,
	const std::vector<std::wstring>& _vecTextureNames,
	const std::wstring& _wstrEffectParticleDesc,
	const std::wstring& _wstrVertexShaderDesc,
	const std::wstring& _wstrPixelShaderDesc,
	const std::wstring& _wstrGeometryShaderDesc
)
{
	m_wpOwnerComponent = _spOwnerComponent;
	m_wstrEffectParticleDesc = _wstrEffectParticleDesc;
	m_wstrVertexShaderDesc = _wstrVertexShaderDesc;
	m_wstrPixelShaderDesc = _wstrPixelShaderDesc;
	m_wstrGeomteryShaderDesc = _wstrGeometryShaderDesc;
	
	m_spPrimitiveBuffer = CPrimitiveBuffer::Create(EPrimitiveType::INSTANCE_POINT, _iNumInstances);
	m_spPrimitiveShader = CPrimitiveShader::Create
	(
		_spOwnerComponent,
		EPrimitiveType::INSTANCE_POINT,
		_vecTextureNames,
		_wstrVertexShaderDesc,
		_wstrPixelShaderDesc,
		_wstrGeometryShaderDesc
	);
	return S_OK;
}

int32 Engine::CEffectParticleData::Tick(float _fDeltaSeconds)
{
	// 메시나 셰이더를 설정하지 않은 경우, 업데이트하지 않습니다.
	if (!m_spPrimitiveBuffer || !m_spPrimitiveShader) { return 0; }

	if (m_eEffectParticleDataState == EEffectParticleDataState::OFF) { return 0; }

	switch ((EEffectShapeType)m_tParticleTransformProperty.m_iEffectShapeType)
	{
	case EEffectShapeType::FALL_DOWN:
		m_spPrimitiveBuffer->Tick(EEffectShapeType::FALL_DOWN, _fDeltaSeconds);
		break;

	case EEffectShapeType::SPREAD:
		m_spPrimitiveBuffer->Tick(EEffectShapeType::SPREAD, _fDeltaSeconds);
		break;

	case EEffectShapeType::SPOT:
		m_spPrimitiveBuffer->Tick(EEffectShapeType::SPOT, _fDeltaSeconds);
		break;

	default:
		CHECKF(false, L"Effect shape type is not designated.")
		break;
	}

	return m_spPrimitiveShader->Tick();
}

void Engine::CEffectParticleData::Render()
{
	// 메시나 셰이더를 설정하지 않은 경우, 렌더하지 않습니다.
	if (!m_spPrimitiveBuffer || !m_spPrimitiveShader) { return; }

	if (m_eEffectParticleDataState == EEffectParticleDataState::OFF) { return; }

	m_spPrimitiveBuffer->IASetVertexBuffer();
	m_spPrimitiveBuffer->IASetIndexBuffer();
	m_spPrimitiveBuffer->IASetPrimitiveTopology();
	m_spPrimitiveShader->IASetInputLayout();

	m_spPrimitiveShader->VSSetShader();
	m_spPrimitiveShader->PSSetShader();

	m_spPrimitiveShader->CopyConstantBuffers();

	m_spPrimitiveShader->VSSetConstantBuffers();
	m_spPrimitiveShader->PSSetConstantBuffers();

	m_spPrimitiveShader->VSSetShaderResources();
	m_spPrimitiveShader->PSSetShaderResources();

	m_spPrimitiveShader->VSSetSamplers();
	m_spPrimitiveShader->PSSetSamplers();

	m_spPrimitiveBuffer->DrawIndexedInstanced();
}

void Engine::CEffectParticleData::Release()
{
	if (m_spPrimitiveBuffer)
	{
		m_spPrimitiveBuffer->Release();
		m_spPrimitiveBuffer = nullptr;
	}

	if (m_spPrimitiveShader)
	{
		m_spPrimitiveShader->Release();
		m_spPrimitiveShader = nullptr;
	}
}

void Engine::CEffectParticleData::Clear()
{
	if (m_spPrimitiveBuffer)
	{
		m_spPrimitiveBuffer->Release();
		m_spPrimitiveBuffer = nullptr;
	}

	if (m_spPrimitiveShader)
	{
		m_spPrimitiveShader->Release();
		m_spPrimitiveShader = nullptr;
	}
}
