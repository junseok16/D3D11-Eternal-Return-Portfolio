#pragma once
namespace Parser
{
	struct FBoneInfo
	{
		string m_strBoneName = "";
		Matrix m_matTransform = Matrix::Identity;
		int32 m_iParentBone = -1;
	};

	struct FKeyFrame
	{
		// ���� ƽ�� �ش��ϴ� ũ��, �̵�, ȸ�� ����
		Vector3 m_vScale = Vector3::One;
		Vector4 m_vRotate = Vector4::Zero;
		Vector3 m_vTranslate = Vector3::Zero;
		double m_dTime = 0.0;
	};

	class CASSIMPManager final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CASSIMPManager() = default;

		virtual ~CASSIMPManager() = default;
		
	/********************
		Events
	********************/
	public:
		HRESULT Initialize();

		void Release();

	/********************
		Methods
	********************/
	public:
		HRESULT ConvertFBX2DAT(EModelType _eModelType);

	private:
		HRESULT SaveStaticModel();

		HRESULT SaveSkeletalModel();

		HRESULT SaveNavigationModel();

		HRESULT SaveEffectModel();

	private:
		// �޽�
		HRESULT SaveStaticMeshes(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry);

		HRESULT SaveSkeletalMeshes(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry);

		HRESULT SaveEffectMeshes(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry);

		// ��
		HRESULT SaveBones(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry);

		HRESULT RecursiveSaveBones(aiNode* _pAINode, int32 _iParentBone);

		// ���׸���
		HRESULT SaveMaterials(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry);

		//�ִϸ��̼�
		HRESULT SaveAnimations(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry);
		
		// �׺���̼�
		HRESULT SaveNaviMeshes(std::ofstream& _outFile, const std::filesystem::directory_entry& _fsEntry);

	/********************
		Data Members
	********************/
	private:
		std::vector<FBoneInfo> m_vecBoneInfos;

	private:
		Matrix m_matPivot = Matrix::Identity;

	private:
		uint32 m_iFlag = aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast;

		const aiScene* m_pAIScene = nullptr;
		
		Assimp::Importer m_oAIImporter;

	private:
		std::string m_strStaticModelFilePath = "../../Resource/Meshes/Static/";

		std::string m_strSkeletalModelFilePath = "../../Resource/Meshes/Skeletal/";

		std::string m_strNavigationModelFilePath = "../../Resource/Navigations/Lumia/";

		std::string m_strEffectModelFilePath = "../../Resource/Meshes/Effect/";
	};
}
