#pragma once

namespace Engine
{
	class CDeviceManager;
	class CEffectHandler;
	class CViewHandler;

	class CEffectLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEffectLoader() = default;

		virtual ~CEffectLoader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CEffectLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT LoadEffectMeshFromFile();

		HRESULT LoadEffectMeshes(std::ifstream& _inFile, std::shared_ptr<FModelDesc>& _spModelDesc, const std::filesystem::directory_entry& _fsEntry);
		
		HRESULT LoadEffectMeshDataFromFile();

		HRESULT LoadEffectMeshData(std::ifstream& _inFile, std::shared_ptr<FMeshEffectDataGroupProperty>& _spMeshEffectGroup, const std::filesystem::directory_entry& _fsEntry);

	private:
		HRESULT CreateVertexBuffer();

		HRESULT CreateIndexBuffer();
		
		HRESULT CreateEffectShaderResourceViewFromFile();
		
	/********************
		Getter/Setter
	********************/
	public:
		int32 GetNumVertices(EModelType _eModelType, const std::wstring& _wstrVertexBufferName);

		int32 GetNumIndices(const std::wstring& _wstrIndexBufferName);

	/********************
		Data Members
	********************/
	private:
		// �޽� ���ؽ� �����͵�
		std::unordered_map<std::wstring, std::vector<TPositionNormalTexCoordTangent>> m_umapEffectMeshVertices;

		// �޽� �ε��� �����͵�
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapEffectMeshIndices;

		// ���� ���ؽ� �����͵�
		std::unordered_map<std::wstring, std::vector<TPositionTexCoord2>> m_umapEffectPrimitiveVertices;

		// ���� �ε��� �����͵�
		std::unordered_map<std::wstring, std::vector<uint32>> m_umapEffectPrimitiveIndices;

	private:
		std::weak_ptr<CDeviceManager> m_wpDeviceManager;

		std::weak_ptr<CEffectHandler> m_wpEffectHandler;

		std::string m_strEffectModelFilePath = "../../Resource/Meshes/Effect/";

		std::wstring m_wstrEffectViewFilePath = L"../../Resource/Textures/Effect/";

		std::wstring m_wstrEffectMeshDataFilePath = L"../../Resource/Editor/Effects/Mesh/";
	};
}
