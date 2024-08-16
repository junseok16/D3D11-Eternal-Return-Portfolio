#include "pch.h"
#include "ASSIMPManager.h"

HRESULT Parser::CASSIMPManager::Initialize()
{
	return S_OK;
}

HRESULT Parser::CASSIMPManager::ConvertFBX2DAT(EModelType _eModelType)
{
	switch (_eModelType)
	{
	case Parser::EModelType::STATIC:
	{
		m_matPivot = Matrix::Identity;
		if (m_strStaticModelFilePath.empty()) { return E_FAIL; }
		SaveStaticModel();
	}
	break;

	case Parser::EModelType::SKELETAL:
	{
		m_matPivot = Matrix::Identity;
		m_matPivot *= Matrix::CreateRotationY(XMConvertToRadians(180.0f));

		if (m_strSkeletalModelFilePath.empty()) { return E_FAIL; }
		SaveSkeletalModel();
	}
	break;

	case Parser::EModelType::NAVIGATION:
	{
		m_matPivot = Matrix::Identity;
		if (m_strNavigationModelFilePath.empty()) { return E_FAIL; }
		SaveNavigationModel();
	}
	break;

	case Parser::EModelType::EFFECT:
	{
		m_matPivot = Matrix::Identity;
		m_matPivot *= Matrix::CreateScale(0.1f);
		if (m_strEffectModelFilePath.empty()) { return E_FAIL; }
		SaveEffectModel();
	}
	break;

	default:
		CHECKF(false, L"The model type is not designated.")
		break;
	}

	return S_OK;
}

void Parser::CASSIMPManager::Release()
{
}

HRESULT Parser::CASSIMPManager::SaveStaticModel()
{
	m_iFlag = aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast | aiProcess_PreTransformVertices;

	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_strStaticModelFilePath))
	{
		// 파일이 아닌 경우
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// fbx 파일이 아닌 경우
		if (fsEntry.path().extension().generic_string() != ".FBX" && fsEntry.path().extension().generic_string() != ".fbx") { continue; }

		// dat 파일을 생성합니다.
		string strFileName = fsEntry.path().stem().string();
		string strFilePath = fsEntry.path().parent_path().generic_string();
		string strPath = strFilePath + "/" + strFileName + ".dat";

		std::ofstream outFile;
		outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

		// 파일이 열리지 않은 경우
		if (!outFile.is_open()) { return E_FAIL; }

		string strModelPath = fsEntry.path().generic_string();
		m_pAIScene = m_oAIImporter.ReadFile(strModelPath.c_str(), m_iFlag);

		// fbx 파일을 열 수 없는 경우
		if (!m_pAIScene)
		{
			outFile.close();
			return E_FAIL;
		}

		// 모델 타입을 씁니다.
		int8 iModelType = (int8)EModelType::STATIC;
		outFile.write((char*)&iModelType, sizeof(int8));

		SaveStaticMeshes(outFile, fsEntry);

		SaveMaterials(outFile, fsEntry);

		m_oAIImporter.FreeScene();
		outFile.close();
	}
	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveSkeletalModel()
{
	m_iFlag = aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast;

	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_strSkeletalModelFilePath))
	{
		// fbx 파일이 아닌 경우
		wstring extenstion = fsEntry.path().extension().generic_wstring();
		if (extenstion != L".FBX" && extenstion != L".fbx") { continue; }

		// dat 파일을 생성합니다.
		string strFileName = fsEntry.path().stem().string();
		string strFilePath = fsEntry.path().parent_path().generic_string();
		string strPath = strFilePath + "/" + strFileName + ".dat";

		std::ofstream outFile;
		outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

		// 파일이 열리지 않은 경우
		if (!outFile.is_open()) { return E_FAIL; }

		string strModelPath = fsEntry.path().generic_string();
		m_pAIScene = m_oAIImporter.ReadFile(strModelPath.c_str(), m_iFlag);

		// fbx 파일을 열 수 없는 경우
		if (!m_pAIScene)
		{
			outFile.close();
			return E_FAIL;
		}

		// 모델 타입을 씁니다.
		int8 iModelType = static_cast<int8>(EModelType::SKELETAL);
		outFile.write((char*)&iModelType, sizeof(int8));

		SaveBones(outFile, fsEntry);

		SaveSkeletalMeshes(outFile, fsEntry);

		SaveMaterials(outFile, fsEntry);

		SaveAnimations(outFile, fsEntry);

		m_oAIImporter.FreeScene();
		outFile.close();
	}
	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveNavigationModel()
{
	m_iFlag = aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast | aiProcess_PreTransformVertices;

	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_strNavigationModelFilePath))
	{
		// 파일이 아닌 경우
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// fbx 파일이 아닌 경우
		if (fsEntry.path().extension().generic_string() != ".FBX" && fsEntry.path().extension().generic_string() != ".fbx") { continue; }

		// dat 파일을 생성합니다.
		string strFileName = fsEntry.path().stem().string();
		string strFilePath = fsEntry.path().parent_path().generic_string();
		string strPath = strFilePath + "/" + strFileName + ".dat";

		std::ofstream outFile;
		outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

		// 파일이 열리지 않은 경우
		if (!outFile.is_open()) { return E_FAIL; }

		string strModelPath = fsEntry.path().generic_string();
		m_pAIScene = m_oAIImporter.ReadFile(strModelPath.c_str(), m_iFlag);

		// fbx 파일을 열 수 없는 경우
		if (!m_pAIScene)
		{
			outFile.close();
			return E_FAIL;
		}

		// 모델 타입을 씁니다.
		int8 iModelType = (int8)EModelType::NAVIGATION;
		outFile.write((char*)&iModelType, sizeof(int8));

		SaveNaviMeshes(outFile, fsEntry);

		m_oAIImporter.FreeScene();
		outFile.close();
	}
	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveEffectModel()
{
	m_iFlag = aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast | aiProcess_PreTransformVertices;

	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_strEffectModelFilePath))
	{
		// 파일이 아닌 경우
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// fbx 파일이 아닌 경우
		if (fsEntry.path().extension().generic_string() != ".FBX" && fsEntry.path().extension().generic_string() != ".fbx") { continue; }

		// dat 파일을 생성합니다.
		string strFileName = fsEntry.path().stem().string();
		string strFilePath = fsEntry.path().parent_path().generic_string();
		string strPath = strFilePath + "/" + strFileName + ".dat";

		std::ofstream outFile;
		outFile.open(strPath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

		// 파일이 열리지 않은 경우
		if (!outFile.is_open()) { return E_FAIL; }

		string strModelPath = fsEntry.path().generic_string();
		m_pAIScene = m_oAIImporter.ReadFile(strModelPath.c_str(), m_iFlag);

		// fbx 파일을 열 수 없는 경우
		if (!m_pAIScene)
		{
			outFile.close();
			return E_FAIL;
		}

		// 모델 타입을 씁니다.
		int8 iModelType = (int8)EModelType::EFFECT;
		outFile.write((char*)&iModelType, sizeof(int8));

		SaveEffectMeshes(outFile, fsEntry);

		m_oAIImporter.FreeScene();
		outFile.close();
	}
	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveStaticMeshes(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry)
{
	// 메시의 개수를 씁니다.
	uint32 iNumMeshes = m_pAIScene->mNumMeshes;
	_outFile.write(reinterpret_cast<char*>(&iNumMeshes), sizeof(uint32));

	for (size_t iIndex = 0; iIndex < iNumMeshes; iIndex++)
	{
		const aiMesh* pAIMesh = m_pAIScene->mMeshes[iIndex];

		// 메시의 이름을 씁니다.
		string strMeshName(pAIMesh->mName.C_Str());
		uint32 iMeshNameLength = static_cast<uint32>(strMeshName.length());
		_outFile.write(reinterpret_cast<char*>(&iMeshNameLength), sizeof(uint32));
		_outFile.write(strMeshName.c_str(), iMeshNameLength);

		// 메시의 머테리얼 번호를 씁니다.
		uint32 iMaterialIndex = m_pAIScene->mMeshes[iIndex]->mMaterialIndex;
		_outFile.write(reinterpret_cast<char*>(&iMaterialIndex), sizeof(uint32));

		// 버텍스의 수
		uint32 iNumVertices = pAIMesh->mNumVertices;
		
		// 버텍스를 저장합니다.
		vector<TPositionNormalTexCoordTangent> vecVertices;
		vecVertices.reserve(iNumVertices);
		vecVertices.resize(iNumVertices);

		for (size_t jIndex = 0; jIndex < iNumVertices; jIndex++)
		{
			memcpy(&vecVertices[jIndex].m_vPosition, &pAIMesh->mVertices[jIndex], sizeof(XMFLOAT3));
			XMStoreFloat3(&vecVertices[jIndex].m_vPosition, XMVector3TransformCoord(XMLoadFloat3(&vecVertices[jIndex].m_vPosition), m_matPivot));

			memcpy(&vecVertices[jIndex].m_vNormal, &pAIMesh->mNormals[jIndex], sizeof(XMFLOAT3));
			XMStoreFloat3(&vecVertices[jIndex].m_vNormal, XMVector3TransformNormal(XMLoadFloat3(&vecVertices[jIndex].m_vNormal), m_matPivot));

			memcpy(&vecVertices[jIndex].m_vTexCoord, &pAIMesh->mTextureCoords[0][jIndex], sizeof(XMFLOAT2));

			memcpy(&vecVertices[jIndex].m_vTangent, &pAIMesh->mTangents[jIndex], sizeof(XMFLOAT3));
		}

		// 버텍스를 씁니다.
		uint64 iVertexSize = vecVertices.size();
		_outFile.write(reinterpret_cast<char*>(&iVertexSize), sizeof(uint64));
		_outFile.write(reinterpret_cast<char*>(vecVertices.data()), sizeof(TPositionNormalTexCoordTangent) * iVertexSize);

		// 인덱스의 수
		uint32 iNumIndices = pAIMesh->mNumFaces * 3;

		// 인덱스를 저장합니다.
		vector<uint32> vecIndices;
		vecIndices.reserve(iNumIndices);
		vecIndices.resize(iNumIndices);

		uint32 iIndexCounter = 0;
		for (size_t jIndex = 0; jIndex < pAIMesh->mNumFaces; jIndex++)
		{
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[0];
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[1];
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[2];
		}

		// 인덱스를 씁니다.
		uint64 iIndexSize = vecIndices.size();
		_outFile.write(reinterpret_cast<char*>(&iIndexSize), sizeof(uint64));
		_outFile.write(reinterpret_cast<char*>(&vecIndices[0]), sizeof(uint32) * iIndexSize);
	}

	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveBones(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry)
{
	m_vecBoneInfos.clear();
	m_vecBoneInfos.shrink_to_fit();

	RecursiveSaveBones(m_pAIScene->mRootNode, -1);

	uint32 iBoneInfoSize = static_cast<uint32>(m_vecBoneInfos.size());
	_outFile.write(reinterpret_cast<char*>(&iBoneInfoSize), sizeof(int32));

	for (const auto& tBoneInfo : m_vecBoneInfos)
	{
		// 본의 이름
		uint32 iBoneNameLength = static_cast<uint32>(tBoneInfo.m_strBoneName.length());
		_outFile.write(reinterpret_cast<char*>(&iBoneNameLength), sizeof(uint32));
		_outFile.write(tBoneInfo.m_strBoneName.c_str(), iBoneNameLength);

		// 본의 트랜스폼 행렬을 씁니다.
		Matrix matTransform = tBoneInfo.m_matTransform;
		_outFile.write(reinterpret_cast<char*>(&matTransform), sizeof(Matrix));

		// 부모 본의 번호를 씁니다.
		int32 iParentBone = tBoneInfo.m_iParentBone;
		_outFile.write(reinterpret_cast<char*>(&iParentBone), sizeof(int32));
	}

	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveSkeletalMeshes(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry)
{
	// 메시의 개수를 씁니다.
	uint32 iNumMeshes = m_pAIScene->mNumMeshes;
	_outFile.write(reinterpret_cast<char*>(&iNumMeshes), sizeof(uint32));

	/********************
		스켈레탈 메시
	********************/
	for (uint32 iIndex = 0; iIndex < iNumMeshes; iIndex++)
	{
		const aiMesh* pAIMesh = m_pAIScene->mMeshes[iIndex];

		// 메시의 이름을 씁니다.
		string strMeshName(pAIMesh->mName.C_Str());
		uint32 iMeshNameLength = static_cast<uint32>(strMeshName.length());
		_outFile.write(reinterpret_cast<char*>(&iMeshNameLength), sizeof(uint32));
		_outFile.write(strMeshName.c_str(), iMeshNameLength);

		// 메시의 머테리얼 번호를 씁니다.
		uint32 iMaterialIndex = m_pAIScene->mMeshes[iIndex]->mMaterialIndex;
		_outFile.write(reinterpret_cast<char*>(&iMaterialIndex), sizeof(uint32));

		/********************
			버텍스
		********************/
		uint32 iNumVertices = pAIMesh->mNumVertices;

		// 버텍스를 저장합니다.
		vector<TPositionNormalTexCoordTangentBlend> vecVertices;
		vecVertices.reserve(iNumVertices);
		vecVertices.resize(iNumVertices);

		for (uint32 jIndex = 0; jIndex < iNumVertices; jIndex++)
		{
			memcpy(&vecVertices[jIndex].m_vPosition, &pAIMesh->mVertices[jIndex], sizeof(XMFLOAT3));
			memcpy(&vecVertices[jIndex].m_vNormal, &pAIMesh->mNormals[jIndex], sizeof(XMFLOAT3));
			memcpy(&vecVertices[jIndex].m_vTexCoord, &pAIMesh->mTextureCoords[0][jIndex], sizeof(XMFLOAT2));
			memcpy(&vecVertices[jIndex].m_vTangent, &pAIMesh->mTangents[jIndex], sizeof(XMFLOAT3));
		}

		// 본의 개수를 씁니다.
		uint32 iNumBones = pAIMesh->mNumBones;
		_outFile.write(reinterpret_cast<char*>(&iNumBones), sizeof(uint32));

		for (uint32 jIndex = 0; jIndex < iNumBones; jIndex++)
		{
			const aiBone* pAIBone = pAIMesh->mBones[jIndex];

			// 본의 이름을 씁니다.
			string strBoneName(pAIBone->mName.C_Str());
			uint32 iBoneNameLength = static_cast<uint32>(strBoneName.length());
			_outFile.write(reinterpret_cast<char*>(&iBoneNameLength), sizeof(uint32));
			_outFile.write(strBoneName.c_str(), iBoneNameLength);

			// 본의 오프셋 행렬을 씁니다.
			Matrix matOffset = Matrix::Identity;
			memcpy(&matOffset, &pAIBone->mOffsetMatrix, sizeof(Matrix));
			matOffset.Transpose(matOffset);
			_outFile.write(reinterpret_cast<char*>(&matOffset), sizeof(Matrix));

			for (uint32 kIndex = 0; kIndex < pAIBone->mNumWeights; ++kIndex)
			{
				if (vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendWeights.x == 0.0f)
				{
					vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendIndices.x = jIndex;
					vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendWeights.x = pAIBone->mWeights[kIndex].mWeight;
				}
				else if (vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendWeights.y == 0.0f)
				{
					vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendIndices.y = jIndex;
					vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendWeights.y = pAIBone->mWeights[kIndex].mWeight;
				}
				else if (vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendWeights.z == 0.0f)
				{
					vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendIndices.z = jIndex;
					vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendWeights.z = pAIBone->mWeights[kIndex].mWeight;
				}
				else if (vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendWeights.w == 0.0f)
				{
					vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendIndices.w = jIndex;
					vecVertices[pAIBone->mWeights[kIndex].mVertexId].m_vBlendWeights.w = pAIBone->mWeights[kIndex].mWeight;
				}
			}
		}

		// 버텍스의 개수와 데이터를 씁니다.
		uint64 iVertexSize = vecVertices.size();
		_outFile.write(reinterpret_cast<char*>(&iVertexSize), sizeof(uint64));
		_outFile.write(reinterpret_cast<char*>(vecVertices.data()), sizeof(TPositionNormalTexCoordTangentBlend) * iVertexSize);


		/********************
			인덱스
		********************/ 
		uint32 iNumIndices = pAIMesh->mNumFaces * 3;

		// 인덱스를 저장합니다.
		vector<uint32> vecIndices;
		vecIndices.reserve(iNumIndices);
		vecIndices.resize(iNumIndices);

		uint32 iIndexCounter = 0;
		for (uint32 jIndex = 0; jIndex < pAIMesh->mNumFaces; jIndex++)
		{
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[0];
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[1];
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[2];
		}

		// 인덱스의 개수와 데이터를 씁니다.
		uint64 iIndexSize = vecIndices.size();
		_outFile.write(reinterpret_cast<char*>(&iIndexSize), sizeof(uint64));
		_outFile.write(reinterpret_cast<char*>(&vecIndices[0]), sizeof(uint32) * iIndexSize);
	}

	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveEffectMeshes(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry)
{
	// 메시의 개수를 씁니다.
	uint32 iNumMeshes = m_pAIScene->mNumMeshes;
	_outFile.write(reinterpret_cast<char*>(&iNumMeshes), sizeof(uint32));

	for (size_t iIndex = 0; iIndex < iNumMeshes; iIndex++)
	{
		const aiMesh* pAIMesh = m_pAIScene->mMeshes[iIndex];

		// 메시의 이름을 씁니다.
		string strMeshName(pAIMesh->mName.C_Str());
		uint32 iMeshNameLength = static_cast<uint32>(strMeshName.length());
		_outFile.write(reinterpret_cast<char*>(&iMeshNameLength), sizeof(uint32));
		_outFile.write(strMeshName.c_str(), iMeshNameLength);

		// 메시의 머테리얼 번호를 씁니다.
		uint32 iMaterialIndex = m_pAIScene->mMeshes[iIndex]->mMaterialIndex;
		_outFile.write(reinterpret_cast<char*>(&iMaterialIndex), sizeof(uint32));

		// 버텍스의 수
		uint32 iNumVertices = pAIMesh->mNumVertices;

		// 버텍스를 저장합니다.
		vector<TPositionNormalTexCoordTangent> vecVertices;
		vecVertices.reserve(iNumVertices);
		vecVertices.resize(iNumVertices);

		for (size_t jIndex = 0; jIndex < iNumVertices; jIndex++)
		{
			memcpy(&vecVertices[jIndex].m_vPosition, &pAIMesh->mVertices[jIndex], sizeof(XMFLOAT3));
			XMStoreFloat3(&vecVertices[jIndex].m_vPosition, XMVector3TransformCoord(XMLoadFloat3(&vecVertices[jIndex].m_vPosition), m_matPivot));

			memcpy(&vecVertices[jIndex].m_vNormal, &pAIMesh->mNormals[jIndex], sizeof(XMFLOAT3));
			XMStoreFloat3(&vecVertices[jIndex].m_vNormal, XMVector3TransformNormal(XMLoadFloat3(&vecVertices[jIndex].m_vNormal), m_matPivot));

			memcpy(&vecVertices[jIndex].m_vTexCoord, &pAIMesh->mTextureCoords[0][jIndex], sizeof(XMFLOAT2));

			memcpy(&vecVertices[jIndex].m_vTangent, &pAIMesh->mTangents[jIndex], sizeof(XMFLOAT3));
		}

		// 버텍스를 씁니다.
		uint64 iVertexSize = vecVertices.size();
		_outFile.write(reinterpret_cast<char*>(&iVertexSize), sizeof(uint64));
		_outFile.write(reinterpret_cast<char*>(vecVertices.data()), sizeof(TPositionNormalTexCoordTangent) * iVertexSize);

		// 인덱스의 수
		uint32 iNumIndices = pAIMesh->mNumFaces * 3;

		// 인덱스를 저장합니다.
		vector<uint32> vecIndices;
		vecIndices.reserve(iNumIndices);
		vecIndices.resize(iNumIndices);

		uint32 iIndexCounter = 0;
		for (size_t jIndex = 0; jIndex < pAIMesh->mNumFaces; jIndex++)
		{
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[0];
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[1];
			vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[2];
		}

		// 인덱스를 씁니다.
		uint64 iIndexSize = vecIndices.size();
		_outFile.write(reinterpret_cast<char*>(&iIndexSize), sizeof(uint64));
		_outFile.write(reinterpret_cast<char*>(&vecIndices[0]), sizeof(uint32) * iIndexSize);
	}

	return S_OK;
}

HRESULT Parser::CASSIMPManager::RecursiveSaveBones(aiNode* _pAINode, int32 _iParentBone)
{
	FBoneInfo tBoneInfo;

	// 본의 이름을 저장합니다.
	string strBoneName(_pAINode->mName.C_Str());
	tBoneInfo.m_strBoneName = strBoneName;

	// 본의 트랜스폼 행렬에 피벗 행렬을 곱합니다.
	Matrix matTransform = Matrix::Identity;
	memcpy(&matTransform, &_pAINode->mTransformation, sizeof(Matrix));

	if (_iParentBone == -1)
	{
		matTransform *= m_matPivot;
		matTransform.Transpose(matTransform);
	}
	else
	{
		matTransform.Transpose(matTransform);
	}
	tBoneInfo.m_matTransform = matTransform;

	// 부모 본 인덱스를 저장합니다.
	tBoneInfo.m_iParentBone = _iParentBone;

	m_vecBoneInfos.push_back(tBoneInfo);
	int32 iParentBone = static_cast<int32>(m_vecBoneInfos.size()) - 1;

	for (uint32 iIndex = 0; iIndex < _pAINode->mNumChildren; iIndex++)
	{
		RecursiveSaveBones(_pAINode->mChildren[iIndex], iParentBone);
	}
	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveMaterials(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry)
{
	string strParentPath = _fsEntry.path().parent_path().generic_string();

	// 머테리얼의 개수를 씁니다.
	uint32 iNumMaterials = m_pAIScene->mNumMaterials;
	_outFile.write(reinterpret_cast<char*>(&iNumMaterials), sizeof(uint32));

	for (uint32 iMaterialIndex = 0; iMaterialIndex < iNumMaterials; iMaterialIndex++)
	{
		const aiMaterial* pAIMaterial = m_pAIScene->mMaterials[iMaterialIndex];

		// 기본 색상을 씁니다.
		aiColor4D vColor;
		if (AI_SUCCESS == aiGetMaterialColor(pAIMaterial, AI_MATKEY_COLOR_DIFFUSE, &vColor))
		{
			Vector4 vBaseColor = { vColor.r, vColor.g, vColor.b, vColor.a };
			_outFile.write(reinterpret_cast<char*>(&vBaseColor), sizeof(Vector4));
		}
		

		for (int32 jIndex = 0; jIndex < AI_TEXTURE_TYPE_MAX; jIndex++)
		{
			// j번째 텍스처를 불러옵니다.
			aiString aiStrTextureFilePath;
			if (FAILED(pAIMaterial->GetTexture((aiTextureType)jIndex, 0, &aiStrTextureFilePath)))
			{
				int32 iNan = -1;
				_outFile.write(reinterpret_cast<char*>(&iNan), sizeof(int32));
				continue;
			}

			string strTextureFileNameExtenstion = filesystem::path(aiStrTextureFilePath.C_Str()).filename().generic_string();
			string strTextureFilePath = strParentPath + "/" + strTextureFileNameExtenstion;

			// 텍스처 번호를 씁니다.
			_outFile.write(reinterpret_cast<char*>(&jIndex), sizeof(int32));
			
			// 텍스처 경로의 길이와 텍스쳐 경로를 씁니다.
			uint32 iTextureFilePathLength = static_cast<uint32>(strTextureFilePath.length());
			_outFile.write(reinterpret_cast<char*>(&iTextureFilePathLength), sizeof(uint32));
			_outFile.write(strTextureFilePath.c_str(), iTextureFilePathLength);
		}
	}
	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveAnimations(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry)
{
	// 애니메이션의 개수를 씁니다.
	uint32 iNumAnimations = m_pAIScene->mNumAnimations;
	_outFile.write(reinterpret_cast<char*>(&iNumAnimations), sizeof(uint32));

	for (size_t iIndex = 0; iIndex < iNumAnimations; ++iIndex)
	{
		const aiAnimation* pAIAnimation = m_pAIScene->mAnimations[iIndex];
		
		// 애니메이션의 이름을 씁니다.
		string strAnimationName(pAIAnimation->mName.C_Str());
		uint32 iAnimationNameLength = static_cast<uint32>(strAnimationName.length());
		_outFile.write(reinterpret_cast<char*>(&iAnimationNameLength), sizeof(uint32));
		_outFile.write(strAnimationName.c_str(), iAnimationNameLength);

		// 애니메이션 재생 시간을 씁니다.
		double dDuration = pAIAnimation->mDuration;
		_outFile.write(reinterpret_cast<char*>(&dDuration), sizeof(double));

		// 애니메이션 초당 틱 수를 씁니다.
		double dTickPerSecond = pAIAnimation->mTicksPerSecond;
		_outFile.write(reinterpret_cast<char*>(&dTickPerSecond), sizeof(double));

		// 애니메이션 채널의 수(본의 수)를 씁니다.
		uint32 iNumChannels = pAIAnimation->mNumChannels;
		_outFile.write(reinterpret_cast<char*>(&iNumChannels), sizeof(uint32));

		for (uint32 jIndex = 0; jIndex < iNumChannels; ++jIndex)
		{
			const aiNodeAnim* pAIChannel = pAIAnimation->mChannels[jIndex];

			// 채널의 이름을 씁니다.
			string strChannelName(pAIChannel->mNodeName.C_Str());
			uint32 iChannelNameLength = static_cast<uint32>(strChannelName.length());
			_outFile.write(reinterpret_cast<char*>(&iChannelNameLength), sizeof(uint32));
			_outFile.write(strChannelName.c_str(), iChannelNameLength);

			/*
			if (umapBoneIndices.find(strChannelName) == umapBoneIndices.end()) { CHECKF(false, L"Channel name is diffrent."); return E_FAIL; }

			// 채널의 본 인덱스를 씁니다.
			int32 iBoneIndex = umapBoneIndices[strChannelName];
			_outFile.write(reinterpret_cast<char*>(&iBoneIndex), sizeof(int32));
			*/

			// 키프레임의 최대 개수를 씁니다.
			uint32 iNumKeyFrames = std::max({ pAIChannel->mNumScalingKeys, pAIChannel->mNumRotationKeys, pAIChannel->mNumPositionKeys });
			_outFile.write(reinterpret_cast<char*>(&iNumKeyFrames), sizeof(uint32));

			Vector3 vScale = Vector3::One;
			Vector4 vRotate = Vector4::Zero;
			Vector3 vTranslate = Vector3::Zero;

			vector<FKeyFrame> vecKeyFrames;
			vecKeyFrames.reserve(iNumKeyFrames);

			for (uint32 kIndex = 0; kIndex < iNumKeyFrames; kIndex++)
			{
				FKeyFrame tKeyFrame;

				if (kIndex < pAIChannel->mNumScalingKeys)
				{
					memcpy(&vScale, &pAIChannel->mScalingKeys[kIndex].mValue, sizeof(Vector3));
					tKeyFrame.m_dTime = pAIChannel->mScalingKeys[kIndex].mTime;
				}

				if (kIndex < pAIChannel->mNumRotationKeys)
				{
					vRotate.x = pAIChannel->mRotationKeys[kIndex].mValue.x;
					vRotate.y = pAIChannel->mRotationKeys[kIndex].mValue.y;
					vRotate.z = pAIChannel->mRotationKeys[kIndex].mValue.z;
					vRotate.w = pAIChannel->mRotationKeys[kIndex].mValue.w;
					tKeyFrame.m_dTime = pAIChannel->mRotationKeys[kIndex].mTime;
				}

				if (kIndex < pAIChannel->mNumPositionKeys)
				{
					memcpy(&vTranslate, &pAIChannel->mPositionKeys[kIndex].mValue, sizeof(Vector3));
					tKeyFrame.m_dTime = pAIChannel->mPositionKeys[kIndex].mTime;
				}

				tKeyFrame.m_vScale = vScale;
				tKeyFrame.m_vRotate = vRotate;
				tKeyFrame.m_vTranslate = vTranslate;

				// 키프레임을 저장합니다.
				vecKeyFrames.emplace_back(tKeyFrame);
			}

			// 키프레임을 씁니다.
			_outFile.write(reinterpret_cast<char*>(vecKeyFrames.data()), sizeof(FKeyFrame) * iNumKeyFrames);
		}

	}
	return S_OK;
}

HRESULT Parser::CASSIMPManager::SaveNaviMeshes(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry)
{
	// 메시의 개수를 씁니다.
	uint32 iNumMeshes = m_pAIScene->mNumMeshes;
	_outFile.write(reinterpret_cast<char*>(&iNumMeshes), sizeof(uint32));

	CHECK(iNumMeshes == 1);
	const aiMesh* pAIMesh = m_pAIScene->mMeshes[0];

	// 메시의 이름을 씁니다.
	string strMeshName(pAIMesh->mName.C_Str());
	uint32 iMeshNameLength = static_cast<uint32>(strMeshName.length());
	_outFile.write(reinterpret_cast<char*>(&iMeshNameLength), sizeof(uint32));
	_outFile.write(strMeshName.c_str(), iMeshNameLength);

	// 버텍스의 수
	uint32 iNumVertices = pAIMesh->mNumVertices;

	// 버텍스를 저장합니다.
	vector<TPosition> vecVertices;
	vecVertices.reserve(iNumVertices);
	vecVertices.resize(iNumVertices);

	for (size_t jIndex = 0; jIndex < iNumVertices; jIndex++)
	{
		memcpy(&vecVertices[jIndex].m_vPosition, &pAIMesh->mVertices[jIndex], sizeof(XMFLOAT3));
		XMStoreFloat3(&vecVertices[jIndex].m_vPosition, XMVector3TransformCoord(XMLoadFloat3(&vecVertices[jIndex].m_vPosition), m_matPivot));
	}

	// 버텍스를 씁니다.
	uint64 iVertexSize = vecVertices.size();
	_outFile.write(reinterpret_cast<char*>(&iVertexSize), sizeof(uint64));
	_outFile.write(reinterpret_cast<char*>(vecVertices.data()), sizeof(TPosition) * iVertexSize);

	// 인덱스의 수
	uint32 iNumIndices = pAIMesh->mNumFaces * 3;

	// 인덱스를 저장합니다.
	vector<uint32> vecIndices;
	vecIndices.reserve(iNumIndices);
	vecIndices.resize(iNumIndices);

	uint32 iIndexCounter = 0;
	for (size_t jIndex = 0; jIndex < pAIMesh->mNumFaces; jIndex++)
	{
		vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[0];
		vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[1];
		vecIndices[iIndexCounter++] = pAIMesh->mFaces[jIndex].mIndices[2];
	}

	// 인덱스를 씁니다.
	uint64 iIndexSize = vecIndices.size();
	_outFile.write(reinterpret_cast<char*>(&iIndexSize), sizeof(uint64));
	_outFile.write(reinterpret_cast<char*>(&vecIndices[0]), sizeof(uint32) * iIndexSize);
	return S_OK;
}
