#pragma once

namespace Engine
{
	class CEngineModule;
	class CWorld;
}

namespace Client
{
	class CClientModule;

	class CClientLoop final
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CClientLoop() = default;

		virtual ~CClientLoop() = default;

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

		std::shared_ptr<CClientModule> m_spClientModule = nullptr;

	public:
		std::shared_ptr<CWorld> m_spWorld = nullptr;
	};
}
