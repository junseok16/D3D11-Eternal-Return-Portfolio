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
		// 애니메이션 수
		uint32 m_iNumAnimations = 0;

		// 애니메이션 이름
		string m_strAnimationName = "";

		// 애니메이션 인덱스
		uint32 m_iAnimationIndex = 0;

		// 애니메이션 재생 시간(초)
		double m_dDuration = 0.0;

		// 초당 틱 수
		double m_dTickPerSeconds = 0.0;

		// 현재 애니메이션이 재생 중인 틱
		double m_dCurTick = 0.0;

		// 마지막 애니메이션인지 여부
		bool m_bLast = false;

		// 채널의 수
		uint32 m_iNumChannels = 0;

		// 이 애니메이션에 영향을 받는 모든 채널들
		std::vector<std::shared_ptr<CChannel>> m_vecChannels;

		// 채널들이 재생하고 있는 현재 키프레임 번호
		vector<uint32> m_vecCurKeyFrames;

		// 채널 이름과 채널의 현재 키프레임
		std::unordered_map<std::string, std::pair<uint32, FKeyFrame>> m_umapCurKeyFrames;

		// 채널 이름과 채널의 첫 번째 키프레임
		std::unordered_map<std::string, std::pair<uint32, FKeyFrame>> m_umapFirstKeyFrames;

		// 채널 이름과 채널의 마지막 키프레임
		std::unordered_map<std::string, std::pair<uint32, FKeyFrame>> m_umapLastKeyFrames;
	};
}
