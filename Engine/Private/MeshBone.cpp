#include "pch.h"
#include "MeshBone.h"

#include "Actor.h"

#include "SceneComponent.h"
#include "StateComponent.h"

#include "ModelHandler.h"
#include "Animation.h"
#include "AnimState.h"
#include "AnimData.h"
#include "Bone.h"

std::shared_ptr<CMeshBone> Engine::CMeshBone::Create(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrModelDesc)
{
	const shared_ptr<CMeshBone> spMeshBone = make_shared<CMeshBone>();
	ENSUREF(spMeshBone->Initialize(_spOwnerComponent, _wstrModelDesc), L"Failed to initialize mesh bone.");
	return spMeshBone;
}

HRESULT Engine::CMeshBone::Initialize(const std::shared_ptr<CSceneComponent>& _spOwnerComponent, const std::wstring& _wstrModelDesc)
{
	// TODO; 레벨 데이터에서 로드할 때, 이곳을 작성해야 합니다.
	if (_wstrModelDesc.empty()) { return S_OK; }
	
	m_wpOwnerComponent = _spOwnerComponent;
	// m_wpStateComponent = m_wpOwnerComponent.lock()->GetOwnerActor()->FindActorComponent<CStateComponent>(EComponentType::STATE);
	m_wpStateComponent = m_wpOwnerComponent.lock()->GetOwnerActor()->FindActorComponent<CStateComponent>(EComponentType::STATE).front();
	m_wpOwnerActor = _spOwnerComponent->GetOwnerActor();

	shared_ptr<FModelDesc> spModelDesc = CModelHandler::GetInstance()->FindModelDesc(_wstrModelDesc);
	m_vecBones = CModelHandler::GetInstance()->CloneBone(spModelDesc->m_wstrModelName, shared_from_this());
	m_umapAnimtaions = CModelHandler::GetInstance()->CloneAnimation(spModelDesc->m_wstrModelName, shared_from_this());
	return S_OK;
}

int32 Engine::CMeshBone::Tick(float _fDeltaSeconds)
{
	UpdateAnimState();
	RecalcAnimation(_fDeltaSeconds);	
	return 0;
}

std::shared_ptr<CBone> Engine::CMeshBone::FindBone(const std::string& _strBoneName)
{
	for (const auto& spBones : m_vecBones)
	{
		if (spBones->GetBoneName() == _strBoneName)
		{
			return spBones;
		}
	}
	return nullptr;
}

void Engine::CMeshBone::SetPlayRate(float _fPlayRate)
{
	m_fPlayRate = _fPlayRate;
}

void Engine::CMeshBone::UpdateAnimState()
{
	// 현재 애니메이션 상태를 불러옵니다.
	m_wpCurAnimState = m_wpAnimData.lock()->GetCurAnimState();

	uint32 iAnimState = m_wpCurAnimState.lock()->GetAnimState();
	uint32 iAnimIndex = m_wpCurAnimState.lock()->GetCurAnimIndex();
	string strAnimationName = m_wpCurAnimState.lock()->GetCurAnimationName();

	if (m_iCurAnimState == -1)
	{
		m_iCurAnimState = (int32)iAnimState;
		m_eAnimChangeState = EAnimChangeState::PLAY;
		m_strCurAnimationName = strAnimationName;
		return;
	}

	if (m_eAnimChangeState == EAnimChangeState::SOFT_INTERPOLATE)
	{
		return;
	}

	if (m_eAnimChangeState == EAnimChangeState::HARD_INTERPOLATE)
	{
		return;
	}

	// 현재 상태와 같은 경우
	if (m_iCurAnimState == iAnimState)
	{
		m_eAnimChangeState = EAnimChangeState::PLAY;
		m_strCurAnimationName = strAnimationName;
	}
	// 현재 상태와 다른 경우
	else
	{
		m_eAnimChangeState = EAnimChangeState::HARD_INTERPOLATE;
		m_strAfterAnimationName = strAnimationName;
		m_iAfterAnimState = iAnimState;
		m_wpOwnerActor.lock()->OnAnimEnter(iAnimState, iAnimIndex, 0.0f);
		m_wpStateComponent.lock()->OnAnimEnter(iAnimState, 1.0f);
	}
}

void Engine::CMeshBone::RecalcAnimation(float _fDeltaSeconds)
{
	float fRatio = 0.0f;

	bool bLoop = m_wpCurAnimState.lock()->IsLoop();

	switch (m_eAnimChangeState)
	{
	case Engine::EAnimChangeState::PLAY:
	{
		// 여러 애니메이션 중에서 현재 애니메이션이 끝난 경우, 다음 애니메이션과 보간합니다.
		if (false == m_umapAnimtaions[m_strCurAnimationName]->RecalcAnimation(m_fPlayRate * _fDeltaSeconds, fRatio, bLoop))
		{
			uint32 iAnimState = m_wpCurAnimState.lock()->GetAnimState();
			uint32 iAnimIndex = m_wpCurAnimState.lock()->GetCurAnimIndex();
			m_wpOwnerActor.lock()->OnAnimExit(iAnimState, iAnimIndex, 1.0f);

			// 다음 애니메이션이 있는 경우
			if (m_wpCurAnimState.lock()->HasAnotherAnimation())
			{
				// 소프트 보간하는 코드
				m_bLastAnim = true;
				m_eAnimChangeState = EAnimChangeState::SOFT_INTERPOLATE;
				m_strAfterAnimationName = m_wpCurAnimState.lock()->GetCurAnimationName();

				uint32 iAnimState = m_wpCurAnimState.lock()->GetAnimState();
				uint32 iAnimIndex = m_wpCurAnimState.lock()->GetCurAnimIndex();
				m_wpOwnerActor.lock()->OnAnimEnter(iAnimState, iAnimIndex, 0.0f);
				m_wpStateComponent.lock()->OnAnimEnter(iAnimState, 1.0f);
			}
			// 다음 애니메이션이 없는 경우
			else
			{
				m_bLastAnim = true;
				m_wpStateComponent.lock()->OnAnimExit(iAnimState, 1.0f);
				return;
			}
		}
		// 애니메이션이 재생 중인 경우
		else
		{
			uint32 iAnimState = m_wpCurAnimState.lock()->GetAnimState();
			uint32 iAnimIndex = m_wpCurAnimState.lock()->GetCurAnimIndex();
			m_wpOwnerActor.lock()->OnAnimStay(iAnimState, iAnimIndex, fRatio);
			m_wpStateComponent.lock()->OnAnimStay(iAnimState, fRatio);
		}
	}
	break;
	
	case Engine::EAnimChangeState::SOFT_INTERPOLATE:
	{
		// 현재 애니메이션이 갖고 있는 채널, 다음 애니메이션이 갖고 있는 채널을 보간합니다.
		if (InterpolateAnimation(_fDeltaSeconds, m_fSoftInterpolateSeconds))
		{
			// 보간이 끝나면 본 상태를 초기화합니다.
			m_umapAnimtaions[m_strCurAnimationName]->ResetAnimation();

			m_eAnimChangeState = EAnimChangeState::PLAY;
			m_strCurAnimationName = m_strAfterAnimationName;
		}
	}
	break;
	
	case Engine::EAnimChangeState::HARD_INTERPOLATE:
	{
		// 현재 애니메이션이 갖고 있는 채널, 다른 애니메이션이 갖고 있는 채널을 보간합니다.
		if (InterpolateAnimation(_fDeltaSeconds, m_fHardInterplateSeconds))
		{
			// 보간이 끝나면 본 상태를 초기화합니다.
			m_umapAnimtaions[m_strCurAnimationName]->ResetAnimation();

			m_eAnimChangeState = EAnimChangeState::PLAY;
			m_iCurAnimState = m_iAfterAnimState;
			m_strCurAnimationName = m_strAfterAnimationName;
		}
	}
	break;

	default:
		break;
	}

	// 보간된 값을 갱신한다.
	for (const auto& spBone : m_vecBones)
	{
		spBone->RecalcBone(m_vecBones);
	}
}

void Engine::CMeshBone::Release()
{
	for (auto& spBone : m_vecBones)
	{
		spBone->Release();
		spBone = nullptr;
	}

	for (auto& pair : m_umapAnimtaions)
	{
		pair.second->Release();
		pair.second = nullptr;
	}
}

bool Engine::CMeshBone::InterpolateAnimation(float _fDeltaSeconds, float _fInterpolateSeconds)
{
	// 현재 재생 중인 시각을 구합니다.
	m_fCurSeconds += _fDeltaSeconds;

	// 현재 재생 중인 시각이 보간 시간보다 큰 경우
	if (m_fCurSeconds >= _fInterpolateSeconds)
	{
		if (m_bLastAnim) { m_bLastAnim = false; }

		m_fCurSeconds = 0.0f;
		return true;
	}

	// 현재 애니메이션은 현재 키프레임을 불러옵니다.
	auto& umapCurKeyFrames = m_umapAnimtaions[m_strCurAnimationName]->GetCurKeyFrames(m_bLastAnim);

	// 다음 애니메이션은 첫 번째 키프레임을 불러옵니다.
	auto& umapAfterKeyFrames = m_umapAnimtaions[m_strAfterAnimationName]->GetFirstKeyFrames();

	unordered_set<string> usetInterpolatedKeyFrames;
	for (const auto& pairCur : umapCurKeyFrames)
	{
		for (const auto& pairAfter : umapAfterKeyFrames)
		{
			// 두 채널의 이름이 같은 경우
			if (pairCur.first == pairAfter.first)
			{
				if (usetInterpolatedKeyFrames.find(pairCur.first) != usetInterpolatedKeyFrames.end()) { continue; }

				Matrix matTransform = Matrix::Identity;
				Vector4 vScale = Vector4::One;
				Vector4 vRotate = Vector4::Zero;
				Vector4 vTranslate = Vector4::Zero;

				double dRatio = m_fCurSeconds / _fInterpolateSeconds;

				vScale		=				XMVectorLerp		(pairCur.second.second.m_vScale,	 pairAfter.second.second.m_vScale,		(float)dRatio);
				vRotate		=				XMQuaternionSlerp	(pairCur.second.second.m_vRotate,	 pairAfter.second.second.m_vRotate,		(float)dRatio);
				vTranslate	= XMVectorSetW (XMVectorLerp		(pairCur.second.second.m_vTranslate, pairAfter.second.second.m_vTranslate,	(float)dRatio), 1.0f);

				matTransform = XMMatrixAffineTransformation(vScale, Vector4::UnitW, vRotate, vTranslate);
				m_vecBones[pairCur.second.first]->SetLocalMatrix(matTransform);

				usetInterpolatedKeyFrames.insert(pairCur.first);
			}
		}
	}

	usetInterpolatedKeyFrames.clear();
	return false;
}
