#pragma once

namespace Engine
{
	class CDeviceManager;
	class CModelHandler;
	class CViewHandler;
	class CBone;

	class CModelLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CModelLoader() = default;

		virtual ~CModelLoader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CModelLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT LoadStaticModelFromFile();

		HRESULT LoadSkeletalModelFromFile();

		HRESULT LoadEffectModelFromFile();

	private:
		HRESULT LoadStaticMeshes(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry);

		HRESULT LoadStaticMaterials(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry);

	private:
		HRESULT LoadSkeletalMeshes(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry);
		
		HRESULT LoadSkeletalMaterials(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry);
		
		HRESULT LoadSkeletalBones(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry);

		HRESULT LoadSkeletalAnimations(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry);

	public:
		HRESULT CreateVertexBuffer();

		HRESULT CreateIndexBuffer();

	/********************
		Getter/Setter
	********************/
	public:
		int32 GetNumVertices(EModelType _eModelType, const std::wstring& _wstrVertexBufferName);

		int32 GetNumIndices(const std::wstring& _wstrIndexBufferName);

		Vector3 GetAverageWorldPosition(EModelType _eModelType, const std::wstring& _wstrVertexBufferName);

	/********************
		Data Members
	********************/
	private:
		// 스태틱 모델 버텍스 데이터들
		std::unordered_map<std::wstring, std::vector<TPositionNormalTexCoordTangent>> m_umapStaticVertices;

		// 스켈레탈 모델 버텍스 데이터들
		std::unordered_map<std::wstring, std::vector<TPositionNormalTexCoordTangentBlend>> m_umapSkeletalVertices;

		// 이펙트 메시 버텍스 데이터들
		std::unordered_map<std::wstring, std::vector<TPositionNormalTexCoordTangent>> m_umapEffectMeshVertices;

		// 인덱스 데이터들
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapIndices;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CModelHandler> m_wpModelHandler;

		std::weak_ptr<CViewHandler> m_wpViewHandler;

		std::string m_strStaticModelFilePath = "../../Resource/Meshes/Static/";
		
		std::string m_strSkeletalModelFilePath = "../../Resource/Meshes/Skeletal/";

		std::string m_strEffectModelFilePath = "../../Resource/Meshes/Effect/";
	};
}
