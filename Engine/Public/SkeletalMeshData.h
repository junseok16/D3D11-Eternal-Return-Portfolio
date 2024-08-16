#pragma once

namespace Engine
{
	class CSceneComponent;
	class CMeshBuffer;
	class CMeshShader;
	class CMeshBone;
	class CAnimData;
	class CBone;

	class CSkeletalMeshData final : public enable_shared_from_this<CSkeletalMeshData>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSkeletalMeshData() = default;

		virtual ~CSkeletalMeshData() = default;

	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CSkeletalMeshData> Create(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrModelDesc = L"", const std::wstring& _wstrVertexShaderDesc = L"", const std::wstring& _wstrPixelShaderDesc = L"");

		HRESULT Initialize(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrModelDesc = L"", const std::wstring& _wstrVertexShaderDesc = L"", const std::wstring& _wstrPixelShaderDesc = L"");

		int32 Tick(float _fDeltaSeconds);

		void RenderShadow();

		void Render();

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		const shared_ptr<CMeshBuffer>& GetMeshBuffer() const { return m_spMeshBuffer; }

		const shared_ptr<CMeshShader>& GetMeshShader() const { return m_spMeshShader; }

		const shared_ptr<CMeshBone>& GetMeshBone() const { return m_spMeshBone; }
		
		void SetAnimData(const std::shared_ptr<CAnimData>& _spAnimData);
		
		void StopAnimation() { m_bPlayAnimation = false; }

		void PlayAnimation() { m_bPlayAnimation = true; }

	/********************
		Methos
	********************/
	public:
		std::shared_ptr<CBone> FindBone(const std::string& _strBoneName);

		void SetPlayRate(float _fPlayRatio);

	/********************
		Data Members
	********************/
	private:
		// 이 데이터를 소유한 컴포넌트
		std::weak_ptr<CSceneComponent> m_wpOwnerComponent;

		std::weak_ptr<CAnimData> m_wpAnimData;

	private:
		// 이 모델을 표현하는 메시의 개수
		uint16 m_iNumMeshes = 0;

		// 이 모델을 표현하는 메시들
		std::shared_ptr<CMeshBuffer> m_spMeshBuffer = nullptr;

		// 이 모델을 표현하는 셰이더들
		std::shared_ptr<CMeshShader> m_spMeshShader = nullptr;

		std::shared_ptr<CMeshShader> m_spShadowMeshShader = nullptr;

		// 이 모델을 표현하는 본들
		std::shared_ptr<CMeshBone> m_spMeshBone = nullptr;

		bool m_bPlayAnimation = true;
	};
}
