#include "pch.h"
#include "SoundLoader.h"

#include "SoundHandler.h"

std::shared_ptr<CSoundLoader> Engine::CSoundLoader::Create()
{
	const std::shared_ptr<CSoundLoader> spLoader = make_shared<CSoundLoader>();
	ENSUREF(spLoader->Initialize(), L"Failed to create sound loader.");
	return spLoader;
}

HRESULT Engine::CSoundLoader::Initialize()
{
	m_wpSoundHandler = CSoundHandler::GetInstance();

	FMOD_System_Create(&m_pFMODSystem);
	FMOD_System_Init(m_pFMODSystem, 32, FMOD_INIT_NORMAL, nullptr);

	LoadSoundFromFile();
	return S_OK;
}

void Engine::CSoundLoader::Release()
{
	FMOD_System_Release(m_pFMODSystem);
	FMOD_System_Close(m_pFMODSystem);
}

HRESULT Engine::CSoundLoader::LoadSoundFromFile()
{
	for (const std::filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_wstrSoundFilePath))
	{
		// 파일이 아닌 경우
		if (!filesystem::is_regular_file(fsEntry)) { continue; }

		// wav 파일이 아닌 경우
		if (fsEntry.path().extension().generic_string() != ".wav" && fsEntry.path().extension().generic_string() != ".WAV") { continue; }

		LoadSound(fsEntry);
	}

	FMOD_System_Update(m_pFMODSystem);
	return S_OK;
}

void Engine::CSoundLoader::LoadSound(const std::filesystem::directory_entry& _fsEntry)
{
	string strSoundFilePath = _fsEntry.path().generic_string();
	
	FMOD_SOUND* pFMODSound = nullptr;
	if (FMOD_System_CreateSound(m_pFMODSystem, strSoundFilePath.c_str(), FMOD_DEFAULT, 0, &pFMODSound) != FMOD_OK) { return; }
	
	string strSoundFileName = _fsEntry.path().stem().generic_string();
	m_wpSoundHandler.lock()->AddSound(strSoundFileName, pFMODSound);
}
