#pragma once

namespace Engine
{
	class CEngineModule;
}

namespace Client
{
	class CGameManager;
	class CUIManager;

	class CClientModule final : public enable_shared_from_this<CClientModule>
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CClientModule() = default;

		virtual ~CClientModule() = default;

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
		Data Members
	********************/
	private:
		std::shared_ptr<CGameManager> m_spGameManager = nullptr;

		std::shared_ptr<CUIManager> m_spUIManager = nullptr;
	};
}
