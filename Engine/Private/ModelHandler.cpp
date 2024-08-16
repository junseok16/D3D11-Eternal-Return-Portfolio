#include "pch.h"
#include "ModelHandler.h"

#include "DeviceManager.h"
#include "ModelLoader.h"

#include "MeshBone.h"
#include "Bone.h"
#include "Animation.h"

IMPLEMENT_SINGLETON(CModelHandler);

HRESULT Engine::CModelHandler::Initialize(const std::shared_ptr<CDeviceManager>& _spDeviceManager)
{
	m_wpDeviceManager = _spDeviceManager;
	m_spModelLoader = CModelLoader::Create();
	return S_OK;
}

void Engine::CModelHandler::Release()
{
	for (auto& pair : m_umapVertexBuffers) { pair.second = nullptr; }
	m_umapVertexBuffers.clear();

	for (auto& pair : m_umapIndexBuffers) { pair.second = nullptr; }
	m_umapIndexBuffers.clear();

	for (auto& pair : m_umapShaderResourceViews) { pair.second = nullptr; }
	m_umapShaderResourceViews.clear();

	for (auto& pair : m_umapBones)
	{
		for (auto& spBone : pair.second)
		{
			spBone->Release();
			spBone = nullptr;
		}
		pair.second.clear();
	}
	m_umapBones.clear();

	for (auto& Outerpair : m_umapAnimations)
	{
		for (auto& InnerPair : Outerpair.second)
		{
			InnerPair.second->Release();
			InnerPair.second = nullptr;
		}
		Outerpair.second.clear();
	}
	m_umapAnimations.clear();

	m_spModelLoader->Release();
	m_spModelLoader = nullptr;

	m_spInstance.reset();
}

HRESULT Engine::CModelHandler::AddVertexBuffer(const std::wstring& _wstrVertexBufferName, const ComPtr<ID3D11Buffer>& _spVertexBuffer)
{
	if (m_umapVertexBuffers.find(_wstrVertexBufferName) != m_umapVertexBuffers.end()) { return E_FAIL; }

	m_umapVertexBuffers.insert({ _wstrVertexBufferName, _spVertexBuffer });
	return S_OK;
}

HRESULT Engine::CModelHandler::AddIndexBuffer(const std::wstring& _wstrIndexBufferName, const ComPtr<ID3D11Buffer>& _spIndexBuffer)
{
	if (m_umapIndexBuffers.find(_wstrIndexBufferName) != m_umapIndexBuffers.end()) { return E_FAIL; }

	m_umapIndexBuffers.insert({ _wstrIndexBufferName, _spIndexBuffer });
	return S_OK;
}

HRESULT Engine::CModelHandler::AddShaderResourceView(const std::wstring& _wstrShaderResourceViewName, const ComPtr<ID3D11ShaderResourceView>& _cpShaderResouceView)
{
	if (m_umapShaderResourceViews.find(_wstrShaderResourceViewName) != m_umapShaderResourceViews.end()) { return E_FAIL; }

	m_umapShaderResourceViews.insert({ _wstrShaderResourceViewName, _cpShaderResouceView });
	return S_OK;
}

HRESULT Engine::CModelHandler::AddBoneOffset(const std::wstring& _wstrMeshName, const shared_ptr<CBoneOffset>& _spBoneOffset)
{
	if (m_umapBoneOffsets.find(_wstrMeshName) != m_umapBoneOffsets.end()) { return E_FAIL; }

	m_umapBoneOffsets.insert({ _wstrMeshName, _spBoneOffset });
	return S_OK;
}

HRESULT Engine::CModelHandler::AddBone(const std::wstring& _wstrBoneName, const std::vector<shared_ptr<CBone>>& _vecBones)
{
	if (m_umapBones.find(_wstrBoneName) != m_umapBones.end()) { return E_FAIL; }

	m_umapBones.insert({ _wstrBoneName, _vecBones });
	return S_OK;
}

HRESULT Engine::CModelHandler::AddAnimation(const std::wstring& _wstrAnimationName, const std::unordered_map<std::string, std::shared_ptr<CAnimation>>& _umapAnimations)
{
	if (m_umapAnimations.find(_wstrAnimationName) != m_umapAnimations.end()) { return E_FAIL; }

	m_umapAnimations.insert({ _wstrAnimationName, _umapAnimations });
	return S_OK;
}

HRESULT Engine::CModelHandler::AddModelDesc(const std::wstring& _wstrModelDescName, const shared_ptr<FModelDesc>& _spModelDesc)
{
	if (m_umapModelDescs.find(_wstrModelDescName) != m_umapModelDescs.end()) { return E_FAIL; }

	m_umapModelDescs.insert({ _wstrModelDescName, _spModelDesc });
	return S_OK;
}

ComPtr<ID3D11Buffer> Engine::CModelHandler::FindVertexBuffer(const std::wstring& _wstrVertexBufferName)
{
	if (m_umapVertexBuffers.find(_wstrVertexBufferName) == m_umapVertexBuffers.end()) { return nullptr; }

	return m_umapVertexBuffers[_wstrVertexBufferName];
}

ComPtr<ID3D11Buffer> Engine::CModelHandler::FindIndexBuffer(const std::wstring& _wstrIndexBufferName)
{
	if (m_umapIndexBuffers.find(_wstrIndexBufferName) == m_umapIndexBuffers.end()) { return nullptr; }

	return m_umapIndexBuffers[_wstrIndexBufferName];
}

std::shared_ptr<CBoneOffset> Engine::CModelHandler::FindBoneOffset(const std::wstring& _wstrMeshName)
{
	if (m_umapBoneOffsets.find(_wstrMeshName) == m_umapBoneOffsets.end()) { return nullptr; }

	return m_umapBoneOffsets[_wstrMeshName];
}

ComPtr<ID3D11ShaderResourceView> Engine::CModelHandler::FindShaderResourceView(const std::wstring& _wstrShaderResourceViewName)
{
	if (m_umapShaderResourceViews.find(_wstrShaderResourceViewName) == m_umapShaderResourceViews.end()) { return nullptr; }

	return m_umapShaderResourceViews[_wstrShaderResourceViewName];
}

std::vector<std::shared_ptr<CBone>> Engine::CModelHandler::CloneBone(const std::wstring& _wstrBoneName, const std::shared_ptr<CMeshBone> _spMeshBone)
{
	const std::vector<std::shared_ptr<CBone>>& vecTempBones = m_umapBones[_wstrBoneName];
	std::vector<std::shared_ptr<CBone>> vecBones(vecTempBones.size(), nullptr);

	// 잘 복사되는지 검증해야 합니다.
	for (size_t iIndex = 0; iIndex < vecTempBones.size(); ++iIndex)
	{
		const shared_ptr<CBone>& spTempBone = vecTempBones[iIndex];
		vecBones[iIndex] = make_shared<CBone>(*spTempBone);
	}
	return vecBones;
}

std::unordered_map<std::string, std::shared_ptr<CAnimation>> Engine::CModelHandler::CloneAnimation(const std::wstring& _wstrAnimationName, const std::shared_ptr<CMeshBone> _spMeshBone)
{
	const std::unordered_map<std::string, std::shared_ptr<CAnimation>>& umapTempAnimations = m_umapAnimations[_wstrAnimationName];
	std::unordered_map<std::string, std::shared_ptr<CAnimation>> umapAnimations;

	for (const auto& pair : umapTempAnimations)
	{
		const shared_ptr<CAnimation>& spTempAnimation = pair.second;
		umapAnimations.insert({ pair.first, make_shared<CAnimation>(*spTempAnimation) });
		umapAnimations[pair.first]->SetMeshBone(_spMeshBone);
	}
	return umapAnimations;

	/*
	// 잘 복사되는지 검증해야 합니다.
	for (size_t iIndex = 0; iIndex < umapTempAnimations.size(); ++iIndex)
	{
		const shared_ptr<CAnimation>& spTempAnimation = vecTempAnimations[iIndex];
		vecAnimations[iIndex] = make_shared<CAnimation>(*spTempAnimation);
		vecAnimations[iIndex]->SetMeshBone(_spMeshBone);
	}
	return vecAnimations;
	*/
}

int32 Engine::CModelHandler::GetNumVertice(EModelType _eModelType, const std::wstring& _wstrVertexBufferName) const
{
	return m_spModelLoader->GetNumVertices(_eModelType, _wstrVertexBufferName);
}

int32 Engine::CModelHandler::GetNumIndices(const std::wstring& _wstrIndexBufferName) const
{
	return m_spModelLoader->GetNumIndices(_wstrIndexBufferName);
}

Vector3 Engine::CModelHandler::GetAverageWorldPosition(EModelType _eModelType, const std::wstring& _wstrVertexBufferName) const
{
	return m_spModelLoader->GetAverageWorldPosition(_eModelType, _wstrVertexBufferName);
}

void Engine::CModelHandler::IASetVertexBuffers(UINT _iStartSlot, UINT _iNumBuffers, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetVertexBuffers(_iStartSlot, _iNumBuffers, _ppVertexBuffers, _pStrides, _pOffsets);
}

void Engine::CModelHandler::IASetIndexBuffer(ID3D11Buffer* _pIndexBuffer, DXGI_FORMAT _tFormat, UINT _iOffset)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetIndexBuffer(_pIndexBuffer, _tFormat, _iOffset);
}

void Engine::CModelHandler::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _tPrimitiveTopology)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->IASetPrimitiveTopology(_tPrimitiveTopology);
}

void Engine::CModelHandler::DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, UINT _iBaseVertexLocation)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->DrawIndexed(_iIndexCount, _iStartIndexLocation, _iBaseVertexLocation);
}

void Engine::CModelHandler::VSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->VSSetShaderResources(_iStartSlot, _iNumViews, _ppShaderResourceViews);
}

void Engine::CModelHandler::PSSetShaderResources(UINT _iStartSlot, UINT _iNumViews, ID3D11ShaderResourceView* const* _ppShaderResourceViews)
{
	m_wpDeviceManager.lock()->GetDeviceContext()->PSSetShaderResources(_iStartSlot, _iNumViews, _ppShaderResourceViews);
}

int32 Engine::CModelHandler::FindBoneIndex(const std::wstring& _wstrModelName, const std::string& _strBoneName)
{
	auto& vecBones = m_umapBones[_wstrModelName];

	size_t iIndex = 0;
	for (iIndex = 0; iIndex < vecBones.size(); ++iIndex)
	{
		if (vecBones[iIndex]->GetBoneName() == _strBoneName)
		{
			return static_cast<int32>(iIndex);
		}
	}

	return -1;
}

const std::unordered_map<std::string, std::shared_ptr<CAnimation>>& Engine::CModelHandler::FindAnimations(const std::wstring& _wstrModelName)
{
	return m_umapAnimations[_wstrModelName];
}

std::shared_ptr<FModelDesc> Engine::CModelHandler::FindModelDesc(const std::wstring& _wstrModelDescName)
{
	if (m_umapModelDescs.find(_wstrModelDescName) == m_umapModelDescs.end()) { return nullptr; }

	return m_umapModelDescs[_wstrModelDescName];
}
