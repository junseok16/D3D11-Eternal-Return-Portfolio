#pragma once
namespace Engine
{
	class CMeshBone;
	class CChannel;

	class CAnimation final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CAnimation() = default;

		virtual ~CAnimation() = default;

		explicit CAnimation(const CAnimation& _rhs);
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CAnimation> Create
		(
			const std::string& _strAnimationName,
			double _dDuration,
			double _dTickPerSeconds,
			uint32 _iNumChannels,
			const std::vector<std::shared_ptr<CChannel>>& _vecChannels
		);

		HRESULT Initialize
		(
			const std::string& _strAnimationName,
			double _dDuration,
			double _dTickPerSeconds,
			uint32 _iNumChannels,
			const std::vector<std::shared_ptr<CChannel>>& _vecChannels
		);

		void Release();
		
	/********************
		Methods
	********************/
	public:
		bool RecalcAnimation(float _fDeltaSeconds, float& _fRatio, bool _bLoop = true);

		void ResetAnimation();

	/********************
		Getter/Setter
	********************/
	public:
		void SetMeshBone(const shared_ptr<CMeshBone>& _spMeshBone);
		
		const std::unordered_map<std::string, std::pair<uint32, FKeyFrame>>& GetCurKeyFrames(bool _bLast)
		{
			return _bLast ? m_umapLastKeyFrames : m_umapCurKeyFrames;
		}

		const std::unordered_map<std::string, std::pair<uint32, FKeyFrame>>& GetFirstKeyFrames() { return m_umapFirstKeyFrames; }

	/********************
		Data Members
	********************/
	private:
		// �ִϸ��̼� ��
		uint32 m_iNumAnimations = 0;

		// �ִϸ��̼� �̸�
		string m_strAnimationName = "";

		// �ִϸ��̼� �ε���
		uint32 m_iAnimationIndex = 0;

		// �ִϸ��̼� ��� �ð�(��)
		double m_dDuration = 0.0;

		// �ʴ� ƽ ��
		double m_dTickPerSeconds = 0.0;

		// ���� �ִϸ��̼��� ��� ���� ƽ
		double m_dCurTick = 0.0;

		// ������ �ִϸ��̼����� ����
		bool m_bLast = false;

		// ä���� ��
		uint32 m_iNumChannels = 0;

		// �� �ִϸ��̼ǿ� ������ �޴� ��� ä�ε�
		std::vector<std::shared_ptr<CChannel>> m_vecChannels;

		// ä�ε��� ����ϰ� �ִ� ���� Ű������ ��ȣ
		vector<uint32> m_vecCurKeyFrames;

		// ä�� �̸��� ä���� ���� Ű������
		std::unordered_map<std::string, std::pair<uint32, FKeyFrame>> m_umapCurKeyFrames;

		// ä�� �̸��� ä���� ù ��° Ű������
		std::unordered_map<std::string, std::pair<uint32, FKeyFrame>> m_umapFirstKeyFrames;

		// ä�� �̸��� ä���� ������ Ű������
		std::unordered_map<std::string, std::pair<uint32, FKeyFrame>> m_umapLastKeyFrames;
	};
}
