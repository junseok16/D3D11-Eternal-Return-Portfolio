#include "pch.h"
#include "Animation.h"

#include "Channel.h"

Engine::CAnimation::CAnimation(const CAnimation& _rhs)
	: m_iNumAnimations(_rhs.m_iNumAnimations)
	, m_strAnimationName(_rhs.m_strAnimationName)
	, m_dDuration(_rhs.m_dDuration)
	, m_dTickPerSeconds(_rhs.m_dTickPerSeconds)
	, m_dCurTick(_rhs.m_dCurTick)
	, m_iNumChannels(_rhs.m_iNumChannels)
	, m_vecCurKeyFrames(_rhs.m_vecCurKeyFrames)
	, m_umapCurKeyFrames(_rhs.m_umapCurKeyFrames)
	, m_umapFirstKeyFrames(_rhs.m_umapFirstKeyFrames)
	, m_umapLastKeyFrames(_rhs.m_umapLastKeyFrames)
{
	size_t iSize = _rhs.m_vecChannels.size();
	m_vecChannels.resize(iSize);
	m_vecChannels.reserve(iSize);

	for (size_t iIndex = 0; iIndex < iSize; ++iIndex)
	{
		shared_ptr<CChannel> spChannel = make_shared<CChannel>(*(_rhs.m_vecChannels[iIndex]));
		m_vecChannels[iIndex] = spChannel;
	}
}

std::shared_ptr<CAnimation> Engine::CAnimation::Create
(
	const std::string& _strAnimationName,
	double _dDuration,
	double _dTickPerSeconds,
	uint32 _iNumChannels,
	const std::vector<std::shared_ptr<CChannel>>& _vecChannels
)
{
	const shared_ptr<CAnimation> spAnimation = make_shared<CAnimation>();
	ENSUREF(spAnimation->Initialize(_strAnimationName, _dDuration, _dTickPerSeconds, _iNumChannels, _vecChannels), L"Failed to initialize animation.");
	return spAnimation;
}

HRESULT Engine::CAnimation::Initialize
(
	const std::string& _strAnimationName,
	double _dDuration,
	double _dTickPerSeconds,
	uint32 _iNumChannels,
	const std::vector<std::shared_ptr<CChannel>>& _vecChannels
)
{
	m_strAnimationName = _strAnimationName;
	m_dDuration = _dDuration;
	m_dTickPerSeconds = _dTickPerSeconds;
	m_iNumChannels = _iNumChannels;
	m_vecChannels = _vecChannels;
	m_vecCurKeyFrames.resize(_iNumChannels);

	for (const auto& spChannel : _vecChannels)
	{
		string strChannelName = spChannel->GetChannelName();
		uint32 iBoneIndex = spChannel->GetBoneIndex();
		FKeyFrame tFirstKeyFrame = spChannel->GetFirstKeyFrame();
		FKeyFrame tLastKeyFrame = spChannel->GetLastKeyFrame();
		m_umapFirstKeyFrames.insert({ strChannelName, { iBoneIndex, tFirstKeyFrame } });
		m_umapLastKeyFrames.insert({ strChannelName, { iBoneIndex, tLastKeyFrame } });
	}
	
	return S_OK;
}

void Engine::CAnimation::Release()
{
	for (auto& spChannel : m_vecChannels)
	{
		spChannel->Release();
		spChannel = nullptr;
	}
}

bool Engine::CAnimation::RecalcAnimation(float _fDeltaSeconds, float& _fRatio, bool _bLoop)
{
	// 현재 재생 중인 틱을 구합니다.
	m_dCurTick += m_dTickPerSeconds * _fDeltaSeconds;

	_fRatio = static_cast<float>(m_dCurTick / m_dDuration);

	// 현재 재생 중인 틱이 재생 시간보다 큰 경우
	if (m_dCurTick >= m_dDuration)
	{
		m_dCurTick = 0.0;

		// 반복하지 않는 애니메이션인 경우, 키프레임을 초기화합니다.
		if (_bLoop == false)
		{
			_fRatio = 1.0f;
			ResetAnimation();
			
			/*
			for (uint32 iIndex = 0; iIndex < m_iNumChannels; ++iIndex)
			{
				m_vecChannels[iIndex]->RecalcChannel(m_dCurTick, m_vecCurKeyFrames[iIndex], true);

				// 채널 이름에 대응되는 키프레임을 갱신합니다.
				string strChannelName = m_vecChannels[iIndex]->GetChannelName();
				FKeyFrame tKeyFrame = m_vecChannels[iIndex]->GetCurKeyFrame();
				int32 iBoneIndex = m_vecChannels[iIndex]->GetBoneIndex();
				m_umapCurKeyFrames[strChannelName] = { iBoneIndex, tKeyFrame };
			}
			*/
			return false; 
		}
		// 반복하는 애니메이션인 경우, 
		else
		{
			_fRatio = 0.0f;
		}
	}

	// 이 애니메이션 안에 있는 채널들
	for (uint32 iIndex = 0; iIndex < m_iNumChannels; ++iIndex)
	{
		m_vecChannels[iIndex]->RecalcChannel(m_dCurTick, m_vecCurKeyFrames[iIndex], false);

		// 채널 이름에 대응되는 키프레임을 갱신합니다.
		string strChannelName = m_vecChannels[iIndex]->GetChannelName();
		FKeyFrame tKeyFrame = m_vecChannels[iIndex]->GetCurKeyFrame();
		int32 iBoneIndex = m_vecChannels[iIndex]->GetBoneIndex();
		m_umapCurKeyFrames[strChannelName] = { iBoneIndex, tKeyFrame };
	}
	return true;
}

void Engine::CAnimation::ResetAnimation()
{
	m_dCurTick = 0.0;
	for (uint32 iIndex = 0; iIndex < m_iNumChannels; ++iIndex)
	{
		m_vecCurKeyFrames[iIndex] = 0;
		string strChannelName = m_vecChannels[iIndex]->GetChannelName();
		m_umapCurKeyFrames[strChannelName] = m_umapFirstKeyFrames[strChannelName];
	}

	/*
	for (uint32 iIndex = 0; iIndex < m_iNumChannels; ++iIndex)
	{
		m_vecChannels[iIndex]->RecalcChannel(0.0, m_vecCurKeyFrames[iIndex], true);

		// 채널 이름에 대응되는 키프레임을 갱신합니다.
		string strChannelName = m_vecChannels[iIndex]->GetChannelName();
		FKeyFrame tKeyFrame = m_vecChannels[iIndex]->GetCurKeyFrame();
		int32 iBoneIndex = m_vecChannels[iIndex]->GetBoneIndex();
		m_umapCurKeyFrames[strChannelName] = { iBoneIndex, tKeyFrame };
	}
	*/
}

void Engine::CAnimation::SetMeshBone(const shared_ptr<CMeshBone>& _spMeshBone)
{
	for (auto& spChannel : m_vecChannels)
	{
		spChannel->SetMeshBone(_spMeshBone);
	}
}
