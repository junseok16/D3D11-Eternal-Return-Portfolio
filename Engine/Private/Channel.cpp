#include "pch.h"
#include "Channel.h"

#include "MeshBone.h"
#include "Bone.h"

Engine::CChannel::CChannel(const CChannel& _rhs)
	: m_strChannelName(_rhs.m_strChannelName)
	, m_iBoneIndex(_rhs.m_iBoneIndex)
	, m_iNumKeyFrames(_rhs.m_iNumKeyFrames)
	, m_vecKeyFrames(_rhs.m_vecKeyFrames)
{
}

std::shared_ptr<CChannel> Engine::CChannel::Create(const std::string& _strChannelName, uint32 _iBoneIndex, uint32 _iNumKeyFrames, const std::vector<FKeyFrame>& _vecKeyFrames)
{
	const std::shared_ptr<CChannel> spChannel = make_shared<CChannel>();
	ENSUREF(spChannel->Initialize(_strChannelName, _iBoneIndex, _iNumKeyFrames, _vecKeyFrames), L"Failed to initialize channel");
	return spChannel;
}

HRESULT Engine::CChannel::Initialize(const std::string& _strChannelName, uint32 _iBoneIndex, uint32 _iNumKeyFrames, const std::vector<FKeyFrame>& _vecKeyFrames)
{
	m_strChannelName =_strChannelName;
	m_iBoneIndex =_iBoneIndex;
	m_iNumKeyFrames =_iNumKeyFrames;
	m_vecKeyFrames =_vecKeyFrames;
	return S_OK;
}

void Engine::CChannel::Release()
{
}

void Engine::CChannel::RecalcChannel(double _dCurTick, uint32& _iCurKeyFrame, bool _bReset)
{
	if (_dCurTick == 0.0)
	{
		m_tCurKeyFrame = m_vecKeyFrames.front();
		_iCurKeyFrame = 0;

		// 반복하지 않는 애니메이션인 경우, 첫 번째 키프레임으로 초기화합니다.
		if (_bReset) { return; }
	}

	FKeyFrame tKeyFrameEnd = m_vecKeyFrames.back();

	Matrix matTransform = Matrix::Identity;
	Vector4 vScale = Vector4::One;
	Vector4 vRotate = Vector4::Zero;
	Vector4 vTranslate = Vector4::Zero;

	// 현재 재생 중인 틱이 마지막 키프레임을 벗어난 경우
	if (_dCurTick >= tKeyFrameEnd.m_dTime)
	{
		vScale		= { tKeyFrameEnd.m_vScale.x, tKeyFrameEnd.m_vScale.y, tKeyFrameEnd.m_vScale.z, 0.0f };
		vRotate		= tKeyFrameEnd.m_vRotate;
		vTranslate	= { tKeyFrameEnd.m_vTranslate.x, tKeyFrameEnd.m_vTranslate.y, tKeyFrameEnd.m_vTranslate.z, 1.0f };
	}
	else
	{
		while (_dCurTick >= m_vecKeyFrames[_iCurKeyFrame + 1].m_dTime) { ++_iCurKeyFrame; }

		double dRatio = (_dCurTick - m_vecKeyFrames[_iCurKeyFrame].m_dTime) / (m_vecKeyFrames[_iCurKeyFrame + 1].m_dTime - m_vecKeyFrames[_iCurKeyFrame].m_dTime);

		vScale		= XMVectorLerp(m_vecKeyFrames[_iCurKeyFrame].m_vScale, m_vecKeyFrames[_iCurKeyFrame + 1].m_vScale, (float)dRatio);
		vRotate		= XMQuaternionSlerp(m_vecKeyFrames[_iCurKeyFrame].m_vRotate, m_vecKeyFrames[_iCurKeyFrame + 1].m_vRotate, (float)dRatio);
		vTranslate	= XMVectorSetW(XMVectorLerp(m_vecKeyFrames[_iCurKeyFrame].m_vTranslate, m_vecKeyFrames[_iCurKeyFrame + 1].m_vTranslate, (float)dRatio), 1.0f);
	}

	// 현재 재생 중인 키프레임도 갱신합니다.
	m_tCurKeyFrame.m_dTime = _dCurTick;
	m_tCurKeyFrame.m_vScale = Vector3(vScale);
	m_tCurKeyFrame.m_vRotate = vRotate;
	m_tCurKeyFrame.m_vTranslate = Vector3(vTranslate);

	matTransform = XMMatrixAffineTransformation(vScale, Vector4::UnitW, vRotate, vTranslate);

	const std::vector<std::shared_ptr<CBone>>& vecBones = m_wpMeshBone.lock()->GetBones();
	vecBones[m_iBoneIndex]->SetLocalMatrix(matTransform);
}
