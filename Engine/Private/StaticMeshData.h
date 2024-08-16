#pragma once

namespace Engine
{
	class CSceneComponent;
	class CMeshBuffer;
	class CMeshShader;

	class CStaticMeshData final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CStaticMeshData() = default;

		virtual ~CStaticMeshData() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CStaticMeshData> Create
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			const std::wstring& _wstrModelDesc = L"",
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L""
		);

		HRESULT Initialize
		(
			const std::shared_ptr<CSceneComponent>& _spOwnerComponent,
			const std::wstring& _wstrModelDesc = L"",
			const std::wstring& _wstrVertexShaderDesc = L"",
			const std::wstring& _wstrPixelShaderDesc = L""
		);

		int32 Tick();

		void Render();

		void RenderShadow();

		void Release();
		
		void Clear();

	/********************
		Getter/Setter
	********************/
	public:
		void SetMeshBuffer(std::shared_ptr<CMeshBuffer> _spMeshBuffer) { m_spMeshBuffer = _spMeshBuffer; }

		std::shared_ptr<CMeshBuffer> GetMeshBuffer() const { return m_spMeshBuffer; }
		
		void SetMeshShader(std::shared_ptr<CMeshShader> _spMeshShader) { m_spMeshShader = _spMeshShader; }

		std::shared_ptr<CMeshShader> GetMeshShader() const { return m_spMeshShader; }

		const std::wstring& GetModelDesc() { return m_wstrStaticModelDesc; }
		
	/********************
		Methods
	********************/
	public:
		HRESULT ChangeModelDesc(const std::wstring& _wstrModelDesc);

		// HRESULT ChangeVertexShader(const std::wstring& _wstrVertexShaderDesc);

		// HRESULT ChangePixelShader(const std::wstring& _wstrPixelShaderDesc);

	/********************
		Data Members
	********************/
	private:
		// �� �����͸� ������ ������Ʈ
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

	private:
		// ���� �̸�
		std::wstring m_wstrStaticModelDesc = L"";

		// �� ���� ǥ���ϴ� �޽��� ����
		uint16 m_iNumMeshes = 0;

		// �� ���� ǥ���ϴ� �޽õ�
		std::shared_ptr<CMeshBuffer> m_spMeshBuffer = nullptr;

		// �� ���� ǥ���ϴ� ���̴���
		std::shared_ptr<CMeshShader> m_spMeshShader = nullptr;

		std::shared_ptr<CMeshShader> m_spShadowMeshShader = nullptr;
	};
}
