#pragma once

namespace Engine
{
	class CController;
}

namespace Editor
{
	class CEditorLevel;
	class CIMGUIManager;

	class CTabWindow final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CTabWindow() = default;

		virtual ~CTabWindow() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CTabWindow> Create(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager);

		HRESULT Initialize(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager);

		int32 Tick();

		void Release();
		
	/********************
		Events
	********************/
	private:
		void TickPlayButton();

		void TickStopButton();

		void TickSaveButton();
			void SaveLocations(std::ofstream& _outFile);
			void SaveNavigations(std::ofstream& _outFile);
			void SaveCollectibleGroups(std::ofstream& _outFile);
			void SaveConsoleGroups(std::ofstream& _outFile);
			void SaveWildAnimal(std::ofstream& _outFile);

		void TickLoadButton();
			void LoadLocations(std::ifstream& _inFile);
			void LoadNavigations(std::ifstream& _inFile);
			void LoadCollectibleGroups(std::ifstream& _inFile);
			void LoadConsoleGroups(std::ifstream& _inFile);
			void LoadWildAnimal(std::ifstream& _inFile);
			
	/********************
		Data Members
	********************/
	private:
		// 파일 이름
		char m_chSaveFileName[MAX_PATH]{ NULL };

		char m_chLoadFileName[MAX_PATH]{ NULL };

		// 파일 경로
		std::string m_strFilePath = "../../Resource/Editor/";

	private:
		std::weak_ptr<CController> m_wpController;

		std::weak_ptr<CEditorLevel> m_wpEditorLevel;

		std::weak_ptr<CIMGUIManager> m_wpIMGUIManager;

		bool m_bOnAir = false;
	};
}
