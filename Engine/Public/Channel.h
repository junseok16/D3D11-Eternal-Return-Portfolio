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
		// ä���� �̸�
		string m_strChannelName = "";

		// �� ä�ΰ� �����Ǵ� ���� �ε���
		uint32 m_iBoneIndex = 0;

		// Ű�������� ��
		uint32 m_iNumKeyFrames = 0;

		// Ű�����ӵ�
		std::vector<FKeyFrame> m_vecKeyFrames;

		// ���� Ű������
		FKeyFrame m_tCurKeyFrame{};

	private:
		std::weak_ptr<CMeshBone> m_wpMeshBone;
	};
}
