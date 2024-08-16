#pragma once

namespace Engine
{
	class CSkeletalMeshData;
	class CEffectMeshData;

	class CSceneComponent;
	class CVertexShader;
	class CPixelShader;
	class CConstantBuffer;
	class CTexture;
	class CSampler;

	class CMeshShader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CMeshShader() = default;

		virtual ~CMeshShader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CMeshShader> Create
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			const std::shared_ptr<CSkeletalMeshData>& _spSkeletalMeshData = nullptr,
			const std::shared_ptr<CEffectMeshData>& _spEffectMeshData = nullptr,
			const std::wstring& _wstrModelDesc = L"",
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L""
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			const std::shared_ptr<CSkeletalMeshData>& _spSkeletalMeshData = nullptr,
			const std::shared_ptr<CEffectMeshData>& _spEffectMeshData = nullptr,
			const std::wstring& _wstrModelDesc = L"",
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L""
		);

		int32 Tick();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		// �Է� ������
		void IASetInputLayout(uint16 _iMeshIndex);

		void CopyConstantBuffers(uint16 _iMeshIndex);

		// ���ؽ� ���̴�
		void VSSetShader(uint16 _iMeshIndex);

		void VSSetConstantBuffers(uint16 _iMeshIndex);

		void VSSetShaderResources(uint16 _iMeshIndex);

		void VSSetSamplers(uint16 _iMeshIndex);

		// �ȼ� ���̴�
		void PSSetShader(uint16 _iMeshIndex);

		void PSSetConstantBuffers(uint16 _iMeshIndex);

		void PSSetShaderResources(uint16 _iMeshIndex);

		void PSSetSamplers(uint16 _iMeshIndex);
		
	/********************
		Getter/Setter
	********************/
	public:
		void ModifyPixelShaderTexture(int32 _iMeshIndex, int32 _iTextureIndex, const std::wstring& _wstrTextureName);

	/********************
		Data Members
	********************/
	private:
		// ���ؽ� ���̴�
		std::vector<std::shared_ptr<CVertexShader>> m_vecVertexShaders;

		// �ؽ��ĵ�
		std::vector<std::vector<std::shared_ptr<CTexture>>> m_vecVSMaterials;

		// ��� ���۵�
		std::vector<std::vector<std::shared_ptr<CConstantBuffer>>> m_vecVSConstantBuffers;

		// ���÷�
		std::vector<std::shared_ptr<CSampler>> m_vecVSSamplers;

	private:
		// �ȼ� ���̴�
		std::vector<std::shared_ptr<CPixelShader>> m_vecPixelShaders;

		// �ؽ��ĵ�
		std::vector<std::vector<std::shared_ptr<CTexture>>> m_vecPSMaterials;

		// ��� ���۵�
		std::vector<std::vector<std::shared_ptr<CConstantBuffer>>> m_vecPSConstantBuffers;

		// ���÷�
		std::vector<std::shared_ptr<CSampler>> m_vecPSSamplers;
	};
}
