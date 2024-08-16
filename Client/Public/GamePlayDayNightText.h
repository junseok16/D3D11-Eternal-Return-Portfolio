#pragma once
#include "Text.h"

namespace Client
{
	class CGameManager;

	class CGamePlayDayNightText : public CText
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CGamePlayDayNightText() = default;

		virtual ~CGamePlayDayNightText() = default;
		
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
		int32 m_iNumDay = 1;

		int32 m_iNumNight = 1;
	};
}
