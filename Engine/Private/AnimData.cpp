#include "pch.h"
#include "AnimData.h"

#include "Actor.h"
#include "StateComponent.h"

#include "AnimState.h"

std::shared_ptr<CAnimData> Engine::CAnimData::Create(const std::shared_ptr<CActor>& _spOwnerActor)
{
	const std::shared_ptr<CAnimData> spAnimData = make_shared<CAnimData>();
	ENSURE(spAnimData->Initialize(_spOwnerActor));
	return spAnimData;
}

HRESULT Engine::CAnimData::Initialize(const std::shared_ptr<CActor>& _spOwnerActor)
{
	m_wpOwnerActor = _spOwnerActor;

	m_wpStateComponent = m_wpOwnerActor.lock()->FindActorComponent<CStateComponent>(EComponentType::STATE).front();
	return S_OK;
}

int32 Engine::CAnimData::Tick(float _fDeltaSeconds)
{
	m_iCurAnimState = m_wpStateComponent.lock()->GetCurAnimState();
	return 0;
}

void Engine::CAnimData::Render()
{
}

void Engine::CAnimData::Release()
{
	for (auto& pair : m_umapAnimStates)
	{
		pair.second->Release();
		pair.second = nullptr;
	}
	m_umapAnimStates.clear();
}

HRESULT Engine::CAnimData::AddAnimState(uint32 _iAnimState, const std::wstring& _wstrAnimStateName, const std::vector<std::string>& _vecAnimationNames, bool _bLoop)
{
	// 이미 애니메이션 스테이트가 있는 경우
	if (m_umapAnimStates.find(_iAnimState) != m_umapAnimStates.end()) { return E_FAIL; }

	m_wstrCurAnimState = _wstrAnimStateName;
	m_umapAnimStates.insert({ _iAnimState, CAnimState::Create(_iAnimState, _wstrAnimStateName, _vecAnimationNames, _bLoop) });
	return S_OK;
}

void Engine::CAnimData::SetSkeletalMeshData(const std::shared_ptr<CSkeletalMeshData>& _spSkeletalMeshData)
{
	m_wpSkeletalMeshData = _spSkeletalMeshData;
}

std::shared_ptr<CAnimState> Engine::CAnimData::GetCurAnimState() const
{
	return m_umapAnimStates.at(m_iCurAnimState);
}
