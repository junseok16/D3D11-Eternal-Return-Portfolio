#pragma once
#include "Text.h"

namespace Editor
{
	class CGameManager;

	class CGamePlayTimeText final : public CText
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CGamePlayTimeText() = default;

		virtual ~CGamePlayTimeText() = default;
		
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
		float m_fLeftSeconds = 0.0f;
	};
}
