#include "pch.h"
#include "ModelLoader.h"

#include "DeviceManager.h"
#include "ModelHandler.h"
#include "ViewHandler.h"

#include "BoneOffset.h"
#include "Bone.h"
#include "Animation.h"
#include "Channel.h"

std::shared_ptr<CModelLoader> Engine::CModelLoader::Create()
{
	const std::shared_ptr<CModelLoader> spLoader = make_shared<CModelLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create model loader.");
	return spLoader;
}

HRESULT Engine::CModelLoader::Initialize()
{
	m_wpModelHandler = CModelHandler::GetInstance();
	m_wpViewHandler = CViewHandler::GetInstance();
	m_wpDeviceManager = CModelHandler::GetInstance()->GetDeviceManager();

	// �ܺο��� ������ �ҷ��ɴϴ�.
	LoadStaticModelFromFile();
	LoadSkeletalModelFromFile();

	CreateVertexBuffer();
	CreateIndexBuffer();
	return S_OK;
}

void Engine::CModelLoader::Release()
{
	for (auto& pair : m_umapStaticVertices)
	{
		pair.second.clear();
	}
	m_umapStaticVertices.clear();

	for (auto& pair : m_umapSkeletalVertices)
	{
		pair.second.clear();
	}
	m_umapSkeletalVertices.clear();

	for (auto& pair : m_umapIndices)
	{
		pair.second.clear();
	}
	m_umapIndices.clear();
}

HRESULT Engine::CModelLoader::CreateVertexBuffer()
{
	// ����ƽ �𵨿��� ���ؽ� ���۸� �����մϴ�.
	for (const auto& pair : m_umapStaticVertices)
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
		m_wpModelHandler.lock()->AddVertexBuffer(pair.first, cpBuffer);
	}

	// ���̷�Ż �𵨿��� ���ؽ� ���۸� �����մϴ�.
	for (const auto& pair : m_umapSkeletalVertices)
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
		m_wpModelHandler.lock()->AddVertexBuffer(pair.first, cpBuffer);
	}
	return S_OK;
}

HRESULT Engine::CModelLoader::CreateIndexBuffer()
{
	for (const auto& pair : m_umapIndices)
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
		m_wpModelHandler.lock()->AddIndexBuffer(pair.first, cpBuffer);
	}
	return S_OK;
}

HRESULT Engine::CModelLoader::LoadStaticModelFromFile()
{
	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_strStaticModelFilePath))
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
		spModelDesc->m_eModelType = EModelType::STATIC;

		LoadStaticMeshes(inFile, spModelDesc, fsEntry);
		LoadStaticMaterials(inFile, spModelDesc, fsEntry);
		m_wpModelHandler.lock()->AddModelDesc(spModelDesc->m_wstrModelName, spModelDesc);

		inFile.close();
	}
	return S_OK;
}

HRESULT Engine::CModelLoader::LoadSkeletalModelFromFile()
{
	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_strSkeletalModelFilePath))
	{
		// ������ �ƴ� ���
		// if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// dat ������ �ƴ� ���
		string strExtension = fsEntry.path().extension().generic_string();
		string strFileName = fsEntry.path().stem().generic_string();
		if (strExtension != ".dat" && strExtension != ".DAT") { continue; }

		std::ifstream inFile;
		inFile.open(fsEntry.path().c_str(), ios_base::in | ios_base::binary);

		// ������ ������ ���� ���
		if (!inFile.is_open()) { return E_FAIL; }

		// �� Ÿ���� �н��ϴ�.
		int8 iModelType = 0;
		inFile.read((char*)&iModelType, sizeof(int8));

		shared_ptr<FModelDesc> spModelDesc = make_shared<FModelDesc>();
		spModelDesc->m_eModelType = EModelType::SKELETAL;

		LoadSkeletalBones(inFile, spModelDesc, fsEntry);

		LoadSkeletalMeshes(inFile, spModelDesc, fsEntry);

		LoadSkeletalMaterials(inFile, spModelDesc, fsEntry);

		LoadSkeletalAnimations(inFile, spModelDesc, fsEntry);

		m_wpModelHandler.lock()->AddModelDesc(spModelDesc->m_wstrModelName, spModelDesc);

		inFile.close();
	}
	return S_OK;
}

HRESULT Engine::CModelLoader::LoadEffectModelFromFile()
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
		LoadStaticMeshes(inFile, spModelDesc, fsEntry);

		m_wpModelHandler.lock()->AddModelDesc(spModelDesc->m_wstrModelName, spModelDesc);

		inFile.close();
	}
	return S_OK;
}



HRESULT Engine::CModelLoader::LoadStaticMeshes(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry)
{
	// dat ������ �̸��� �����մϴ�. L"Hyunwoo"
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
		// �޽��� �̸��� ���մϴ�. L"Hyunwoo0"
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
		
		// L"Hyunwoo0"
		_spModelDesc->m_vecNumVertices.emplace_back(static_cast<uint32>(iVertexSize));
		m_umapStaticVertices.emplace(wstrFileName, vecVertices);

		// �ε��� �����͸� �н��ϴ�.
		uint64 iIndexSize = 0;
		_inFile.read(reinterpret_cast<char*>(&iIndexSize), sizeof(uint64));

		vector<uint32> vecIndices;
		vecIndices.reserve(iIndexSize);
		vecIndices.resize(iIndexSize);
		_inFile.read(reinterpret_cast<char*>(vecIndices.data()), sizeof(uint32) * iIndexSize);

		// L"Hyunwoo0"
		_spModelDesc->m_vecNumIndices.emplace_back(static_cast<uint32>(iIndexSize));
		m_umapIndices.emplace(wstrFileName, vecIndices);
	}

	return S_OK;
}

HRESULT Engine::CModelLoader::LoadStaticMaterials(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry)
{
	// ���׸����� ������ �н��ϴ�.
	uint32 iNumMaterials = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumMaterials), sizeof(uint32));

	for (uint32 iMaterialIndex = 0; iMaterialIndex < iNumMaterials; ++iMaterialIndex)
	{
		int32 iNumTextures = 0;

		vector<uint32> vecTextureIndices;

		// �⺻ ������ �н��ϴ�.
		Vector4 vBaseColor = Vector4::One;
		_inFile.read(reinterpret_cast<char*>(&vBaseColor), sizeof(Vector4));
		
		for (int32 jIndex = 0; jIndex < AI_TEXTURE_TYPE_MAX; jIndex++)
		{
			// �ؽ�ó ��ȣ�� �н��ϴ�.
			int32 iNan = 0;
			_inFile.read(reinterpret_cast<char*>(&iNan), sizeof(int32));

			if (iNan == -1) { continue; }

			// �ؽ�ó ����� ���̸� �н��ϴ�.
			uint32 iTextureFilePathLength = 0;
			_inFile.read(reinterpret_cast<char*>(&iTextureFilePathLength), sizeof(uint32));

			string strTextureFilePath;
			strTextureFilePath.reserve(iTextureFilePathLength);
			strTextureFilePath.resize(iTextureFilePathLength);

			// �ؽ��� ��θ� �н��ϴ�. L"../../Resource/Meshes/Skeletal/Survivor/Hyunwoo/....png"
			_inFile.read(strTextureFilePath.data(), iTextureFilePathLength);
			wstring wstrTextureFilePath(strTextureFilePath.begin(), strTextureFilePath.end());

			// �ؽ�ó �������͸� �����մϴ�.
			ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = nullptr;
			wstring wstrTextureFileExtenstion = _fsEntry.path().extension().generic_wstring();
			if (wstrTextureFileExtenstion == L".dds" || wstrTextureFileExtenstion == L".DDS")
			{
				// dds Ȯ����
				if (FAILED(CreateDDSTextureFromFile(m_wpDeviceManager.lock()->GetDevice().Get(), wstrTextureFilePath.c_str(), nullptr, cpShaderResourceView.GetAddressOf())))
				{
					return E_FAIL;
				}
			}
			else if (wstrTextureFileExtenstion == L".tga" || wstrTextureFileExtenstion == L".TGA")
			{
				// tga Ȯ����
				return E_FAIL;
			}
			else
			{
				// jpg, png Ȯ����
				if (FAILED(CreateWICTextureFromFile(m_wpDeviceManager.lock()->GetDevice().Get(), wstrTextureFilePath.c_str(), nullptr, cpShaderResourceView.GetAddressOf())))
				{
					return E_FAIL;
				}
			}

			// L"Hyunwoo0_0", L"Hyunwoo0_1", ..., L"Hyunwoo64_0"
			wstring wstrFileName = _fsEntry.path().stem().generic_wstring() + L"_" + to_wstring(iMaterialIndex) + L"_" + to_wstring(iNumTextures++);
			m_wpModelHandler.lock()->AddShaderResourceView(wstrFileName, cpShaderResourceView.Get());

			vecTextureIndices.emplace_back(iNan);
		}
		
		// �� ���׸����� �ؽ�ó�� ���� �����մϴ�.
		_spModelDesc->m_vecNumTextures.emplace_back(iNumTextures);
		_spModelDesc->m_vecTextureIndices.emplace_back(vecTextureIndices);
		_spModelDesc->m_vecBaseColors.emplace_back(vBaseColor);
	}

	return S_OK;
}



HRESULT Engine::CModelLoader::LoadSkeletalMeshes(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry)
{
	// dat ������ �̸��� �����մϴ�.
	_spModelDesc->m_wstrModelName = _fsEntry.path().stem().generic_wstring();

	// �޽��� ������ �н��ϴ�.
	uint32 iNumMeshes = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumMeshes), sizeof(uint32));
	_spModelDesc->m_iNumMeshes = iNumMeshes;
	
	_spModelDesc->m_vecNumVertices.reserve(iNumMeshes);
	_spModelDesc->m_vecNumIndices.reserve(iNumMeshes);
	// _spModelDesc->m_vecMaterials.reserve(iNumMeshes);
	_spModelDesc->m_vecMaterialIndices.reserve(iNumMeshes);

	/********************
		���̷�Ż �޽�
	********************/
	for (uint64 iIndex = 0; iIndex < iNumMeshes; ++iIndex)
	{
		// ������ �̸��� ���մϴ�. L"Hyunwoo0"
		wstring wstrFileName = _fsEntry.path().stem().generic_wstring();
		wstring wstrFileNameNo = _fsEntry.path().stem().generic_wstring() + to_wstring(iIndex);

		// �޽��� �̸��� �н��ϴ�.
		uint32 iMeshNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iMeshNameLength), sizeof(uint32));

		string strMeshName;
		strMeshName.reserve(iMeshNameLength);
		strMeshName.resize(iMeshNameLength);
		_inFile.read(strMeshName.data(), iMeshNameLength);

		// �޽��� ���׸��� ��ȣ�� �н��ϴ�.
		uint32 iMaterialIndex = 0;
		_inFile.read(reinterpret_cast<char*>(&iMaterialIndex), sizeof(uint32));
		_spModelDesc->m_vecMaterialIndices.emplace_back(iMaterialIndex);

		// ���� ������ �н��ϴ�.
		uint32 iNumBones = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumBones), sizeof(uint32));

		vector<uint32> vecBoneIndices;
		vector<Matrix> vecOffsetMatrices;

		for (uint32 jIndex = 0; jIndex < iNumBones; ++jIndex)
		{
			// ���� �̸��� �н��ϴ�.
			uint32 iBoneNameLength = 0;
			_inFile.read(reinterpret_cast<char*>(&iBoneNameLength), sizeof(uint32));

			string strBoneName;
			strBoneName.reserve(iBoneNameLength);
			strBoneName.resize(iBoneNameLength);
			_inFile.read(strBoneName.data(), iBoneNameLength);

			int32 iBoneIndex = m_wpModelHandler.lock()->FindBoneIndex(wstrFileName, strBoneName);
			vecBoneIndices.push_back(iBoneIndex);

			// ���� ������ ����� �н��ϴ�.
			Matrix matOffset = Matrix::Identity;
			_inFile.read(reinterpret_cast<char*>(&matOffset), sizeof(Matrix));

			vecOffsetMatrices.push_back(matOffset);
		}

		if (iNumBones == 0)
		{
			iNumBones = 1;

			int32 iBoneIndex = m_wpModelHandler.lock()->FindBoneIndex(wstrFileName, strMeshName);
			vecBoneIndices.push_back(iBoneIndex);

			vecOffsetMatrices.push_back(Matrix::Identity);
		}
		
		shared_ptr<CBoneOffset> spBoneOffset = CBoneOffset::Create(iNumBones, vecBoneIndices, vecOffsetMatrices);
		m_wpModelHandler.lock()->AddBoneOffset(wstrFileNameNo, spBoneOffset);

		/********************
			���ؽ�
		********************/
		// ���ؽ� �����͸� �����մϴ�.
		uint64 iVertexSize = 0;
		_inFile.read((char*)&iVertexSize, sizeof(uint64));

		vector<TPositionNormalTexCoordTangentBlend> vecVertices;
		vecVertices.reserve(iVertexSize);
		vecVertices.resize(iVertexSize);
		_inFile.read(reinterpret_cast<char*>(vecVertices.data()), sizeof(TPositionNormalTexCoordTangentBlend) * iVertexSize);

		// L"Hyunwoo0"
		_spModelDesc->m_vecNumVertices.emplace_back(static_cast<uint32>(iVertexSize));
		m_umapSkeletalVertices.emplace(wstrFileNameNo, vecVertices);

		/********************
			�ε���
		********************/
		// �ε��� �����͸� �����մϴ�.
		uint64 iIndexSize = 0;
		_inFile.read((char*)&iIndexSize, sizeof(uint64));

		vector<uint32> vecIndices;
		vecIndices.reserve(iIndexSize);
		vecIndices.resize(iIndexSize);
		_inFile.read(reinterpret_cast<char*>(vecIndices.data()), sizeof(uint32) * iIndexSize);

		// L"Hyunwoo0"
		_spModelDesc->m_vecNumIndices.emplace_back(static_cast<uint32>(iIndexSize));
		m_umapIndices.emplace(wstrFileNameNo, vecIndices);
	}

	return S_OK;
}

HRESULT Engine::CModelLoader::LoadSkeletalMaterials(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry)
{
	// ���׸����� ������ �н��ϴ�.
	uint32 iNumMaterials = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumMaterials), sizeof(uint32));

	for (uint32 iMaterialIndex = 0; iMaterialIndex < iNumMaterials; ++iMaterialIndex)
	{
		int32 iNumTextures = 0;

		for (int32 jIndex = 0; jIndex < AI_TEXTURE_TYPE_MAX; jIndex++)
		{
			// �ؽ�ó ��ȣ�� �н��ϴ�.
			int32 iNan = 0;
			_inFile.read(reinterpret_cast<char*>(&iNan), sizeof(int32));

			if (iNan == -1) { continue; }

			// �ؽ�ó ����� ���̸� �н��ϴ�.
			uint32 iTextureFilePathLength = 0;
			_inFile.read(reinterpret_cast<char*>(&iTextureFilePathLength), sizeof(uint32));

			string strTextureFilePath;
			strTextureFilePath.reserve(iTextureFilePathLength);
			strTextureFilePath.resize(iTextureFilePathLength);

			// �ؽ��� ��θ� �н��ϴ�.
			_inFile.read(strTextureFilePath.data(), iTextureFilePathLength);
			wstring wstrTextureFilePath(strTextureFilePath.begin(), strTextureFilePath.end());

			// �ؽ�ó �������͸� �����մϴ�.
			ComPtr<ID3D11ShaderResourceView> cpShaderResourceView = nullptr;
			wstring wstrTextureFileExtenstion = _fsEntry.path().extension().generic_wstring();
			if (wstrTextureFileExtenstion == L".dds" || wstrTextureFileExtenstion == L".DDS")
			{
				// dds Ȯ����
				if (FAILED(CreateDDSTextureFromFile(m_wpDeviceManager.lock()->GetDevice().Get(), wstrTextureFilePath.c_str(), nullptr, cpShaderResourceView.GetAddressOf()))) { return E_FAIL; }
			}
			else if (wstrTextureFileExtenstion == L".tga" || wstrTextureFileExtenstion == L".TGA")
			{
				// tga Ȯ����
				return E_FAIL;
			}
			else
			{
				// jpg, png Ȯ����
				if (FAILED(CreateWICTextureFromFile(m_wpDeviceManager.lock()->GetDevice().Get(), wstrTextureFilePath.c_str(), nullptr, cpShaderResourceView.GetAddressOf()))) { return E_FAIL; }
			}

			// L"Hyunwoo0_0", L"Hyunwoo0_1", ...
			wstring wstrFileName = _fsEntry.path().stem().generic_wstring() + L"_" + to_wstring(iMaterialIndex) + L"_" + to_wstring(iNumTextures++);
			m_wpModelHandler.lock()->AddShaderResourceView(wstrFileName, cpShaderResourceView.Get());
		}
		// �� ���׸����� �ؽ�ó�� ���� �����մϴ�.
		_spModelDesc->m_vecNumTextures.emplace_back(iNumTextures);
	}
	return S_OK;
}

HRESULT Engine::CModelLoader::LoadSkeletalBones(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry)
{
	// L"Hyunwoo"
	wstring wstrFileName = _fsEntry.path().stem().generic_wstring();

	uint32 iBoneInfoSize = 0;
	_inFile.read(reinterpret_cast<char*>(&iBoneInfoSize), sizeof(int32));

	vector<shared_ptr<CBone>> vecBones(iBoneInfoSize, nullptr);

	for (size_t iIndex = 0; iIndex < iBoneInfoSize; ++iIndex)
	{
		uint32 iBoneNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iBoneNameLength), sizeof(uint32));

		string strBoneName = "";
		strBoneName.reserve(iBoneNameLength);
		strBoneName.resize(iBoneNameLength);
		_inFile.read(strBoneName.data(), iBoneNameLength);

		// ���� ����� �н��ϴ�.
		Matrix matTransform = Matrix::Identity;
		_inFile.read(reinterpret_cast<char*>(&matTransform), sizeof(Matrix));

		// �θ� ���� ��ȣ�� �н��ϴ�.
		int32 iParentBone = -1;
		_inFile.read(reinterpret_cast<char*>(&iParentBone), sizeof(int32));

		shared_ptr<CBone> spBone = CBone::Create(strBoneName, matTransform, iParentBone);
		vecBones[iIndex] = spBone;
	}
	
	m_wpModelHandler.lock()->AddBone(wstrFileName, vecBones);
	return S_OK;
}

HRESULT Engine::CModelLoader::LoadSkeletalAnimations(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry)
{
	// L"Hyunwoo"
	wstring wstrFileName = _fsEntry.path().stem().generic_wstring();

	// �ִϸ��̼��� ������ �н��ϴ�.
	uint32 iNumAnimations = 0;
	_inFile.read(reinterpret_cast<char*>(&iNumAnimations), sizeof(uint32));

	unordered_map<string, shared_ptr<CAnimation>> umapAnimations;
	umapAnimations.reserve(iNumAnimations);

	for (size_t iIndex = 0; iIndex < iNumAnimations; ++iIndex)
	{
		// �ִϸ��̼��� �̸��� �н��ϴ�.
		uint32 iAnimationNameLength = 0;
		_inFile.read(reinterpret_cast<char*>(&iAnimationNameLength), sizeof(uint32));

		string strAnimationName;
		strAnimationName.reserve(iAnimationNameLength);
		strAnimationName.resize(iAnimationNameLength);
		_inFile.read(strAnimationName.data(), iAnimationNameLength);

		// �ִϸ��̼� ��� �ð��� �н��ϴ�.
		double dDuration = 0.0;
		_inFile.read(reinterpret_cast<char*>(&dDuration), sizeof(double));

		// �ִϸ��̼� �ʴ� ƽ ���� �н��ϴ�.
		double dTickPerSecond = 0.0;
		_inFile.read(reinterpret_cast<char*>(&dTickPerSecond), sizeof(double));

		// �ִϸ��̼� ä���� ��(���� ��)�� �н��ϴ�.
		uint32 iNumChannels = 0;
		_inFile.read(reinterpret_cast<char*>(&iNumChannels), sizeof(uint32));

		vector<shared_ptr<CChannel>> vecChannels;
		vecChannels.reserve(iNumChannels);

		for (uint32 jIndex = 0; jIndex < iNumChannels; ++jIndex)
		{
			// ä���� �̸��� �н��ϴ�.
			uint32 iChannelNameLength = 0;
			_inFile.read(reinterpret_cast<char*>(&iChannelNameLength), sizeof(uint32));

			string strChannelName;
			strChannelName.reserve(iChannelNameLength);
			strChannelName.resize(iChannelNameLength);
			_inFile.read(strChannelName.data(), iChannelNameLength);

			// Ű�������� �ִ� ������ �н��ϴ�.
			uint32 iNumKeyFrames = 0;
			_inFile.read(reinterpret_cast<char*>(&iNumKeyFrames), sizeof(uint32));

			// Ű�������� �н��ϴ�.
			vector<FKeyFrame> vecKeyFrames;
			vecKeyFrames.reserve(iNumKeyFrames);
			vecKeyFrames.resize(iNumKeyFrames);
			_inFile.read(reinterpret_cast<char*>(vecKeyFrames.data()), sizeof(FKeyFrame) * iNumKeyFrames);

			int32 iBoneIndex = m_wpModelHandler.lock()->FindBoneIndex(wstrFileName, strChannelName);

			shared_ptr<CChannel> spChannel = CChannel::Create(strChannelName, iBoneIndex, iNumKeyFrames, vecKeyFrames);
			vecChannels.push_back(spChannel);
		}

		shared_ptr<CAnimation> spAnimation = CAnimation::Create(strAnimationName, dDuration, dTickPerSecond, iNumChannels, vecChannels);
		umapAnimations.insert({ strAnimationName, spAnimation });
	}

	m_wpModelHandler.lock()->AddAnimation(wstrFileName, umapAnimations);
	return S_OK;
}

int32 Engine::CModelLoader::GetNumVertices(EModelType _eModelType, const std::wstring& _wstrVertexBufferName)
{
	switch (_eModelType)
	{
	case Engine::EModelType::STATIC:
		return static_cast<int32>(m_umapStaticVertices[_wstrVertexBufferName].size());

	case Engine::EModelType::SKELETAL:
		return  static_cast<int32>(m_umapSkeletalVertices[_wstrVertexBufferName].size());

	default:
		break;
	}
	return -1;
}

int32 Engine::CModelLoader::GetNumIndices(const std::wstring& _wstrIndexBufferName)
{
	return static_cast<int32>(m_umapIndices[_wstrIndexBufferName].size());
}

Vector3 Engine::CModelLoader::GetAverageWorldPosition(EModelType _eModelType, const std::wstring& _wstrVertexBufferName)
{
	switch (_eModelType)
	{
	case Engine::EModelType::STATIC:
	{
		const std::vector<TPositionNormalTexCoordTangent>& vecVertices = m_umapStaticVertices[_wstrVertexBufferName];

		Vector3 vPosition = Vector3::Zero;
		for (const auto& tVertex : vecVertices)
		{
			vPosition += tVertex.m_vPosition;
		}
		vPosition /= static_cast<float>(vecVertices.size());

		return vPosition;
	}
	break;

	default:
		break;
	}
	return { 0.0f, 0.0f, 0.0f };
}
