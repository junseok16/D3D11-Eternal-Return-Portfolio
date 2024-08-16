#include "pch.h"
#include "SoundComponent.h"

#include "SoundHandler.h"

#include "Actor.h"

HRESULT Engine::CSoundComponent::PreInitializeComponent()
{
	if (FAILED(CSceneComponent::PreInitializeComponent())) { return E_FAIL; }
	
	m_wpSoundHandler = CSoundHandler::GetInstance();
	return S_OK;
}

HRESULT Engine::CSoundComponent::InitializeComponent()
{
	if (FAILED(CSceneComponent::InitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSoundComponent::PostInitializeComponent()
{
	if (FAILED(CSceneComponent::PostInitializeComponent())) { return E_FAIL; }

	return S_OK;
}

HRESULT Engine::CSoundComponent::BeginPlay()
{
	if (FAILED(CSceneComponent::BeginPlay())) { return E_FAIL; }

	return S_OK;
}

int32 Engine::CSoundComponent::PreTickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::PreTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	if (!m_wpListener.expired())
	{
		m_fCurRadius = Vector3::Distance(m_wpOwnerActor.lock()->GetActorWorldPosition().value(), m_wpListener.lock()->GetActorWorldPosition().value());
	}

	return 0;
}

int32 Engine::CSoundComponent::TickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::TickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

int32 Engine::CSoundComponent::PostTickComponent(float _fDeltaSeconds)
{
	switch (CSceneComponent::PostTickComponent(_fDeltaSeconds))
	{
	case -1:	return -1;
	default:	break;
	}

	return 0;
}

HRESULT Engine::CSoundComponent::EndPlay()
{
	if (FAILED(CSceneComponent::EndPlay())) { return E_FAIL; }

	return S_OK;
}

void Engine::CSoundComponent::Render()
{
	CSceneComponent::Render();
}

void Engine::CSoundComponent::Release()
{
	CSceneComponent::Release();
}

void Engine::CSoundComponent::PlaySoundEx(const std::string& _strSoundFileName, ESoundType _eSoundType, float _fVolume, bool _bLoop)
{
	m_wpSoundHandler.lock()->PlaySoundEx(_strSoundFileName, _eSoundType, _fVolume, _bLoop);
}

void Engine::CSoundComponent::StopSoundEx(ESoundType _eSoundType)
{
	m_wpSoundHandler.lock()->StopSoundEx(_eSoundType);
}

void Engine::CSoundComponent::StopAllSoundEx()
{
	m_wpSoundHandler.lock()->StopAllSoundEx();
}

void Engine::CSoundComponent::ModifyVolume(ESoundType _eSoundType, float _fVolume)
{
	if (_fVolume <= 0.0f) { _fVolume = 0.0f; }

	m_wpSoundHandler.lock()->ModifyVolume(_eSoundType, _fVolume);
}

void Engine::CSoundComponent::RecalcAttenuation()
{
	CHECK(m_fNearRadius <= m_fFarRadius);

	if (m_fCurRadius <= m_fNearRadius)
	{
		m_fCurVolume = m_fMaxVolume;
		return;
	}

	else if (m_fFarRadius <= m_fCurRadius)
	{
		m_fCurVolume = m_fMinVolume;
		return;
	}

	switch (m_eSoundAttenuationType)
	{
	case ESoundAttenuationType::LINEAR:
		m_fCurVolume = m_fMaxVolume - (1.0f / (m_fFarRadius - m_fNearRadius) * (m_fCurRadius - m_fNearRadius));
		break;

	default:
		break;
	}

	if (m_fCurVolume >= 1.0f) { m_fCurVolume = 1.0f; }

	if (m_fCurVolume <= 0.0f) { m_fCurVolume = 0.0f; }
}
