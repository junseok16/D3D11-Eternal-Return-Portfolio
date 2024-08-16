#pragma once

namespace Engine
{
	class CSoundLoader;

	class ENGINE_DLL CSoundHandler final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		DECLARE_SINGLETON(CSoundHandler)
		
	/********************
		Events
	********************/
	public:
		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT AddSound(const std::string& _strSoundFileName, FMOD_SOUND* _pFMODSound);

	public:
		void PlaySoundEx(const std::string& _strSoundFileName, ESoundType _eSoundType, float _fVolume, bool _bLoop);

		void StopSoundEx(ESoundType _eSoundType);

		void StopAllSoundEx();

		void ModifyVolume(ESoundType _eSoundType, float _fVolume);

	/********************
		Data Members
	********************/
	private:
		std::shared_ptr<CSoundLoader> m_spSoundLoader = nullptr;

	private:
		std::array<FMOD_CHANNEL*, (int32)ESoundType::ENUM_END> m_arrFMODChannels{ nullptr };

		std::unordered_map<std::string, FMOD_SOUND*> m_umapFMODSounds;
	};
}
