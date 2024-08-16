#pragma once

namespace Engine
{
	class CMeshBone;

	class CChannel final
	{
	public:
		explicit CChannel() = default;

		virtual ~CChannel() = default;

		explicit CChannel(const CChannel& _rhs);

	public:
		static std::shared_ptr<CChannel> Create
		(
			const std::string& _strChannelName,
			uint32 _iBoneIndex,
			uint32 _iNumKeyFrames,
			const std::vector<FKeyFrame>& _vecKeyFrames
		);

		HRESULT Initialize
		(
			const std::string& _strChannelName,
			uint32 _iBoneIndex,
			uint32 _iNumKeyFrames,
			const std::vector<FKeyFrame>& _vecKeyFrames
		);

		void Release();

	public:
		void RecalcChannel(double _dCurTick, uint32& _iCurKeyFrame, bool _bReset);

		void SetMeshBone(const std::shared_ptr<CMeshBone>& _spMeshBone) { m_wpMeshBone = _spMeshBone; }

		const string& GetChannelName() { return m_strChannelName; }

		const FKeyFrame GetCurKeyFrame() { return m_tCurKeyFrame; }

		const uint32 GetBoneIndex() { return m_iBoneIndex; }

		const FKeyFrame GetFirstKeyFrame() { return m_vecKeyFrames.front(); }

		const FKeyFrame GetLastKeyFrame() { return m_vecKeyFrames.back(); }

	private:
		// 채널의 이름
		string m_strChannelName = "";

		// 이 채널과 대응되는 본의 인덱스
		uint32 m_iBoneIndex = 0;

		// 키프레임의 수
		uint32 m_iNumKeyFrames = 0;

		// 키프레임들
		std::vector<FKeyFrame> m_vecKeyFrames;

		// 현재 키프레임
		FKeyFrame m_tCurKeyFrame{};

	private:
		std::weak_ptr<CMeshBone> m_wpMeshBone;
	};
}
