#include "pch.h"
#include "EffectLoader.h"

#include "DeviceManager.h"
#include "EffectHandler.h"

std::shared_ptr<CEffectLoader> Engine::CEffectLoader::Create()
{
	const std::shared_ptr<CEffectLoader> spLoader = make_shared<CEffectLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create effect loader.");
	return spLoader;
}

HRESULT Engine::CEffectLoader::Initialize()
{
	m_wpEffectHandler = CEffectHandler::GetInstance();
	m_wpDeviceManager = CEffectHandler::GetInstance()->GetDeviceManager();

	// �ܺο��� ����Ʈ �޽ø� �ҷ��ɴϴ�.
	LoadEffectMeshFromFile();

	// �� ��ü�� �����մϴ�.
	CreateVertexBuffer();
	CreateIndexBuffer();

	// �ܺο��� ����Ʈ �ؽ�ó�� �ҷ�����, �� ��ü�� �����մϴ�.
	CreateEffectShaderResourceViewFromFile();

	LoadEffectMeshDataFromFile();
	return S_OK;
}

void Engine::CEffectLoader::Release()
{
	for (auto& pair : m_umapEffectMeshVertices)
	{
		pair.second.clear();
	}
	m_umapEffectMeshVertices.clear();

	for (auto& pair : m_umapEffectMeshIndices)
	{
		pair.second.clear();
	}
	m_umapEffectMeshIndices.clear();
}

HRESULT Engine::CEffectLoader::CreateVertexBuffer()
{
	// ����Ʈ �𵨿��� ���ؽ� ���۸� �����մϴ�.
	for (const auto& pair : m_umapEffectMeshVertices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tVertexSubResourceData;
		ZeroMemory(&tVertexSubResourceData, sizeof(tVertexSubResourceData));
		tVertexSubResourceData.pSysMem = pair.second.data();
		tVertexSubResourceData.SysMemPitch = 0;
		tVertexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tVertexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpEffectHandler.lock()->AddVertexBuffer(pair.first, cpBuffer);
	}

	for (const auto& pair : m_umapEffectPrimitiveVertices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tVertexSubResourceData;
		ZeroMemory(&tVertexSubResourceData, sizeof(tVertexSubResourceData));
		tVertexSubResourceData.pSysMem = pair.second.data();
		tVertexSubResourceData.SysMemPitch = 0;
		tVertexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tVertexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpEffectHandler.lock()->AddVertexBuffer(pair.first, cpBuffer);
	}

	return S_OK;
}

HRESULT Engine::CEffectLoader::CreateIndexBuffer()
{
	for (const auto& pair : m_umapEffectMeshIndices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tIndexSubResourceData;
		ZeroMemory(&tIndexSubResourceData, sizeof(tIndexSubResourceData));
		tIndexSubResourceData.pSysMem = pair.second.data();
		tIndexSubResourceData.SysMemPitch = 0;
		tIndexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tIndexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpEffectHandler.lock()->AddIndexBuffer(pair.first, cpBuffer);
	}

	for (const auto& pair : m_umapEffectPrimitiveIndices)
	{
		D3D11_BUFFER_DESC tBufferDesc;
		ZeroMemory(&tBufferDesc, sizeof(tBufferDesc));
		tBufferDesc.ByteWidth = static_cast<UINT>(sizeof(pair.second[0]) * pair.second.size());
		tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		tBufferDesc.CPUAccessFlags = 0;
		tBufferDesc.StructureByteStride = sizeof(pair.second[0]);

		D3D11_SUBRESOURCE_DATA tIndexSubResourceData;
		ZeroMemory(&tIndexSubResourceData, sizeof(tIndexSubResourceData));
		tIndexSubResourceData.pSysMem = pair.second.data();
		tIndexSubResourceData.SysMemPitch = 0;
		tIndexSubResourceData.SysMemSlicePitch = 0;

		ComPtr<ID3D11Buffer> cpBuffer = nullptr;
		ENSURE(m_wpDeviceManager.lock()->GetDevice()->CreateBuffer(&tBufferDesc, &tIndexSubResourceData, cpBuffer.GetAddressOf()));
		m_wpEffectHandler.lock()->AddIndexBuffer(pair.first, cpBuffer);
	}

	return S_OK;
}

HRESULT Engine::CEffectLoader::CreateEffectShaderResourceViewFromFile()
{
	for (const filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrEffectViewFilePath))
	{
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = nullptr;
		wstring wstrTextureFileExtenstion = fsEntry.path().extension().generic_wstring();
		if (wstrTextureFileExtenstion == L".dds" || wstrTextureFileExtenstion == L".DDS")
		{
			// dds Ȯ����
			if (FAILED(CreateDDSTextureFromFile(m_wpDeviceManager.lock()->GetDevice().Get(), fsEntry.path().c_str(), nullptr, cpShaderResourceView.GetAddressOf()))) { return E_FAIL; }
		}
		else if (wstrTextureFileExtenstion == L".png" || wstrTextureFileExtenstion == L".PNG")
		{
			// jpg, png Ȯ����
			if (FAILED(CreateWICTextureFromFile(m_wpDeviceManager.lock()->GetDevice().Get(), fsEntry.path().c_str(), nullptr, cpShaderResourceView.GetAddressOf()))) { return E_FAIL; }
		}
		else
		{
			continue;
		}

		wstring wstrTextureFileName = fsEntry.path().stem().generic_wstring();

		if (fsEntry.path().parent_path().stem() == L"Mask")
		{
			m_wpEffectHandler.lock()->AddMaskShaderResourceView(wstrTextureFileName, cpShaderResourceView.Get());
		}
		else if (fsEntry.path().parent_path().stem() == L"Noise")
		{
			m_wpEffectHandler.lock()->AddNoiseShaderResourceView(wstrTextureFileName, cpShaderResourceView.Get());
		}
	}
	return S_OK;
}

int32 Engine::CEffectLoader::GetNumVertices(EModelType _eModelType, const std::wstring& _wstrVertexBufferName)
{
	switch (_eModelType)
	{
	case Engine::EModelType::EFFECT:
		return static_cast<int32>(m_umapEffectMeshVertices[_wstrVertexBufferName].size());

	default:
		CHECKF(false, L"Model type should be the effect.")
		break;
	}
	return -1;
}

int32 Engine::CEffectLoader::GetNumIndices(const std::wstring& _wstrIndexBufferName)
{
	return static_cast<int32>(m_umapEffectMeshIndices[_wstrIndexBufferName].size());
}

HRESULT Engine::CEffectLoader::LoadEffectMeshFromFile()
{
	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_strEffectModelFilePath))
	{
		// ������ �ƴ� ���
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// dat ������ �ƴ� ���
		if (fsEntry.path().extension().generic_string() != ".dat" && fsEntry.path().extension().generic_string() != ".DAT") { continue; }

		std::ifstream inFile;
		inFile.open(fsEntry.path().c_str(), ios_base::in | ios_base::binary);

		// ������ ������ ���� ���
		if (!inFile.is_open()) { return E_FAIL; }

		// �� Ÿ���� �н��ϴ�.
		int8 iModelType = 0;
		inFile.read((char*)&iModelType, sizeof(int8));

		shared_ptr<FModelDesc> spModelDesc = make_shared<FModelDesc>();
		spModelDesc->m_eModelType = EModelType::EFFECT;

		// ����Ʈ ���� ����ƽ �𵨰� �ε� �Լ��� �����մϴ�.
		LoadEffectMeshes(inFile, spModelDesc, fsEntry);

		m_wpEffectHandler.lock()->AddModelDesc(spModelDesc->m_wstrModelName, spModelDesc);

		inFile.close();
	}
	return S_OK;
}

HRESULT Engine::CEffectLoader::LoadEffectMeshes(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry)
{
	// dat ������ �̸��� �����մϴ�.
	_spModelDesc->m_wstrModelName = _fsEntry.path().stem().generic_wstring();

	// �޽��� ������ �н��ϴ�.
	uint32 iNumMeshes = 0;
	_inFile.read((char*)&iNumMeshes, sizeof(uint32));
	_spModelDesc->m_iNumMeshes = iNumMeshes;

	_spModelDesc->m_vecNumIndices.reserve(iNumMeshes);
	_spModelDesc->m_vecNumVertices.reserve(iNumMeshes);
	_spModelDesc->m_vecMaterialIndices.reserve(iNumMeshes);

	for (uint64 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
	{
		// �޽��� �̸��� ���մϴ�.
		wstring wstrFileName = _fsEntry.path().stem().generic_wstring() + to_wstring(iIndex);

		// �޽��� �̸��� �н��ϴ�.
		uint32 iMeshNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iMeshNameLength), sizeof(uint32));

		string strMeshName;
		strMeshName.reserve(iMeshNameLength);
		_inFile.read(strMeshName.data(), iMeshNameLength);

		// �޽��� ���׸��� ��ȣ�� �н��ϴ�.
		uint32 iMaterialIndex = 0;
		_inFile.read(reinterpret_cast<char*>(&iMaterialIndex), sizeof(uint32));
		_spModelDesc->m_vecMaterialIndices.emplace_back(iMaterialIndex);

		// ���ؽ� �����͸� �н��ϴ�.
		uint64 iVertexSize = 0;
		_inFile.read(reinterpret_cast<char*>(&iVertexSize), sizeof(uint64));

		vector<TPositionNormalTexCoordTangent> vecVertices;
		vecVertices.reserve(iVertexSize);
		vecVertices.resize(iVertexSize);
		_inFile.read(reinterpret_cast<char*>(vecVertices.data()), sizeof(TPositionNormalTexCoordTangent) * iVertexSize);

		_spModelDesc->m_vecNumVertices.emplace_back(static_cast<uint32>(iVertexSize));
		m_umapEffectMeshVertices.emplace(wstrFileName, vecVertices);

		// �ε��� �����͸� �н��ϴ�.
		uint64 iIndexSize = 0;
		_inFile.read(reinterpret_cast<char*>(&iIndexSize), sizeof(uint64));

		vector<uint32> vecIndices;
		vecIndices.reserve(iIndexSize);
		vecIndices.resize(iIndexSize);
		_inFile.read(reinterpret_cast<char*>(vecIndices.data()), sizeof(uint32) * iIndexSize);

		// L"Hyunwoo0"
		_spModelDesc->m_vecNumIndices.emplace_back(static_cast<uint32>(iIndexSize));
		m_umapEffectMeshIndices.emplace(wstrFileName, vecIndices);
	}

	return S_OK;
}

HRESULT Engine::CEffectLoader::LoadEffectMeshDataFromFile()
{
	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrEffectMeshDataFilePath))
	{
		// ������ �ƴ� ���
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// dat ������ �ƴ� ���
		if (fsEntry.path().extension().generic_string() != ".dat" && fsEntry.path().extension().generic_string() != ".DAT") { continue; }

		std::ifstream inFile;
		inFile.open(fsEntry.path().c_str(), ios_base::in | ios_base::binary);

		// ������ ������ ���� ���
		if (!inFile.is_open()) { return E_FAIL; }

		shared_ptr<FMeshEffectDataGroupProperty> spMeshEffectGroup = make_shared<FMeshEffectDataGroupProperty>();
		spMeshEffectGroup->m_wstrMeshEffectGroupName = fsEntry.path().stem().generic_wstring();

		LoadEffectMeshData(inFile, spMeshEffectGroup, fsEntry);

		m_wpEffectHandler.lock()->AddEffectMeshDataGroup(spMeshEffectGroup->m_wstrMeshEffectGroupName, spMeshEffectGroup);
		inFile.close();
	}
	return S_OK;
}

HRESULT Engine::CEffectLoader::LoadEffectMeshData(std::ifstream& _inFile, std::shared_ptr<FMeshEffectDataGroupProperty>& _spMeshEffectGroup, const std::filesystem::directory_entry& _fsEntry)
{
	// ����Ʈ ������ �н��ϴ�.
	uint32 iNumEffectMeshData = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumEffectMeshData), sizeof(uint32));

	_spMeshEffectGroup->m_vecMeshEffectDataNames.resize(iNumEffectMeshData);

	_spMeshEffectGroup->m_vecEffectModelDescNames.resize(iNumEffectMeshData);
	_spMeshEffectGroup->m_vecVSDescNames.resize(iNumEffectMeshData);
	_spMeshEffectGroup->m_vecPSDescNames.resize(iNumEffectMeshData);

	_spMeshEffectGroup->m_vecPlayProperties.resize(iNumEffectMeshData);
	_spMeshEffectGroup->m_vecMaskProperties.resize(iNumEffectMeshData);
	_spMeshEffectGroup->m_vecNoiseProperties.resize(iNumEffectMeshData);
	_spMeshEffectGroup->m_vecColorProperties.resize(iNumEffectMeshData);
	_spMeshEffectGroup->m_vecTransformProperties.resize(iNumEffectMeshData);
	_spMeshEffectGroup->m_vecUVProperties.resize(iNumEffectMeshData);

	for (uint32 iIndex = 0; iIndex < iNumEffectMeshData; ++iIndex)
	{
		// ����Ʈ �޽� ������ �̸�
		uint32 iEffectMeshDataNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iEffectMeshDataNameLength), sizeof(uint32));

		string strEffectMeshDataName = "";
		strEffectMeshDataName.resize(iEffectMeshDataNameLength);
		_inFile.read(strEffectMeshDataName.data(), iEffectMeshDataNameLength);

		wstring wstrEffectMeshDataName = L"";
		wstrEffectMeshDataName.assign(strEffectMeshDataName.begin(), strEffectMeshDataName.end());

		_spMeshEffectGroup->m_vecMeshEffectDataNames[iIndex] = wstrEffectMeshDataName;



		// �� �̸�
		uint32 iEffectModelDescNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iEffectModelDescNameLength), sizeof(uint32));

		string strEffectModelDescName = "";
		strEffectModelDescName.resize(iEffectModelDescNameLength);
		_inFile.read(strEffectModelDescName.data(), iEffectModelDescNameLength);

		wstring wstrEffectModelDescName = L"";
		wstrEffectModelDescName.assign(strEffectModelDescName.begin(), strEffectModelDescName.end());

		_spMeshEffectGroup->m_vecEffectModelDescNames[iIndex] = wstrEffectModelDescName;



		// ���ؽ� ���̴� �̸�
		uint32 iVSDescNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iVSDescNameLength), sizeof(uint32));

		string strVSDescName = "";
		strVSDescName.resize(iVSDescNameLength);
		_inFile.read(strVSDescName.data(), iVSDescNameLength);

		wstring wstrVSDescName = L"";
		wstrVSDescName.assign(strVSDescName.begin(), strVSDescName.end());

		_spMeshEffectGroup->m_vecVSDescNames[iIndex] = wstrVSDescName;



		// �ȼ� ���̴� �̸�
		uint32 iPSDescNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iPSDescNameLength), sizeof(uint32));

		string strPSDescName = "";
		strPSDescName.resize(iPSDescNameLength);
		_inFile.read(strPSDescName.data(), iPSDescNameLength);

		wstring wstrPSDescName = L"";
		wstrPSDescName.assign(strPSDescName.begin(), strPSDescName.end());

		_spMeshEffectGroup->m_vecPSDescNames[iIndex] = wstrPSDescName;



		// �÷��� ������Ƽ
		FPlayEffectProperty tPlayProperty;
		_inFile.read(reinterpret_cast<char*>(&tPlayProperty.m_fStartPlaySeconds), sizeof(float));
		_inFile.read(reinterpret_cast<char*>(&tPlayProperty.m_fFinishPlaySeconds), sizeof(float));
		_inFile.read(reinterpret_cast<char*>(&tPlayProperty.m_bLoop), sizeof(bool));

		_spMeshEffectGroup->m_vecPlayProperties[iIndex] = tPlayProperty;



		// ����ũ ������Ƽ
		FMaskEffectProperty tMaskProperty;
		_inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_bUseMask), sizeof(bool));
		_inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_bUseColorMask), sizeof(bool));

		uint32 iMaskTextureNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iMaskTextureNameLength), sizeof(uint32));

		string strMaskTextureName = "";
		strMaskTextureName.resize(iMaskTextureNameLength);
		_inFile.read(strMaskTextureName.data(), iMaskTextureNameLength);

		wstring wstrMaskTextureName = L"";
		wstrMaskTextureName.assign(strMaskTextureName.begin(), strMaskTextureName.end());

		tMaskProperty.m_wstrMaskTextureName = wstrMaskTextureName;
		_inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_iMaskRowColume[0]), sizeof(int32));
		_inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_iMaskRowColume[1]), sizeof(int32));
		_inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_vMaskUVSpeed), sizeof(Vector2));
		_inFile.read(reinterpret_cast<char*>(&tMaskProperty.m_vMaskMaxUV), sizeof(Vector2));

		_spMeshEffectGroup->m_vecMaskProperties[iIndex] = tMaskProperty;



		// ������ ������Ƽ
		FNoiseEffectProperty tNoiseProperty;
		_inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_bUseNoise), sizeof(bool));

		uint32 iNoiseTextureNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iNoiseTextureNameLength), sizeof(uint32));

		string strNoiseTextureName = "";
		strNoiseTextureName.resize(iNoiseTextureNameLength);
		_inFile.read(strNoiseTextureName.data(), iNoiseTextureNameLength);

		wstring wstrNoiseTextureName = L"";
		wstrNoiseTextureName.assign(strNoiseTextureName.begin(), strNoiseTextureName.end());

		tNoiseProperty.m_wstrNoiseTextureName = wstrNoiseTextureName;
		_inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_iNoiseRowColume[0]), sizeof(int32));
		_inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_iNoiseRowColume[1]), sizeof(int32));
		_inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_vNoiseUVSpeed), sizeof(Vector2));
		_inFile.read(reinterpret_cast<char*>(&tNoiseProperty.m_vNoiseMaxUV), sizeof(Vector2));

		_spMeshEffectGroup->m_vecNoiseProperties[iIndex] = tNoiseProperty;



		// ���� ������Ƽ
		FColorEffectProperty tColorProperty;
		_inFile.read(reinterpret_cast<char*>(&tColorProperty.m_vStartColor), sizeof(Vector4));
		_inFile.read(reinterpret_cast<char*>(&tColorProperty.m_vFinishColor), sizeof(Vector4));

		_spMeshEffectGroup->m_vecColorProperties[iIndex] = tColorProperty;



		// Ʈ������ ������Ƽ
		FTransformEffectProperty tTransformProperty;
		_inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vStartScale), sizeof(Vector3));
		_inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vStartRotate), sizeof(Vector3));
		_inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vStartTranslate), sizeof(Vector3));
		_inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vFinishScale), sizeof(Vector3));
		_inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vFinishRotate), sizeof(Vector3));
		_inFile.read(reinterpret_cast<char*>(&tTransformProperty.m_vFinishTranslate), sizeof(Vector3));

		_spMeshEffectGroup->m_vecTransformProperties[iIndex] = tTransformProperty;



		// UV ������Ƽ
		FUVEffectProperty tUVProperty;
		_inFile.read(reinterpret_cast<char*>(&tUVProperty.m_bUseEffectUV), sizeof(bool));
		_inFile.read(reinterpret_cast<char*>(&tUVProperty.m_vEffectStartUV), sizeof(Vector2));
		_inFile.read(reinterpret_cast<char*>(&tUVProperty.m_vEffectFinishUV), sizeof(Vector2));

		_spMeshEffectGroup->m_vecUVProperties[iIndex] = tUVProperty;
	}
	return S_OK;
}
