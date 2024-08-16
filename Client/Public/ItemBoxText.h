#pragma once
#include "Text.h"

namespace Client
{
	class CGameManager;

	class CItemBoxText : public CText
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CItemBoxText() = default;

		virtual ~CItemBoxText() = default;
		
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
		Data Members
	********************/
	private:
		std::weak_ptr<CGameManager> m_wpGameManager;

	private:
		bool m_bOpened = false;
	};
}
