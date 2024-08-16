#include "pch.h"
#include "SoundHandler.h"

#include "SoundLoader.h"

IMPLEMENT_SINGLETON(CSoundHandler)

HRESULT Engine::CSoundHandler::Initialize()
{
	m_spSoundLoader = CSoundLoader::Create();
	return S_OK;
}

void Engine::CSoundHandler::Release()
{
	for (auto& pair : m_umapFMODSounds)
	{
		FMOD_Sound_Release(pair.second);
	}
	m_umapFMODSounds.clear();

	m_spSoundLoader->Release();
	m_spSoundLoader = nullptr;

	m_spInstance.reset();
}

HRESULT Engine::CSoundHandler::AddSound(const std::string& _strSoundFileName, FMOD_SOUND* _pFMODSound)
{
	if (m_umapFMODSounds.find(_strSoundFileName) != m_umapFMODSounds.end()) { return E_FAIL; }

	m_umapFMODSounds.insert({ _strSoundFileName, _pFMODSound });
	return S_OK;
}

void Engine::CSoundHandler::PlaySoundEx(const std::string& _strSoundFileName, ESoundType _eSoundType, float _fVolume, bool _bLoop)
{
	if (m_umapFMODSounds.find(_strSoundFileName) == m_umapFMODSounds.end()) { return; }

	FMOD_System_PlaySound(m_spSoundLoader->GetFMODSystem(), m_umapFMODSounds[_strSoundFileName], nullptr, false, &m_arrFMODChannels[static_cast<int32>(_eSoundType)]);

	if (_bLoop) { FMOD_Channel_SetMode(m_arrFMODChannels[static_cast<int32>(_eSoundType)], FMOD_LOOP_NORMAL); }
	FMOD_Channel_SetVolume(m_arrFMODChannels[(int32)_eSoundType], _fVolume);
	FMOD_System_Update(m_spSoundLoader->GetFMODSystem());
}

void Engine::CSoundHandler::StopSoundEx(ESoundType _eSoundType)
{
	FMOD_Channel_Stop(m_arrFMODChannels[static_cast<int32>(_eSoundType)]);
}

void Engine::CSoundHandler::StopAllSoundEx()
{
	for (int32 iIndex = 0; iIndex < (int32)ESoundType::ENUM_END; ++iIndex)
	{
		FMOD_Channel_Stop(m_arrFMODChannels[iIndex]);
	}
}

void Engine::CSoundHandler::ModifyVolume(ESoundType _eSoundType, float _fVolume)
{
	FMOD_Channel_SetVolume(m_arrFMODChannels[static_cast<int32>(_eSoundType)], _fVolume);
	FMOD_System_Update(m_spSoundLoader->GetFMODSystem());
}
