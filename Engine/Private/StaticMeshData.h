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
		// 이 데이터를 소유한 컴포넌트
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

	private:
		// 모델의 이름
		std::wstring m_wstrStaticModelDesc = L"";

		// 이 모델을 표현하는 메시의 개수
		uint16 m_iNumMeshes = 0;

		// 이 모델을 표현하는 메시들
		std::shared_ptr<CMeshBuffer> m_spMeshBuffer = nullptr;

		// 이 모델을 표현하는 셰이더들
		std::shared_ptr<CMeshShader> m_spMeshShader = nullptr;

		std::shared_ptr<CMeshShader> m_spShadowMeshShader = nullptr;
	};
}
