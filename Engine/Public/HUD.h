#pragma once
#include "Actor.h"

namespace Engine
{
	class CPanel;

	class ENGINE_DLL CHUD : public CActor
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CHUD() = default;

		virtual ~CHUD() = default;
		
	/********************
		Events
	********************/
	public:
		virtual HRESULT PreInitialize();

		virtual HRESULT Initialize();

		virtual HRESULT PostInitialize();

		virtual HRESULT BeginPlay();

		virtual int32 PreTick(float _fDeltaSeconds);

		virtual int32 Tick(float _fDeltaSeconds);
		
		virtual int32 PostTick(float _fDeltaSeconds);

		virtual HRESULT EndPlay();

		virtual void Render();

		virtual void Release();
		
	/********************
		Methods
	********************/
	public:
		HRESULT AddPanel(const std::wstring& _wstrPanelName, const std::shared_ptr<CPanel> _spPanel);

		HRESULT RemovePanel(const std::wstring& _wstrPanelName);

	/********************
		Data Members
	********************/
	protected:
		std::weak_ptr<CActor> m_wpOwnerActor;

	protected:
		std::unordered_map<std::wstring, std::shared_ptr<CPanel>> m_umapPanels;
	};
}
