#pragma once

namespace Engine
{
	class CEngineModule;

	class CModelHandler;
	class CShaderHandler;
	class CNavHandler;

	class CInputManager;
}

namespace Editor
{
	class CIMGUIManager;
	class CEditorCamera;
	class CEditorLevel;

	class CModeWindow final
	{
	public:
		explicit CModeWindow() = default;

		virtual ~CModeWindow() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CModeWindow> Create(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager);

		HRESULT Initialize(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager);

		int32 Tick();

		void Release();
		
	/********************
		Methods
	********************/
	private:
		void TickSeparaterMode();
		void TickWildAnimalTab();
		void CreateWildAnimal();

		void SaveChicken();
		void SaveBear();
		void SaveBoar();
		void SaveDog();
		void SaveWolf();

		void LoadChicken();
		void LoadBear();
		void LoadBoar();
		void LoadDog();
		void LoadWolf();
			
	/********************
		Data Members
	********************/
	private:
		// level
		std::weak_ptr<CEditorLevel> m_wpEditorLevel;

		// handler
		std::weak_ptr<CModelHandler> m_wpModelHandler;

		std::weak_ptr<CShaderHandler> m_wpShaderHandler;

		std::weak_ptr<CNavHandler> m_wpNavHandler;

		// manager
		std::weak_ptr<CIMGUIManager> m_wpIMGUIManager;

		std::weak_ptr<CInputManager> m_wpInputManager;

		std::weak_ptr<CEditorCamera> m_wpEditorCamera;

	private:
		EEditorCreateMode m_eEditorCreateMode = EEditorCreateMode::NONE;

		const std::array<const char*, 6> m_arrWildAnimalNames{ "BEAR", "BOAR", "CHICKEN", "DOG", "WOLF", "ENUM_END" };

		uint32 m_iChangableWildAnimalType = (uint32)m_arrWildAnimalNames.size() - 1;

		int32 m_iCellIndex = 0;

		// 야생 동물 파일 이름
		char m_chSaveWildAnimalFileName[MAX_PATH]{ NULL };

		// 야생 동물 파일 경로
		std::string m_strWildAnimalFilePath = "../../Resource/Editor/WildAnimal/";
	};
}
