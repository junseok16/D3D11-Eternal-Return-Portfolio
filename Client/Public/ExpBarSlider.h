#pragma once
#include "Slider.h"

namespace Client
{
	class CGameManager;
	class CSurvivor;

	class CExpBarSlider final : public CSlider
	{
	/********************
		Ctor/Dtor
	********************/
	public:
		explicit CExpBarSlider() = default;

		virtual ~CExpBarSlider() = default;
		
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
	private:
		virtual void TickSlider() override;
		
	/********************
		Data Memebers
	********************/
	private:
		std::weak_ptr<CGameManager> m_wpGameManager;

		std::weak_ptr<CSurvivor> m_wpSurvivor;
	};
}
