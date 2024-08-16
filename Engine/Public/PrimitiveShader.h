#pragma once

namespace Engine
{
	class CSceneComponent;
	class CPrimitiveMeshData;
	class CVertexShader;
	class CGeometryShader;
	class CPixelShader;
	class CConstantBuffer;
	class CTexture;
	class CSampler;

	class CPrimitiveShader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CPrimitiveShader() = default;

		virtual ~CPrimitiveShader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CPrimitiveShader> Create
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			EPrimitiveType _ePrimitiveType,
			const std::vector<std::wstring>& _vecTextureNames,
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L"",
			const std::wstring & _wstrGeometryShaderDesc = L""
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			EPrimitiveType _ePrimitiveType,
			const std::vector<std::wstring>& _vecTextureNames,
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L"",
			const std::wstring& _wstrGeometryShaderDesc = L""
		);

		int32 Tick();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		// 입력 조립기
		void IASetInputLayout();

		void CopyConstantBuffers();

		// 버텍스 셰이더
		void VSSetShader();

		void VSSetConstantBuffers();

		void VSSetShaderResources();

		void VSSetSamplers();

		// 픽셀 셰이더
		void PSSetShader();

		void PSSetConstantBuffers();

		void PSSetShaderResources(uint32 _iIndex = 0);

		void PSSetMultiShaderResources();

		void PSSetSamplers();

		// 지오메트리 셰이더
		void GSSetShader();

		void GSSetConstantBuffers();

		void GSSetShaderResources();

		void GSSetSamplers();

		void GSUnsetShader();

	public:
		void AddConstantBuffer(const shared_ptr<CConstantBuffer>& _spConstantBuffer);

	/********************
		Data Members
	********************/
	private:
		EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

	private:
		// 버텍스 셰이더
		std::shared_ptr<CVertexShader> m_spVertexShader = nullptr;

		// 텍스처들
		std::vector<std::shared_ptr<CTexture>> m_vecVSMaterials;

		// 상수 버퍼들
		std::vector<std::shared_ptr<CConstantBuffer>> m_vecVSConstantBuffers;

		// 샘플러
		std::shared_ptr<CSampler> m_spVSSampler = nullptr;

	private:
		// 픽셀 셰이더
		std::shared_ptr<CPixelShader> m_spPixelShader = nullptr;

		// 텍스처들
		std::vector<std::vector<std::shared_ptr<CTexture>>> m_vecPSMaterials;

		// 상수 버퍼들
		std::vector<std::shared_ptr<CConstantBuffer>> m_vecPSConstantBuffers;

		// 샘플러
		std::shared_ptr<CSampler> m_spPSSampler = nullptr;

	private:
		// 지오메트리 셰이더
		std::shared_ptr<CGeometryShader> m_spGeometryShader = nullptr;

		// 텍스처들
		std::vector<std::shared_ptr<CTexture>> m_vecGSMaterials;

		// 상수 버퍼들
		std::vector<std::shared_ptr<CConstantBuffer>> m_vecGSConstantBuffers;

		// 샘플러
		std::shared_ptr<CSampler> m_spGSSampler = nullptr;
	};
}
