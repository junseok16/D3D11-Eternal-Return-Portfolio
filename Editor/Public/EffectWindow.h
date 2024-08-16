#pragma once

namespace Engine
{
	class CShaderHandler;
	class CEffectHandler;
	class CEffectMeshData;
	class CEffectParticleData;
	class CEffectComponent;
}

namespace Editor
{
	class CEffectTester;
	class CIMGUIManager;
	class CEditorLevel;

	class CEffectWindow final
	{
	public:
		explicit CEffectWindow() = default;

		virtual ~CEffectWindow() = default;

	public:
		static std::shared_ptr<CEffectWindow> Create(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager);

		HRESULT Initialize(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager);

		int32 Tick();

		void Release();

	private:
		void TickSeparaterMeshEffect();

		void TickSeparaterParticleEffect();

	private:
		std::weak_ptr<CEffectTester> m_wpEffectTester;

		std::weak_ptr<CEffectComponent> m_wpEffectComponent;

		std::weak_ptr<CIMGUIManager> m_wpIMGUIManager;

		std::weak_ptr<CEffectHandler> m_wpEffectHandler;

		std::weak_ptr<CShaderHandler> m_wpShaderHandler;

		std::weak_ptr<CEditorLevel> m_wpEditorLevel;

	/************************
		이펙트 메시
	************************/
	public:
		// 이펙트 메시 데이터 목록들
		std::vector<std::pair<wstring, std::shared_ptr<CEffectMeshData>>> m_vecEffectMeshData;

		int32 m_iCurEffectMeshDataIndex = -1;

		std::shared_ptr<CEffectMeshData> m_spCurEffectMeshData = nullptr;
		
	/************************
		이펙트 파티클
	***********************/
	public:
		// 이펙트 파티클 데이터 목록들
		std::vector<std::pair<std::wstring, std::shared_ptr<CEffectParticleData>>> m_vecEffectParticleData;

		int32 m_iCurEffectParticleDataIndex = -1;

		std::shared_ptr<CEffectParticleData> m_spCurEffectParticleData = nullptr;

	/************************
		메시 이펙트
	************************/
	public:
		// 이펙트 메시 데이터 이름
		char m_chEffectMeshDataName[MAX_PATH]{ NULL };

		// 이펙트 메시들
		std::vector<std::pair<std::string, std::shared_ptr<FModelDesc>>> m_vecEffectMeshDescs;

	/************************
		파티클 이펙트 
	************************/
	public:
		// 파티클 이펙트는 메시를 사용하지 않습니다.
		char m_chEffectParticleDataName[MAX_PATH]{ NULL };

		std::vector<std::pair<std::string, std::shared_ptr<FModelDesc>>> m_vecEffectParticleDescs;

	/************************
		메시 이펙트 셰이더
	************************/
	public:
		// 버텍스 셰이더 목록들
		std::vector<std::pair<std::string, std::shared_ptr<FVertexShaderDesc>>> m_vecMeshVSDescs;

		int32 m_iCurMeshVSIndex = -1;

		// 픽셀 셰이더 목록들
		std::vector<std::pair<std::string, std::shared_ptr<FPixelShaderDesc>>> m_vecMeshPSDescs;

		int32 m_iCurMeshPSIndex = -1;
		
	/************************
		파티클 이펙트 셰이더
	************************/
	public:
		// 버텍스 셰이더 목록들
		std::vector<std::pair<std::string, std::shared_ptr<FVertexShaderDesc>>> m_vecParticleVSDescs;

		int32 m_iCurParticleVSIndex = -1;

		// 픽셀 셰이더 목록들
		std::vector<std::pair<std::string, std::shared_ptr<FPixelShaderDesc>>> m_vecParticlePSDescs;

		int32 m_iCurParticlePSIndex = -1;

	/************************
		메시 이펙트 시간
	************************/
	public:
		// 메시 이펙트 시작 시간
		float m_fMeshStartTime = 0.0f;

		// 메시 이펙트 종료 시간
		float m_fMeshFinishTime = 0.0f;

		// 메시 이펙트 반복 여부
		bool m_bMeshLoop = false;
		
	/************************
		파티클 이펙트 시간
	************************/
	public:
		// 파티클 시작 시간
		float m_fParticleStartPlaySeconds = 0.0f;

		// 파티클 종료 시간
		float m_fParticleFinishPlaySeconds = 0.0f;

		// 파티클 최소 지속시간
		float m_fParticleMinLifeSeconds = 0.0f;

		// 파티클 최대 지속 시간
		float m_fParticleMaxLifeSeconds = 0.0f;

		// 파티클 반복 여부
		bool m_bParticleLoop = false;

	/************************
		메시 이펙트 색상
	************************/
	public:
		// 이펙트 시작 색상
		Vector4 m_vMeshStartColor{ 0.0f, 0.0f, 0.0f, 1.0f };

		// 이펙트 종료 색상
		Vector4 m_vMeshFinishColor{ 1.0f, 1.0f, 1.0f, 1.0f };
		
	/************************
		파티클 이펙트 색상
	************************/
	public:
		Vector4 m_vParticleStartColor{ 0.0f, 0.0f, 0.0f, 1.0f };

		Vector4 m_vParticleFinishColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	/************************
		메시 이펙트 uv
	************************/
	public:
		// 이펙트 uv 사용 여부
		bool m_bUseMeshEffectUV = false;

		// 이펙트 시작 uv
		float m_fMeshStartEffectUV[2]{ 0.0f, 0.0f };

		// 이펙트 종료 uv
		float m_fMeshFinishEffectUV[2]{ 1.0f, 1.0f };

	/************************
		메시 이펙트 마스크
	************************/
	public:
		// 마스크 사용 여부
		bool m_bUseMeshMask = false;

		// 컬러 마스크 사용 여부
		bool m_bUseColorMeshMask = false;

		// 마스크 이미지
		std::vector<std::pair<std::string, ComPtr<ID3D11ShaderResourceView>>> m_vecMeshMasks;

		int32 m_iCurMeshMaskTextureIndex = -1;

		// 마스크 이미지 종횡수
		int32 m_iMeshMaskRowColumn[2]{ 1, 1 };

		// 마스크 uv 재생 속도
		float m_fMeshMaskUVSpeed[2]{ 0.0f, 0.0f };

		// 마스크 uv 최댓값
		float m_fMeshMaskMaxUV[2]{ 1.0f, 1.0f };

	/************************
		메시 이펙트 노이즈
	************************/
	public:
		// 마스크 사용 여부
		bool m_bUseMeshNoise = false;

		// 노이즈 이미지
		std::vector<std::pair<std::string, ComPtr<ID3D11ShaderResourceView>>> m_vecMeshNoises;

		int32 m_iCurMeshNoiseTextureIndex = -1;

		// 노이즈 이미지 종횡수
		int32 m_iMeshNoiseRowColumn[2]{ 1, 1 };

		// 노이즈 uv 재생 속도
		float m_fMeshNoiseUVSpeed[2]{ 0.0f, 0.0f };

		// 노이즈 uv 최댓값
		float m_fMeshNoiseMaxUV[2]{ 1.0f, 1.0f };

	/************************
		메시 이펙트 트랜스폼
	************************/
	public:
		// 이펙트 시작 트랜스폼
		Vector3 m_vMeshStartScale = Vector3::One;

		Vector3 m_vMeshStartRotate = Vector3::Zero;

		Vector3 m_vMeshStartTranslate = Vector3::Zero;

		// 이펙트 종료 트랜스폼
		Vector3 m_vMeshFinishScale = Vector3::One;

		Vector3 m_vMeshFinishRotate = Vector3::Zero;

		Vector3 m_vMeshFinishTranslate = Vector3::Zero;
		
	/******************************
		파티클 이펙트 트랜스폼
	******************************/
	public:
		Vector3 m_vPivot = Vector3::Zero;

		Vector3 m_vCenter = Vector3::Zero;

		Vector3 m_vRange = Vector3::One;

	/*************************************
		메시 이펙트 저장하기, 불러오기
	*************************************/
	public:
		// 파일 이름
		char m_chSaveMeshEffectFileName[MAX_PATH]{ NULL };

		char m_chLoadMeshEffectFileName[MAX_PATH]{ NULL };

		// 파일 경로
		std::string m_strMeshEffectFilePath = "../../Resource/Editor/Effects/Mesh/";
		
	/*************************************
		파티클 이펙트 저장하기, 불러오기
	*************************************/
	public:
		// 파일 이름
		char m_chSaveParticleEffectFileName[MAX_PATH]{ NULL };

		char m_chLoadParticleEffectFileName[MAX_PATH]{ NULL };

		// 파일 경로
		std::string m_strParticleEffectFilePath = "../../Resource/Editor/Effects/Particle/";
	};
}
