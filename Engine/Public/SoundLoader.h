#pragma once

namespace Engine
{
	class CSoundHandler;

	class CSoundLoader final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CSoundLoader() = default;

		virtual ~CSoundLoader() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CSoundLoader> Create();

		HRESULT Initialize();

		void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT LoadSoundFromFile();

	private:
		void LoadSound(const std::filesystem::directory_entry& _fsEntry);
		
	/********************
		Getter/Setter
	********************/
	public:
		FMOD_SYSTEM* GetFMODSystem() const { return m_pFMODSystem; }

	/********************
		Data Members
	********************/
	private:
		std::weak_ptr<CSoundHandler> m_wpSoundHandler;

		FMOD_SYSTEM* m_pFMODSystem = nullptr;

		std::wstring m_wstrSoundFilePath = L"../../Resource/Sounds/";
	};
}
