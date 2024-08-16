#pragma once

namespace Engine
{
	class CEngineModule;
}

namespace Editor
{
	class CGameManager;
	class CIMGUIManager;

	class CEditorModule final : public enable_shared_from_this<CEditorModule>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEditorModule() = default;

		virtual ~CEditorModule() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize(const std::shared_ptr<CEngineModule>& _spEngineModule);

		HRESULT Initialize();

		HRESULT PostInitialize();

		int32 PreTick();

		int32 Tick(float _fDeltaSeconds);

		int32 PostTick();

		void Render();

		void Release();
		
	/********************
		Getter/Setter
	********************/
	public:
		std::shared_ptr<CIMGUIManager> GetIMGUIManager() const { return m_spIMGUIManager; }

	/********************
		Data Members
	********************/
	private:
		std::shared_ptr<CIMGUIManager> m_spIMGUIManager = nullptr;

		std::shared_ptr<CGameManager> m_spGameManager = nullptr;
	};
}

