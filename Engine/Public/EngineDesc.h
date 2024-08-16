
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
		// 모델 타입
		EModelType m_eModelType = EModelType::STATIC;

		// L"Hyunwoo"
		// 본 정보, 애니메이션 정보를 추출합니다.
		std::wstring m_wstrModelName = L"";

		// 메시의 개수
		uint32 m_iNumMeshes = 0;

		// "Hyunwoo0" 메시의 버텍스 수, "Hyunwoo1" 메시의 버텍스 수...
		// 메시 정보를 추출합니다.
		std::vector<uint32> m_vecNumVertices;

		// "Hyunwoo0" 메시의 인덱스 수, "Hyunwoo1" 메시의 인덱스 수...
		// 메시 정보를 추출합니다.
		std::vector<uint32> m_vecNumIndices;

		// "Hyunwoo0" 메시의 머테리얼 번호, "Hyunwoo1" 메시의 머테리얼 번호, ... 74
		std::vector<uint32> m_vecMaterialIndices;

		// "Hyunwoo0" 메시의 텍스쳐 수, "Hyunwoo1" 텍스쳐 수... 64
		// 머테리얼 정보를 추출합니다.
		std::vector<uint32> m_vecNumTextures;

		// n번째 메시의 텍스처 번호
		std::vector<std::vector<uint32>> m_vecTextureIndices;

		// n번째 메시의 기본 색상
		std::vector<Vector4> m_vecBaseColors;
	};
}