#pragma once

namespace Engine
{
	class CEngineModule;
	class CWorld;
}

namespace Editor
{
	class CEditorModule;

	class CEditorLoop final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CEditorLoop() = default;

		virtual ~CEditorLoop() = default;

	/********************
		Events
	********************/
	public:
		HRESULT PreInitialize();

		HRESULT Initialize();

		HRESULT PostInitialize();

		int32 Tick();

		void Render();

		void Release();
		
	/********************
		Data Members
	********************/
	public:
		std::shared_ptr<CEngineModule> m_spEngineModule = nullptr;

		std::shared_ptr<CEditorModule> m_spEditorModule = nullptr;

	public:
		std::shared_ptr<CWorld> m_spWorld = nullptr;
	};
}
