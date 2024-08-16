
/********************
	Description
********************/
namespace Engine
{
	// Shader Description
	struct FShaderDesc
	{
	public:
		EShaderType m_eShaderType = EShaderType::ENUM_END;

		std::vector<std::pair<uint8, std::wstring>> m_vecTextureInfo;

		std::vector<std::pair<uint8, std::wstring>> m_vecSamplerInfo;

		std::vector<std::pair<uint8, std::wstring>> m_vecConstantBufferInfo;
	};

	// Vertex Shader Description
	struct FVertexShaderDesc final : public FShaderDesc
	{
	public:
		std::wstring m_wstrInputLayoutName = L"";

		std::wstring m_wstrVertexShaderName = L"";
	};

	// Geometry Shader Description
	struct FGeometryShaderDesc final : public FShaderDesc
	{
	public:
		std::wstring m_wstrGeometryShaderName = L"";
	};

	// Pixel Shader Description
	struct FPixelShaderDesc final : public FShaderDesc
	{
	public:
		std::wstring m_wstrPixelShaderName = L"";
	};


	// Model Description
	struct FModelDesc final
	{
		// �� Ÿ��
		EModelType m_eModelType = EModelType::STATIC;

		// L"Hyunwoo"
		// �� ����, �ִϸ��̼� ������ �����մϴ�.
		std::wstring m_wstrModelName = L"";

		// �޽��� ����
		uint32 m_iNumMeshes = 0;

		// "Hyunwoo0" �޽��� ���ؽ� ��, "Hyunwoo1" �޽��� ���ؽ� ��...
		// �޽� ������ �����մϴ�.
		std::vector<uint32> m_vecNumVertices;

		// "Hyunwoo0" �޽��� �ε��� ��, "Hyunwoo1" �޽��� �ε��� ��...
		// �޽� ������ �����մϴ�.
		std::vector<uint32> m_vecNumIndices;

		// "Hyunwoo0" �޽��� ���׸��� ��ȣ, "Hyunwoo1" �޽��� ���׸��� ��ȣ, ... 74
		std::vector<uint32> m_vecMaterialIndices;

		// "Hyunwoo0" �޽��� �ؽ��� ��, "Hyunwoo1" �ؽ��� ��... 64
		// ���׸��� ������ �����մϴ�.
		std::vector<uint32> m_vecNumTextures;

		// n��° �޽��� �ؽ�ó ��ȣ
		std::vector<std::vector<uint32>> m_vecTextureIndices;

		// n��° �޽��� �⺻ ����
		std::vector<Vector4> m_vecBaseColors;
	};
}