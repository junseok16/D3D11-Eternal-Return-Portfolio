#pragma once

namespace Engine
{
	class CActor;
	class CModelHandler;
	class CShaderHandler;
}

namespace Editor
{
	class CEditorLevel;
	class CIMGUIManager;

	class CDetailWindow final
	{
	public:
		explicit CDetailWindow() = default;

		virtual ~CDetailWindow() = default;
		
	/********************
		Events
	********************/
	public:
		static std::shared_ptr<CDetailWindow> Create(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager);

		HRESULT Initialize(const std::shared_ptr<CIMGUIManager>& _spIMGUIManager);

		int32 Tick();

		void Release();
		
	/********************
		Methods
	********************/
	private:
		void TickSeparaterLevel();
			void TickWildAnimalTabBar();

		void TickSeparaterDetail();
			void TickSceneComponentDetail();
			
	/********************
		Data Members
	********************/
	private:
		// 액터 이름
		char m_chName[64]{ NULL };

		std::weak_ptr<CActor> m_wpActor;

		wstring m_wstrActorName = L"";

		float m_fDegree = 0.0f;

	private:
		std::weak_ptr<CEditorLevel> m_wpEditorLevel;

		std::weak_ptr<CIMGUIManager> m_wpIMGUIManager;

		std::weak_ptr<CModelHandler> m_wpModelHandler;

		std::weak_ptr<CShaderHandler> m_wpShaderHandler;
	};
}
