#include "pch.h"
#include "PrimitiveMeshData.h"

// primitive
#include "PrimitiveBuffer.h"
#include "PrimitiveShader.h"

// handler
#include "StateHandler.h"

std::shared_ptr<CPrimitiveMeshData> Engine::CPrimitiveMeshData::Create
(
	const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
	EPrimitiveType _ePrimitiveType,
	const std::vector<std::wstring>& _vecTextureNames,
	const std::wstring& _wstrVertexShaderDesc,
	const std::wstring& _wstrPixelShaderDesc,
	const std::wstring& _wstrGeometryShaderDesc
)
{
	const shared_ptr<CPrimitiveMeshData> spPrimitiveMeshData = make_shared<CPrimitiveMeshData>();
	ENSUREF(spPrimitiveMeshData->Initialize(_spOwnerComponent, _ePrimitiveType, _vecTextureNames, _wstrVertexShaderDesc, _wstrPixelShaderDesc, _wstrGeometryShaderDesc), L"Failed to initialize primitive mesh data.");
	return spPrimitiveMeshData;
}

HRESULT Engine::CPrimitiveMeshData::Initialize
(
	const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
	EPrimitiveType _ePrimitiveType,
	const std::vector<std::wstring>& _vecTextureNames,
	const std::wstring& _wstrVertexShaderDesc,
	const std::wstring& _wstrPixelShaderDesc,
	const std::wstring& _wstrGeometryShaderDesc
)
{
	m_wpOwnerComponent = _spOwnerComponent;
	m_ePrimitiveType = _ePrimitiveType;
	m_spPrimitiveBuffer = CPrimitiveBuffer::Create(_ePrimitiveType);
	m_spPrimitiveShader = CPrimitiveShader::Create(_spOwnerComponent, _ePrimitiveType, _vecTextureNames, _wstrVertexShaderDesc, _wstrPixelShaderDesc, _wstrGeometryShaderDesc);
	return S_OK;
}

int32 Engine::CPrimitiveMeshData::Tick()
{
	// 메시나 셰이더를 설정하지 않은 경우, 업데이트하지 않습니다.
	if (!m_spPrimitiveBuffer || !m_spPrimitiveShader) { return 0; }

	return m_spPrimitiveShader->Tick();
}

void Engine::CPrimitiveMeshData::Render(uint32 _iTextureIndex)
{
	// 메시나 셰이더를 설정하지 않은 경우, 렌더하지 않습니다.
	if (!m_spPrimitiveBuffer || !m_spPrimitiveShader) { return; }

	switch (m_ePrimitiveType)
	{
	case Engine::EPrimitiveType::POINT:
	{
		m_spPrimitiveBuffer->IASetVertexBuffer();
		m_spPrimitiveBuffer->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		m_spPrimitiveShader->IASetInputLayout();

		m_spPrimitiveShader->VSSetShader();
		m_spPrimitiveShader->GSSetShader();
		m_spPrimitiveShader->PSSetShader();

		m_spPrimitiveShader->CopyConstantBuffers();

		m_spPrimitiveShader->VSSetConstantBuffers();
		m_spPrimitiveShader->GSSetConstantBuffers();
		m_spPrimitiveShader->PSSetConstantBuffers();

		m_spPrimitiveShader->VSSetShaderResources();
		m_spPrimitiveShader->GSSetShaderResources();
		m_spPrimitiveShader->PSSetShaderResources(_iTextureIndex);

		m_spPrimitiveShader->VSSetSamplers();
		m_spPrimitiveShader->GSSetSamplers();
		m_spPrimitiveShader->PSSetSamplers();

		m_spPrimitiveBuffer->Draw();

		m_spPrimitiveShader->GSUnsetShader();
	}
	break;

	case Engine::EPrimitiveType::RECT:
	{
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

		m_spPrimitiveBuffer->DrawIndexed();
	}
	break;

	case Engine::EPrimitiveType::CUBE:
	{
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
		m_spPrimitiveShader->PSSetMultiShaderResources();

		m_spPrimitiveShader->VSSetSamplers();
		m_spPrimitiveShader->PSSetSamplers();

		m_spPrimitiveBuffer->DrawIndexed();
	}
	break;

	default:
	break;
	}
}

void Engine::CPrimitiveMeshData::Release()
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

void Engine::CPrimitiveMeshData::SetConstantBuffer(const shared_ptr<CConstantBuffer>& _spConstantBuffer)
{
	m_spPrimitiveShader->AddConstantBuffer(_spConstantBuffer);
}
