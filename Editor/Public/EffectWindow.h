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
		����Ʈ �޽�
	************************/
	public:
		// ����Ʈ �޽� ������ ��ϵ�
		std::vector<std::pair<wstring, std::shared_ptr<CEffectMeshData>>> m_vecEffectMeshData;

		int32 m_iCurEffectMeshDataIndex = -1;

		std::shared_ptr<CEffectMeshData> m_spCurEffectMeshData = nullptr;
		
	/************************
		����Ʈ ��ƼŬ
	***********************/
	public:
		// ����Ʈ ��ƼŬ ������ ��ϵ�
		std::vector<std::pair<std::wstring, std::shared_ptr<CEffectParticleData>>> m_vecEffectParticleData;

		int32 m_iCurEffectParticleDataIndex = -1;

		std::shared_ptr<CEffectParticleData> m_spCurEffectParticleData = nullptr;

	/************************
		�޽� ����Ʈ
	************************/
	public:
		// ����Ʈ �޽� ������ �̸�
		char m_chEffectMeshDataName[MAX_PATH]{ NULL };

		// ����Ʈ �޽õ�
		std::vector<std::pair<std::string, std::shared_ptr<FModelDesc>>> m_vecEffectMeshDescs;

	/************************
		��ƼŬ ����Ʈ 
	************************/
	public:
		// ��ƼŬ ����Ʈ�� �޽ø� ������� �ʽ��ϴ�.
		char m_chEffectParticleDataName[MAX_PATH]{ NULL };

		std::vector<std::pair<std::string, std::shared_ptr<FModelDesc>>> m_vecEffectParticleDescs;

	/************************
		�޽� ����Ʈ ���̴�
	************************/
	public:
		// ���ؽ� ���̴� ��ϵ�
		std::vector<std::pair<std::string, std::shared_ptr<FVertexShaderDesc>>> m_vecMeshVSDescs;

		int32 m_iCurMeshVSIndex = -1;

		// �ȼ� ���̴� ��ϵ�
		std::vector<std::pair<std::string, std::shared_ptr<FPixelShaderDesc>>> m_vecMeshPSDescs;

		int32 m_iCurMeshPSIndex = -1;
		
	/************************
		��ƼŬ ����Ʈ ���̴�
	************************/
	public:
		// ���ؽ� ���̴� ��ϵ�
		std::vector<std::pair<std::string, std::shared_ptr<FVertexShaderDesc>>> m_vecParticleVSDescs;

		int32 m_iCurParticleVSIndex = -1;

		// �ȼ� ���̴� ��ϵ�
		std::vector<std::pair<std::string, std::shared_ptr<FPixelShaderDesc>>> m_vecParticlePSDescs;

		int32 m_iCurParticlePSIndex = -1;

	/************************
		�޽� ����Ʈ �ð�
	************************/
	public:
		// �޽� ����Ʈ ���� �ð�
		float m_fMeshStartTime = 0.0f;

		// �޽� ����Ʈ ���� �ð�
		float m_fMeshFinishTime = 0.0f;

		// �޽� ����Ʈ �ݺ� ����
		bool m_bMeshLoop = false;
		
	/************************
		��ƼŬ ����Ʈ �ð�
	************************/
	public:
		// ��ƼŬ ���� �ð�
		float m_fParticleStartPlaySeconds = 0.0f;

		// ��ƼŬ ���� �ð�
		float m_fParticleFinishPlaySeconds = 0.0f;

		// ��ƼŬ �ּ� ���ӽð�
		float m_fParticleMinLifeSeconds = 0.0f;

		// ��ƼŬ �ִ� ���� �ð�
		float m_fParticleMaxLifeSeconds = 0.0f;

		// ��ƼŬ �ݺ� ����
		bool m_bParticleLoop = false;

	/************************
		�޽� ����Ʈ ����
	************************/
	public:
		// ����Ʈ ���� ����
		Vector4 m_vMeshStartColor{ 0.0f, 0.0f, 0.0f, 1.0f };

		// ����Ʈ ���� ����
		Vector4 m_vMeshFinishColor{ 1.0f, 1.0f, 1.0f, 1.0f };
		
	/************************
		��ƼŬ ����Ʈ ����
	************************/
	public:
		Vector4 m_vParticleStartColor{ 0.0f, 0.0f, 0.0f, 1.0f };

		Vector4 m_vParticleFinishColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	/************************
		�޽� ����Ʈ uv
	************************/
	public:
		// ����Ʈ uv ��� ����
		bool m_bUseMeshEffectUV = false;

		// ����Ʈ ���� uv
		float m_fMeshStartEffectUV[2]{ 0.0f, 0.0f };

		// ����Ʈ ���� uv
		float m_fMeshFinishEffectUV[2]{ 1.0f, 1.0f };

	/************************
		�޽� ����Ʈ ����ũ
	************************/
	public:
		// ����ũ ��� ����
		bool m_bUseMeshMask = false;

		// �÷� ����ũ ��� ����
		bool m_bUseColorMeshMask = false;

		// ����ũ �̹���
		std::vector<std::pair<std::string, ComPtr<ID3D11ShaderResourceView>>> m_vecMeshMasks;

		int32 m_iCurMeshMaskTextureIndex = -1;

		// ����ũ �̹��� ��Ⱦ��
		int32 m_iMeshMaskRowColumn[2]{ 1, 1 };

		// ����ũ uv ��� �ӵ�
		float m_fMeshMaskUVSpeed[2]{ 0.0f, 0.0f };

		// ����ũ uv �ִ�
		float m_fMeshMaskMaxUV[2]{ 1.0f, 1.0f };

	/************************
		�޽� ����Ʈ ������
	************************/
	public:
		// ����ũ ��� ����
		bool m_bUseMeshNoise = false;

		// ������ �̹���
		std::vector<std::pair<std::string, ComPtr<ID3D11ShaderResourceView>>> m_vecMeshNoises;

		int32 m_iCurMeshNoiseTextureIndex = -1;

		// ������ �̹��� ��Ⱦ��
		int32 m_iMeshNoiseRowColumn[2]{ 1, 1 };

		// ������ uv ��� �ӵ�
		float m_fMeshNoiseUVSpeed[2]{ 0.0f, 0.0f };

		// ������ uv �ִ�
		float m_fMeshNoiseMaxUV[2]{ 1.0f, 1.0f };

	/************************
		�޽� ����Ʈ Ʈ������
	************************/
	public:
		// ����Ʈ ���� Ʈ������
		Vector3 m_vMeshStartScale = Vector3::One;

		Vector3 m_vMeshStartRotate = Vector3::Zero;

		Vector3 m_vMeshStartTranslate = Vector3::Zero;

		// ����Ʈ ���� Ʈ������
		Vector3 m_vMeshFinishScale = Vector3::One;

		Vector3 m_vMeshFinishRotate = Vector3::Zero;

		Vector3 m_vMeshFinishTranslate = Vector3::Zero;
		
	/******************************
		��ƼŬ ����Ʈ Ʈ������
	******************************/
	public:
		Vector3 m_vPivot = Vector3::Zero;

		Vector3 m_vCenter = Vector3::Zero;

		Vector3 m_vRange = Vector3::One;

	/*************************************
		�޽� ����Ʈ �����ϱ�, �ҷ�����
	*************************************/
	public:
		// ���� �̸�
		char m_chSaveMeshEffectFileName[MAX_PATH]{ NULL };

		char m_chLoadMeshEffectFileName[MAX_PATH]{ NULL };

		// ���� ���
		std::string m_strMeshEffectFilePath = "../../Resource/Editor/Effects/Mesh/";
		
	/*************************************
		��ƼŬ ����Ʈ �����ϱ�, �ҷ�����
	*************************************/
	public:
		// ���� �̸�
		char m_chSaveParticleEffectFileName[MAX_PATH]{ NULL };

		char m_chLoadParticleEffectFileName[MAX_PATH]{ NULL };

		// ���� ���
		std::string m_strParticleEffectFilePath = "../../Resource/Editor/Effects/Particle/";
	};
}
