#include "pch.h"
#include "AnimState.h"

std::shared_ptr<CAnimState> Engine::CAnimState::Create
(
	uint32 _iAnimState,
	const std::wstring& _wstrAnimStateName,
	const std::vector<std::string>& _vecAnimationNames,
	bool _bLoop
)
{
	const std::shared_ptr<CAnimState> spAnimState = make_shared<CAnimState>();
	ENSURE(spAnimState->Initialize(_iAnimState, _wstrAnimStateName, _vecAnimationNames, _bLoop));
	return spAnimState;
}

HRESULT Engine::CAnimState::Initialize
(
	uint32 _iAnimState,
	const std::wstring& _wstrAnimStateName,
	const std::vector<std::string>& _vecAnimationNames,
	bool _bLoop
)
{
	m_iAnimState = _iAnimState;
	m_wstrAnimStateName = _wstrAnimStateName;
	m_vecAnimationNames = _vecAnimationNames;
	m_bLoop = _bLoop;
	return S_OK;
}

int32 Engine::CAnimState::Tick(float _fDeltaSeconds)
{
	return 0;
}

void Engine::CAnimState::Release()
{
}

bool Engine::CAnimState::HasAnotherAnimation()
{
	if (++m_iCurAnimationIndex < m_vecAnimationNames.size()) { return true; }

	m_iCurAnimationIndex = 0;
	return false;
}
