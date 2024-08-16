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
		// �Է� ������
		void IASetInputLayout();

		void CopyConstantBuffers();

		// ���ؽ� ���̴�
		void VSSetShader();

		void VSSetConstantBuffers();

		void VSSetShaderResources();

		void VSSetSamplers();

		// �ȼ� ���̴�
		void PSSetShader();

		void PSSetConstantBuffers();

		void PSSetShaderResources(uint32 _iIndex = 0);

		void PSSetMultiShaderResources();

		void PSSetSamplers();

		// ������Ʈ�� ���̴�
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
		// ���ؽ� ���̴�
		std::shared_ptr<CVertexShader> m_spVertexShader = nullptr;

		// �ؽ�ó��
		std::vector<std::shared_ptr<CTexture>> m_vecVSMaterials;

		// ��� ���۵�
		std::vector<std::shared_ptr<CConstantBuffer>> m_vecVSConstantBuffers;

		// ���÷�
		std::shared_ptr<CSampler> m_spVSSampler = nullptr;

	private:
		// �ȼ� ���̴�
		std::shared_ptr<CPixelShader> m_spPixelShader = nullptr;

		// �ؽ�ó��
		std::vector<std::vector<std::shared_ptr<CTexture>>> m_vecPSMaterials;

		// ��� ���۵�
		std::vector<std::shared_ptr<CConstantBuffer>> m_vecPSConstantBuffers;

		// ���÷�
		std::shared_ptr<CSampler> m_spPSSampler = nullptr;

	private:
		// ������Ʈ�� ���̴�
		std::shared_ptr<CGeometryShader> m_spGeometryShader = nullptr;

		// �ؽ�ó��
		std::vector<std::shared_ptr<CTexture>> m_vecGSMaterials;

		// ��� ���۵�
		std::vector<std::shared_ptr<CConstantBuffer>> m_vecGSConstantBuffers;

		// ���÷�
		std::shared_ptr<CSampler> m_spGSSampler = nullptr;
	};
}
